#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<string.h>

using namespace std;

#define INF 0x3f3f3f3f
#define MAXN 250
#define MAXM 100010

struct Edge {
	int s, e;
	int cap;
	int next;
};

int K, C, M;
int MAP[MAXN][MAXN];
Edge edges[MAXM];
int heads[MAXN];
int prevs[MAXN];
int levels[MAXN];
int edgeCnt;
int startIdx, endIdx;
int MAXFLOW;


void init() {
	edgeCnt = 0;
	MAXFLOW = 0;
	memset(heads, -1, sizeof(heads));
	return;
}

void addEdge(int s, int e, int cap) {
	//forward.
	edges[edgeCnt].s = s;
	edges[edgeCnt].e = e;
	edges[edgeCnt].cap = cap;
	edges[edgeCnt].next = heads[s];
	heads[s] = edgeCnt++;
	//backward.
	edges[edgeCnt].s = e;
	edges[edgeCnt].e = s;
	edges[edgeCnt].cap = 0;
	edges[edgeCnt].next = heads[e];
	heads[e] = edgeCnt++;
	return;
}


bool bfs() {
	memset(levels, 0, sizeof(levels));
	queue<int> que;
	levels[startIdx] = 1;
	que.push(startIdx);
	while (!que.empty()) {
		int tmp = que.front();
		que.pop();
		if (tmp == endIdx)
			return true;
		for (int i = heads[tmp]; i != -1; i = edges[i].next) {
			int nextIdx = edges[i].e;
			if (edges[i].cap > 0 && !levels[nextIdx]) {
				levels[nextIdx] = levels[tmp] + 1;
				que.push(nextIdx);
			}
		}
	}
	return false;
}

int dfs(int curIdx, int bottleNeck) {
	// cout << "dfs: " << curIdx << endl;
	// system("pause");
	if (curIdx == endIdx)
		return bottleNeck;
	int left = bottleNeck;
	for (int i = heads[curIdx]; i != -1; i = edges[i].next) {
		// cout << "i: " << i << " e:" << edges[i].e << " cap:" << edges[i].cap << endl;
		int nextIdx = edges[i].e;
		if (edges[i].cap > 0 && levels[nextIdx] == levels[curIdx] + 1) {
			// cout << nextIdx << " cap:" << edges[i].cap << " level:" << levels[nextIdx] << endl;
			int flow = dfs(nextIdx, min(left, edges[i].cap));
			if (flow > 0) {
				edges[i].cap -= flow;
				edges[i ^ 1].cap += flow;
				left -= flow;
				if (!left)
					break;
			}
		}
	}
	if (left > 0)
		levels[curIdx] = 0;
	return bottleNeck - left;
}

void Dinic() {
	while (bfs()) {
		MAXFLOW += dfs(startIdx, INF);
	}
	return;
}

int main() {
	scanf("%d%d%d", &K, &C, &M);
	for (int i = 1; i <= K + C; i++)
		for (int j = 1; j <= K + C; j++) {
			scanf("%d", &MAP[i][j]);
			if (!MAP[i][j])
				MAP[i][j] = INF;
		}
	// floyd.
	for (int k = 1; k <= K + C; k++)
		for (int i = 1; i <= K + C; i++)
			for (int j = 1; j <= K + C; j++)
				MAP[i][j] = min(MAP[i][j], MAP[i][k] + MAP[k][j]);
	int left = 0;
	int right = 21000;
	while (left < right) {
		int mid = (left + right) / 2;
		// build Graph.
		init();
		startIdx = 0;
		endIdx = K + C + 1;
		for (int i = K + 1; i <= K + C; i++)
			addEdge(startIdx, i, 1);
		for (int i = 1; i <= K; i++)
			addEdge(i, endIdx, M);
		for (int i = K + 1; i <= K + C; i++)
			for (int j = 1; j <= K; j++)
				if (MAP[i][j] <= mid)
					addEdge(i, j, 1);
		Dinic();
		if (MAXFLOW < C)
			left = mid + 1;
		else
			right = mid;
	}
	cout << left << endl;
	system("pause");
	return 0;
}
