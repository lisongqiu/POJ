#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string.h>

using namespace std;

#define INF 0x3f3f3f3f
#define MAXN 1010

struct Edge {
	int e;
	int d;
	Edge(){}
	Edge(int ee, int dd):e(ee), d(dd){}
};

int T, N;
vector<Edge> edges[MAXN];
int minD[MAXN];
bool used[MAXN];

int main() {
	scanf("%d%d", &T, &N);
	int a, b, c;
	for (int i = 0; i < T; i++) {
		scanf("%d%d%d", &a, &b, &c);
		edges[a].push_back(Edge(b, c));
		edges[b].push_back(Edge(a, c));
	}
	//init.
	for (int i = 1; i <= N; i++)
		minD[i] = INF;
	memset(used, 0, sizeof(used));
	minD[N] = 0;
	while (1) {
		int minIdx = 0, minVal = INF;
		for (int i = 1; i <= N; i++) {
			if (minD[i] < minVal && !used[i]) {
				minIdx = i;
				minVal = minD[i];
			}
		}
		if (minIdx == 1) {
			cout << minVal << endl;
			break;
		}
		used[minIdx] = true;
		for (int i = 0; i < edges[minIdx].size(); i++) {
			minD[edges[minIdx][i].e] = min(minD[edges[minIdx][i].e], minD[minIdx] + edges[minIdx][i].d);
		}
	}
	system("pause");
	return 0;
}