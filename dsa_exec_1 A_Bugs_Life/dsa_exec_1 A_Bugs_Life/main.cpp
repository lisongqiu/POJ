#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<algorithm>
#include<vector>

using namespace std;

struct Item {
	int par, rel;
};

#define MAXN 2010
Item items[MAXN];
int N, M;

int getPar(int a) {
	if (items[a].par == a)
		return a;
	int p = getPar(items[a].par);
	int r = items[items[a].par].rel;
	items[a].par = p;
	items[a].rel = (r + items[a].rel + 2) % 2;
	return p;
}

void merge(int a, int b) {
	int pa = getPar(a);
	int pb = getPar(b);
	if (pa == pb)
		return;
	items[pa].par = pb;
	items[pa].rel = (-items[a].rel + 1 + items[b].rel + 2) % 2;
	return;
}


int main() {
	int T, caseId = 0;
	scanf("%d", &T);
	int a, b;
	while (caseId++ < T) {
		printf("Scenario #%d:\n", caseId);
		scanf("%d%d", &N, &M);
		//init.
		for (int i = 1; i <= N; i++) {
			items[i].par = i;
			items[i].rel = 0;
		}
		bool found = false;
		while (M--) {
			scanf("%d%d", &a, &b);
			if (found)
				continue;
			int pa = getPar(a);
			int pb = getPar(b);
			if (pa != pb) {
				merge(a, b);
				continue;
			}
			int r = (items[a].rel + items[b].rel) % 2;
			if (r == 0)
				found = true;
		}
		if (found)
			printf("Suspicious bugs found!\n\n");
		else
			printf("No suspicious bugs found!\n\n");
	}
	system("pause");
	return 0;
}