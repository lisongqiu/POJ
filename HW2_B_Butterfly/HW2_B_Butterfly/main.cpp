#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;

#define MAXN 1010

struct Node {
	int par;
	int rel;
};

Node nodes[MAXN];
int N, M;

int getPar(int a) {
	if (nodes[a].par == a)
		return a;
	int pa = getPar(nodes[a].par);
	int pr = nodes[nodes[a].par].rel;
	nodes[a].par = pa;
	nodes[a].rel = (nodes[a].rel + pr) % 2;
	return pa;
}

void merge(int a, int b, int r) {
	int pa = getPar(a);
	int pb = getPar(b);
	if (pa == pb)
		return;
	nodes[pa].par = pb;
	nodes[pa].rel = (nodes[a].rel + nodes[b].rel + r) % 2;
	return;
}

int main() {
	while (~scanf("%d%d", &N, &M)) {
		//init.
		for (int i = 0; i < N; i++) {
			nodes[i].par = i;
			nodes[i].rel = 0;
		}
		//input relation.
		int r, a, b;
		bool done = true;
		while (M--) {
			scanf("%d%d%d", &a, &b, &r);
			if (!done)
				continue;
			int pa = getPar(a);
			int pb = getPar(b);
			if (pa != pb)
				merge(a, b, r);
			else {
				int rab = (nodes[a].rel + nodes[b].rel) % 2;
				if (rab != r)
					done = false;
			}
		}
		if (done)
			printf("YES\n");
		else
			printf("NO\n");
	}
	system("pause");
	return 0;
}