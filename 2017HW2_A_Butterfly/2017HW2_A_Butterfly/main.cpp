#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;

#define MAXN 1010
int N, M;

struct Node {
	int p;
	int r;
	Node(){}
	Node(int pp, int rr):p(pp), r(rr){}
};
Node nodes[MAXN];

int getPar(int a) {
	if (nodes[a].p == a)
		return a;
	int pa = getPar(nodes[a].p);
	int pr = nodes[nodes[a].p].r;
	nodes[a].p = pa;
	nodes[a].r = (nodes[a].r + pr) % 2;
	return pa;
}

void merge(int a, int b, int r) {
	int pa = getPar(a);
	int pb = getPar(b);
	if (pa == pb)
		return;
	nodes[pa].p = pb;
	nodes[pa].r = (r + nodes[a].r + nodes[b].r) % 2;
	return;

}

int main() {
	while (~scanf("%d%d", &N, &M)) {
		//init.
		bool is_ok = true;
		for (int i = 0; i < N; i++) {
			nodes[i].p = i;
			nodes[i].r = 0;
		}
		int a, b, r;
		while (M--) {
			scanf("%d%d%d", &a, &b, &r);
			if (!is_ok)
				continue;
			int pa = getPar(a);
			int pb = getPar(b);
			if (pa == pb) {
				if (r != (nodes[a].r + nodes[b].r) % 2)
					is_ok = false;
			}
			else
				merge(a, b, r);
		}
		if (is_ok)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	system("pause");
	return 0;
}