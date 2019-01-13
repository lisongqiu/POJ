#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

#define MAXN 110010
#define MAXM (MAXN*10001)
int N, M;
int a[MAXN];

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; i++)
		scanf("%d", a + i);
	long long l = 1, r = MAXM;
	while (l < r) {
		long long m = (l + r) / 2;
		int cnt = 1;
		long long cost = 0;
		for (int i = 0; i < N; i++) {
			cost += a[i];
			if (cost > m) {
				cost = a[i];
				if (cost > m) // here !!! important !!!
					cnt = M;
				cnt++;
				if (cnt > M)
					break;
			}
		}
		if (cnt <= M)
			r = m;
		else
			l = m + 1;
	}
	cout << l << endl;
	system("pause");
	return 0;
}