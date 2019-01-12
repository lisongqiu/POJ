#define _CRT_SECURE_NO_DEPRECATE

#include<iostream>
#include<algorithm>
#include<vector>
#include<string.h>

using namespace std;

#define MAXN 200010

long long CNT = 0;
int N;
int a[MAXN];
int b[MAXN];

void mergeSort(int s, int e) {
	if (s == e)
		return;
	int mid = (s + e) / 2;
	mergeSort(s, mid);
	mergeSort(mid + 1, e);
	// merge.
	int lp = s, rp = mid + 1, base = s + mid + 1;
	while (lp <= mid && rp <= e) {
		if (a[lp] <= a[rp]) {
			b[lp + rp - base] = a[lp];
			lp++;
		}
		else {
			int ll = lp, rr = mid + 1;
			while (ll < rr) {
				int mm = (ll + rr) / 2;
				if (2 * a[rp] >= a[mm])
					ll = mm + 1;
				else
					rr = mm;
			}
			CNT += (mid - ll + 1);
			b[lp + rp - base] = a[rp];
			rp++;
		}
	}
	while (lp <= mid) {
		b[lp + rp - base] = a[lp];
		lp++;
	}
	while (rp <= e) {
		b[lp + rp - base] = a[rp];
		rp++;
	}
	for (int i = 0; i < lp + rp - base; i++) {
		a[i + s] = b[i];
	}
	return;
}

int main() {
	while (~scanf("%d", &N)) {
		if (N == 0)
			break;
		for (int i = 0; i < N; i++)
			scanf("%d", a + i);
		CNT = 0;
		mergeSort(0, N - 1);
		printf("%lld\n", CNT);
	}
	system("pause");
	return 0;
}
