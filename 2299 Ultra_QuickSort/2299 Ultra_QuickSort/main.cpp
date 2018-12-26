#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<algorithm>
#include<vector>
#include<string.h>

using namespace std;

#define MAXN 500010
int N;
int a[MAXN];

long long mergeSort(int begin, int end) { //must be long long. int will lead to WrongAnswer.
	long long res = 0;
	if (begin == end)
		return 0;
	int mid = (begin + end) / 2;
	res += mergeSort(begin, mid);
	res += mergeSort(mid + 1, end);
	int lp = begin, rp = mid + 1;
	vector<int> buffer;
	while (lp <= mid && rp <= end) {
		if (a[lp] < a[rp])
			buffer.push_back(a[lp++]);
		else {
			buffer.push_back(a[rp++]);
			res += (mid - lp + 1);
		}
	}
	while (lp <= mid)
		buffer.push_back(a[lp++]);
	while (rp <= end)
		buffer.push_back(a[rp++]);
	for (int i = 0; i <= end - begin; i++) {
		a[begin + i] = buffer[i];
	}
	return res;
}

int main() {
	while (~scanf("%d", &N)) {
		if (N == 0)
			break;
		for (int i = 0; i < N; i++)
			scanf("%d", a + i);
		printf("%lld\n", mergeSort(0, N-1));
	}
	system("pause");
	return 0;
}