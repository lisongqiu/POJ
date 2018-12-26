#define _CRT_SECURE_NO_DEPRECATE

#include<stdio.h>
#include<iostream>
#include<algorithm>

using namespace std;

#define MAXN 10010
int N;
int a[MAXN];

void quick_sort(int *A, int b, int e) {
	if (b >= e)
		return;
	int x = A[e];
	int i = b - 1, tmp;
	for (int j = b; j <= e; j++) {
		if (A[j] <= x) {
			i++;
			tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
		}
	}
	quick_sort(A, b, i - 1);
	quick_sort(A, i + 1, e);
	return;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", a + i);
	//sort(a, a+N);
	quick_sort(a, 0, N - 1);
	/*
	for (int i = 0; i < N; i++)
		printf("%d ", a[i]);
	printf("\n");
	*/
	printf("%d\n", a[N / 2]);
	system("pause");
	return 0;
}