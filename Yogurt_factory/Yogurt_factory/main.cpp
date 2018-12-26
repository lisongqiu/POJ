#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;

#define MAXN 10010

long long N, S;
long long a[MAXN][2];

int main() {
	scanf("%lld%lld", &N, &S);
	for (int i = 0; i < N; i++)
		scanf("%lld%lld", &a[i][0], &a[i][1]);
	long long cost = 0;
	long long fee = a[0][0];
	int idx = 0;
	cost += a[0][0] * a[0][1];
	for (int i = 1; i < N; i++) {
		long long tmpCost = fee + (i - idx)*S;
		if (tmpCost <= a[i][0]) {
			cost += tmpCost * a[i][1];
			continue;
		}
		cost += a[i][0] * a[i][1];
		fee = a[i][0];
		idx = i;
	}
	printf("%lld\n", cost);
	system("pause");
	return 0;
}
