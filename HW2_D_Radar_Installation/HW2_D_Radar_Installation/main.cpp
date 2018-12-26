#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<math.h>
#include<string.h>

using namespace std;

struct Node {
	int x, y;
	double lx, rx;
	bool done;
	Node() {}
};

bool cmp(Node& n1, Node& n2) {
	return n1.rx <= n2.rx;
}

#define MAXN 10010

int N, D;
Node nodes[MAXN];
int caseId = 0;

int main() {
	while (~scanf("%d%d", &N, &D)) {
		if (N == 0 && D == 0)
			break;
		bool done = false;
		for (int i = 0; i < N; i++) {
			scanf("%d%d", &nodes[i].x, &nodes[i].y);
			if (done)
				continue;
			if (nodes[i].y > D)
				done = true;
			else {
				double dx = sqrt(D*D - nodes[i].y*nodes[i].y);
				nodes[i].lx = nodes[i].x - dx;
				nodes[i].rx = nodes[i].x + dx;
			}
			nodes[i].done = false;
		}
		if (done) {
			printf("Case %d: -1\n", ++caseId);
			continue;
		}
		sort(nodes, nodes + N, cmp);
		int res = 0;
		for (int i = 0; i < N; i++) {
			if (nodes[i].done)
				continue;
			nodes[i].done = true;
			res ++;
			double thres = nodes[i].rx;
			for (int j = i + 1; j < N; j++) {
				if (nodes[j].lx <= thres)
					nodes[j].done = true;
			}
		}
		printf("Case %d: %d\n", ++caseId, res);
	}
	system("pause");
	return 0;
}