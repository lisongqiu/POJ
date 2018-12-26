#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<string.h>

using namespace std;

struct Edge {
	int s, e;
	int cap;
	int next;
};

#define INF 0x3f3f3f3f
#define MAXN 410
#define MAXM 410

int M, N;
Edge edges[4 * MAXM];
int heads[MAXN];
int edgeCnt = 0;
long long maxFlow;
int Prev[MAXN];
bool Used[MAXN];

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
	que.push(1);
	Used[1] = true;
	while (!que.empty()) {
		int tmp = que.front();
		que.pop();
		// cout << "bfs:" << tmp << endl;
		for (int i = heads[tmp]; i != -1; i = edges[i].next) {
			int nextIdx = edges[i].e;
			if (edges[i].cap > 0 && !Used[nextIdx]) {
				Used[nextIdx] = true;
				Prev[nextIdx] = i;
				que.push(nextIdx);
				if (nextIdx == N)
					return true;
			}
		}
	}
	return false;
}

void Fold_Fulkerson() {
	while (bfs()) {
		// printGraph();
		// system("pause");
		//get bottleNeck;
		int bottleNeck = INF;
		int pt = Prev[N];
		while (pt != -1) {
			bottleNeck = min(bottleNeck, edges[pt].cap);
			pt = Prev[edges[pt].s];
		}
		// cout << "bottleNeck: " << bottleNeck << endl;
		//augment edges.
		pt = Prev[N];
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
	while (cin >> M >> N) {
		init();
		int s, e, c;
		for (int i = 0; i < M; i++) {
			cin >> s >> e >> c;
			addEdge(s, e, c);
		}
		Fold_Fulkerson();
		cout << maxFlow << endl;
	}
	system("pause");
	return 0;
}