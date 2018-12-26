#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

#define MAXN 100010
int N;
int a[MAXN];

int getNum(int diff) {
	int res = 0;
	for (int i = 0; i < N - 1; i++) {
		int tgt = a[i] + diff;
		int l = i + 1, r = N - 1;
		while (l < r) {
			int mid = (l + r) / 2;
			if (a[mid] >= tgt)
				r = mid;
			else
				l = mid + 1;
		}
		if (a[l] >= tgt)
			res += N - l;
	}
	return res;
}

int main() {
	while (~scanf("%d", &N)) {
		for (int i = 0; i < N; i++)
			scanf("%d", a + i);
		sort(a, a + N);
		int l = 0, r = a[N - 1] - a[0], mid;
		int threshold = N * (N - 1) / 2 / 2 + 1;
		//cout << "threshold: " << threshold << endl;
		while (l < r) {
			mid = (l + r) / 2 + 1;
			int lgCnt = getNum(mid);
			//cout << l << " " << r << " mid:" << mid << " " << lgCnt << endl;
			if (lgCnt >= threshold)
				l = mid;
			else
				r = mid - 1;
		}
		cout << r << endl;
	}
	system("pause");
	return 0;
}