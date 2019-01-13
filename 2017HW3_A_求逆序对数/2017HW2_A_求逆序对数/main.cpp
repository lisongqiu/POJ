#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string.h>

using namespace std;

#define MAXN 20010
int a[MAXN];
int b[MAXN];
int N;
int RTN = 0;

void func(int s, int e) {
	if (s == e)
		return;
	int m = (s + e) / 2;
	func(s, m);
	func(m + 1, e);
	//merge.
	int pl = s, pr = m + 1, base = s + m + 1;
	while (pl <= m && pr <= e) {
		if (a[pl] <= a[pr]) {
			b[pl + pr - base] = a[pl];
			pl++;
		}
		else {
			b[pl + pr - base] = a[pr];
			RTN += (m - pl + 1);
			pr++;
		}
	}
	while (pl <= m) {
		b[pl + pr - base] = a[pl];
		pl++;
	}
	while (pr <= e) {
		b[pl + pr - base] = a[pr];
		pr++;
	}
	for (int i = 0; i < pl + pr - base; i++) {
		a[s + i] = b[i];
	}
	return;
}

int main() {
	while (~scanf("%d", &N)) {
		if (N == 0)
			break;
		for (int i = 0; i < N; i++)
			scanf("%d", a + i);
		RTN = 0;
		func(0, N - 1);
		cout << RTN << endl;
	}
	system("pause");
	return 0;
}
