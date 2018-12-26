#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;

#define MAXN 20010

int N;
int a[MAXN];
int b[MAXN];

int mergeSort(int begin, int end) {
	if (begin == end)
		return 0;
	int mid = (begin + end) >> 1;
	int res = 0;
	res += mergeSort(begin, mid);
	res += mergeSort(mid + 1, end);
	int pb = 0;
	int pl = begin, pr = mid + 1;
	while (pl <= mid && pr <= end) {
		if (a[pl] <= a[pr]) {
			b[pb++] = a[pl];
			pl++;
		}
		else {
			b[pb++] = a[pr];
			pr++;
			res += (mid - pl + 1);
		}
	}
	while (pl <= mid)
		b[pb++] = a[pl++];
	while (pr <= end)
		b[pb++] = a[pr++];
	for (int i = 0; i < pb; i++)
		a[begin + i] = b[i];
	return res;
}

int main() {
	while (~scanf("%d", &N)) {
		if (N == 0)
			break;
		for (int i = 0; i < N; i++)
			scanf("%d", a + i);
		printf("%d\n", mergeSort(0, N - 1));
	}
	system("pause");
	return 0;
}