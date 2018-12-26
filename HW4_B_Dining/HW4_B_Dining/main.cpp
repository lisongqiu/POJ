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
#define MAXN 410
#define MAXM (MAXN*MAXN)

int N, F, D;

struct Edge {
	int s, e;
	int cap;
	int next;
};

Edge edges[MAXM];
int heads[MAXN];
int edgeCnt = 0;
int maxFlow;
int Prev[MAXN];
bool Used[MAXN];
int startIdx, endIdx;

void init() {
	maxFlow = 0;
	edgeCnt = 0;
	memset(edges, 0, sizeof(edges));
	memset(heads, -1, sizeof(heads));
	return;
}

void addEdge(int s, int e, int cap) {
	//forward edge.
	edges[edgeCnt].s = s;
	edges[edgeCnt].e = e;
	edges[edgeCnt].cap = cap;
	edges[edgeCnt].next = heads[s];
	heads[s] = edgeCnt++;
	//backward edge.
	edges[edgeCnt].s = e;
	edges[edgeCnt].e = s;
	edges[edgeCnt].cap = 0;
	edges[edgeCnt].next = heads[e];
	heads[e] = edgeCnt++;
	return;
}

void printGraph() {
	cout << "=========================" << endl;
	cout << maxFlow << endl;
	for (int i = 1; i <= N; i++) {
		cout << "Node: " << i << endl;
		for (int j = heads[i]; j != -1; j = edges[j].next)
			cout << "--Edge: s:" << edges[j].s << " e:" << edges[j].e << " cap:" << edges[j].cap << endl;
	}
	return;
}

bool bfs() {
	memset(Used, 0, sizeof(Used));
	memset(Prev, -1, sizeof(Prev));
	queue<int> que;
	que.push(startIdx);
	Used[startIdx] = true;
	while (!que.empty()) {
		int tmp = que.front();
		que.pop();
		for (int i = heads[tmp]; i != -1; i = edges[i].next) {
			int nextIdx = edges[i].e;
			if (edges[i].cap > 0 && !Used[nextIdx]) {
				Used[nextIdx] = true;
				Prev[nextIdx] = i;
				que.push(nextIdx);
				if (nextIdx == endIdx)
					return true;
			}
		}
	}
	return false;
}

void Fold_Fulkerson() {
	//cout << "Fold_Fulkerson" << endl;
	while (bfs()) {
		//printGraph();
		//system("pause");
		//get bottleNeck;
		int bottleNeck = INF;
		int pt = Prev[endIdx];
		while (pt != -1) {
			bottleNeck = min(bottleNeck, edges[pt].cap);
			pt = Prev[edges[pt].s];
		}
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
	return;
}


int main() {
	cin >> N >> F >> D;
	init();
	startIdx = 0;
	endIdx = 2 * N + F + D + 1;
	int f, d, t;
	int fs[MAXN], ds[MAXN];
	for (int i = 1; i <= N; i++) {
		addEdge(i, N + i, 1);
		cin >> f >> d;
		for (int j = 0; j < f; j++) {
			cin >> t;
			addEdge(2 * N + t, i, 1);
		}
		for (int j = 0; j < d; j++) {
			cin >> t;
			addEdge(N + i, 2 * N + F + t, 1);
		}
	}
	for (int i = 1; i <= F; i++)
		addEdge(startIdx, 2 * N + i, 1);
	for (int i = 1; i <= D; i++)
		addEdge(2 * N + F + i, endIdx, 1);
	Fold_Fulkerson();
	cout << maxFlow << endl;
	system("pause");
	return 0;
}