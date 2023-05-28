#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_HEAP_NODE 200
void error(char str[]) {
	printf("%s\n", str);
	exit(1);
}
typedef int HNode;
#define key(n) (n)
HNode heap[MAX_HEAP_NODE];
int heap_size;

#define Parent(i) (heap[i/2])
#define Left(i) (heap[i*2])
#define Right(i) (heap[(i*2)+1])

void init_heap() {
	heap_size = 0;
}
int is_empty_heap() {
	return heap_size == 0;
}
int is_full_heap() {
	return (heap_size == MAX_HEAP_NODE - 1);
}
HNode find_heap() {
	return heap[1];
}
void insert_heap(HNode n) {
	int i;
	if (is_full_heap()) return;
	i = ++(heap_size);
	while (i != 1 && key(n) < key(Parent(i))) {
		heap[i] = Parent(i);
		i /= 2;
	}
	heap[i] = n;
}
HNode delete_heap() {
	HNode hroot, last;
	int parent = 1, child = 2;

	if (is_empty_heap())
		error("힙 트리 공백 에러");

	hroot = heap[1];
	last = heap[heap_size--];

	while (child <= heap_size) {
		if (child < heap_size && key(Left(parent)) > key(Right(parent)))
			child++;
		if (key(last) <= key(heap[child]))
			break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = last;
	return hroot;
}
void make_tree(int freq[], int n) {
	HNode e1, e2;
	int i;

	init_heap();
	for (i = 0; i < n; i++) {
		insert_heap(freq[i]);
	}
	for (i = 1; i < n; i++) {
		e1 = delete_heap();
		e2 = delete_heap();
		insert_heap(key(e1) + key(e2));
		printf("(%d+%d)\n", key(e1), key(e2));
	}

}
int main() {
	int arr[26] = { 0 };
	char alpa[26];
	int result = 0;
	int i;
	int c;
	FILE* fp = NULL;
	fp = fopen("input.txt", "r");
	if (fp == NULL) {
		printf("파일을 찾을 수 없습니다.\n");
	}
	else {
		printf("파일을 찾았습니다.\n");
	}
	while ((c = fgetc(fp)) != EOF)   // EOF는 파일의 끝 
	{
		for (i = 0; i < 26; i++) {
			if (c == 'a' + i) {
				arr[i] = arr[i] + 1;
			}
		}
	}
	fclose(fp);
	printf("a ~ z의 빈도 수 출력\n");
	for (i = 0; i < 26; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	FILE* fp1 = NULL;
	fp1 = fopen("stats.txt", "w");
	for (i = 0; i < 26; i++) {
		fprintf(fp1, "%c\t%d\n", 'a' + i, arr[i]);
	}
	for (i = 0; i < 26; i++) {
		alpa[i] = 'a' + i;
	}
	fclose(fp1);
	printf("허프만 압축 과정\n");
	make_tree(arr, 26);
}