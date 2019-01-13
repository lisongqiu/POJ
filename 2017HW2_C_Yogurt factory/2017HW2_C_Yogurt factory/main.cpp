#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

#define MAXN 10010
int c[MAXN];
int y[MAXN];
long long Total = 0;

int main() {
	int N, S;
	scanf("%d%d", &N, &S);
	for (int i = 0; i < N; i++)
		scanf("%d%d", &c[i], &y[i]);
	int pt = 0;
	int tmp_c = c[0];
	while (pt < N) {
		if (tmp_c > c[pt])
			tmp_c = c[pt];
		Total += tmp_c * y[pt];
		pt++;
		tmp_c += S;
	}
	printf("%lld\n", Total);
	system("pause");
	return 0;
}
