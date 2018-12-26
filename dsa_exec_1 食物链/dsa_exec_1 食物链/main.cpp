#define _CRT_SECURE_NO_DEPRECATE

#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct Item {
	int par, rel;
};

#define MAXN 50010
int N, K;
Item items[MAXN];

int getPar(int v) {
	if (items[v].par == v)
		return v;
	int par = getPar(items[v].par);
	int rel = items[items[v].par].rel;
	items[v].par = par;
	items[v].rel = (rel + items[v].rel) % 3;
	return par;
}

void merge(int a, int b, int r) { //a-->b with relation r.
	int pa = getPar(a);
	int pb = getPar(b);
	if (pa == pb)
		return;
	items[pa].par = pb;
	items[pa].rel = (-items[a].rel + r + items[b].rel) % 3;
	return;
}

int main() {
	scanf("%d%d", &N, &K);
	//init.
	for (int i = 1; i <= N; i++) {
		items[i].par = i;
		items[i].rel = 0;
	}
	int a, b, c;
	int res = 0;
	while (K--) {
		scanf("%d%d%d", &a, &b, &c);
		if (b > N || c > N || (a == 2 && b == c)) {
			res++;
			continue;
		}
		int pa = getPar(b);
		int pb = getPar(c);
		if (pa == pb) {
			int r = (items[b].rel - items[c].rel + 3 + 1) % 3;
			if (r == a)
				continue;
			else
				res++;
		}
		else
			merge(b, c, a - 1);
	}
	printf("%d\n", res);
	system("pause");
	return 0;
}