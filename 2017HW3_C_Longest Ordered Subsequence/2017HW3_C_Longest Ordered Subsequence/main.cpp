#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

#define MAXN 1010
int a[MAXN];
int N;
int dp[MAXN];
int rtn = 0;

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", a + i);
	for (int i = 1; i <= N; i++) {
		dp[i] = 1;
		for (int j = 1; j < i; j++)
			if (a[i] > a[j])
				dp[i] = max(dp[i], dp[j] + 1);
		rtn = max(rtn, dp[i]);
	}
	cout << rtn << endl;
	system("pause");
	return 0;
}