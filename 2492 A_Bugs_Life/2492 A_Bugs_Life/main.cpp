#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<iostream>
#include<algorithm>

using namespace std;

#define MAXN 2010

int par[MAXN];
int rel[MAXN];

int getPar(int a) {
	if (par[a] == a)
		return a;
	int t = getPar(par[a]);
	int r = rel[par[a]];
	par[a] = t;
	rel[a] = (2 + r + rel[a]) % 2;
	return par[a];
}

int main() {
	int caseN;
	int n, m;
	scanf("%d", &caseN);
	for (int i = 1; i <= caseN; i++) {
		scanf("%d%d", &n, &m);
		//init.
		for (int j = 1; j <= n; j++) {
			par[j] = j;
			rel[j] = 0;
		}
		bool found = false;
		int a, b;
		while(m--){
			scanf("%d%d", &a, &b);
			int pa = getPar(a);
			int pb = getPar(b);
			if (pa == pb) {
				if (rel[a] == rel[b])
					found = true;
			}
			else {
				par[pa] = pb;
				rel[pa] = (rel[a] + rel[b] + 1) % 2;
			}
		}
		if (found)
			printf("Scenario #%d:\nSuspicious bugs found!\n\n", i);
		else
			printf("Scenario #%d:\nNo suspicious bugs found!\n\n", i);
	}
	system("pause");
	return 0;
}
