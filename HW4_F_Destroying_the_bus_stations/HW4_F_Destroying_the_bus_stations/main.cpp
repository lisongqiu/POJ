#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<stack>
#include<string.h>

using namespace std;

#define INF 0x3f3f3f3f
#define MAXN 110
#define MAXM 4010

struct Edge {
	int s, e;
	int cap, cost;
	int next;
};

int N, M, K;
Edge edges[MAXN * 2 + MAXM * 2];
int heads[MAXN];
int edgeCnt;
int costs[MAXN];
int Prev[MAXN];
int startIdx, endIdx;

void init_flow() {
	startIdx = 1;
	endIdx = 2 * N;
	edgeCnt = 0;
	memset(heads, -1, sizeof(heads));
	return;
}

void printGraph() {
	for (int i = startIdx; i <= endIdx; i++) {
		cout << "Node: " << i << endl;
		for (int j = heads[i]; j != -1; j = edges[j].next)
			cout << "--Edge: s:" << edges[j].s << " e:" << edges[j].e << " cap:" << edges[j].cap << " cost:" << edges[j].cost << endl;
	}
}

bool spfa() {
	//printGraph();
	//system("pause");
	memset(Prev, -1, sizeof(Prev));
	for (int i = startIdx; i <= endIdx; i++)
		costs[i] = INF;
	queue<int> que;
	que.push(startIdx);
	costs[startIdx] = 0;
	while (!que.empty()) {
		int tmp = que.front();
		que.pop();
		//cout << "SPFA: " << tmp << endl;
		//system("pause");
		for (int i = heads[tmp]; i != -1; i=edges[i].next) {
			int nextIdx = edges[i].e;
			if (edges[i].cap > 0 && (costs[tmp] + edges[i].cost) < costs[nextIdx]) {
				costs[nextIdx] = costs[tmp] + edges[i].cost;
				Prev[nextIdx] = i;
				que.push(nextIdx);
			}
		}
	}
	if (costs[endIdx] == INF)
		return false;
	else
		return true;
}

int maxFlow() {
	int maxFlow = 0;
	while (spfa()) {
		if (costs[endIdx] > K)
			break;
		//get bottleNeck.
		int bottleNeck = INF;
		int pt = Prev[endIdx];
		while (pt != -1) {
			bottleNeck = min(bottleNeck, edges[pt].cap);
			pt = Prev[edges[pt].s];
		}
		//cout << "bottleNeck: " << bottleNeck << endl;
		//augment edges.
		pt = Prev[endIdx];
		while (pt != -1) {
			edges[pt].cap -= bottleNeck;
			edges[pt ^ 1].cap += bottleNeck;
			pt = Prev[edges[pt].s];
		}
		//update maxFlow.
		maxFlow += bottleNeck;
	}
	return maxFlow;
}

void add_edge(int s, int e, int cap, int cost) {
	//forward edge.
	edges[edgeCnt].s = s;
	edges[edgeCnt].e = e;
	edges[edgeCnt].cap = cap;
	edges[edgeCnt].cost = cost;
	edges[edgeCnt].next = heads[s];
	heads[s] = edgeCnt++;
	//backward edge.
	edges[edgeCnt].s = e;
	edges[edgeCnt].e = s;
	edges[edgeCnt].cap = 0;
	edges[edgeCnt].cost = -cost;
	edges[edgeCnt].next = heads[e];
	heads[e] = edgeCnt++;
	return;
}

int main() {
	int a, b;
	while (~scanf("%d%d%d", &N, &M, &K)) {
		if (N == 0 && M == 0 && K == 0)
			break;
		init_flow();
		for (int i = 1; i <= N; i++) {
			if (i == 1 || i == N)
				add_edge(i, N + i, INF, 0);
			else
				add_edge(i, N + i, 1, 0);
		}
		for (int i = 0; i < M; i++) {
			scanf("%d%d", &a, &b);
			add_edge(N + a, b, 1, 1);
		}
		cout << maxFlow() << endl;
	}
	system("pause");
	return 0;
}

/*
SAMPLE INPUT:
5 7 3
1 3
3 4
4 5
1 2
2 5
1 4
4 5
0 0 0
SAMPLE OUTPUT:
2
*/