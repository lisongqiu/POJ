#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string.h>

using namespace std;

#define MAXN 1100
#define MAXM 44000
#define INF 0x3f3f3f3f

struct Edge {
	int s, e;
	int cost, cap;
	int next;
	Edge() {}
	Edge(int ss, int ee, int ct, int cp, int nt) :s(ss), e(ee), cost(ct), cap(cp), next(nt){}
};

Edge edges[MAXM];
int head[MAXN];
int N, M;
int edgeCnt = 0;

int Cost[MAXN];
int Prev[MAXN];
int Used[MAXN];

void addEdge(int s, int e, int cap, int cost) {
	//forward edge.
	edges[edgeCnt].s = s;
	edges[edgeCnt].e = e;
	edges[edgeCnt].cap = cap;
	edges[edgeCnt].cost = cost;
	edges[edgeCnt].next = head[s];
	head[s] = edgeCnt++;
	//backward edge.
	edges[edgeCnt].s = e;
	edges[edgeCnt].e = s;
	edges[edgeCnt].cap = 0;
	edges[edgeCnt].cost = -cost;
	edges[edgeCnt].next = head[e];
	head[e] = edgeCnt++;
}

bool SPFA() {
	//init.
	for (int i = 0; i <= N + 1; i++)
		Cost[i] = INF;
	memset(Prev, -1, sizeof(Prev));
	memset(Used, 0, sizeof(Used));
	//do SPFA.
	queue<int> que;
	que.push(0);
	Cost[0] = 0;
	Used[0] = true;
	while (!que.empty()) {
		int curIdx = que.front();
		//cout << "curIdx: " << curIdx << endl;
		que.pop();
		Used[curIdx] = false;
		for (int i = head[curIdx]; i != -1; i = edges[i].next) {
			int nextIdx = edges[i].e;
			//cout << "nextIdx: " << nextIdx << " cap:" << edges[i].cap << endl;
			if (edges[i].cap && (Cost[curIdx] + edges[i].cost) < Cost[nextIdx]) {
				//cout << "next: " << nextIdx << endl;
				Cost[nextIdx] = Cost[curIdx] + edges[i].cost;
				Prev[nextIdx] = i;
				if (!Used[nextIdx]) {
					Used[nextIdx] = true;
					que.push(nextIdx);
				}
			}
		}
	}
	if (Cost[N + 1] == INF)
		return false;
	else
		return true;
}

void printGraph() {
	for (int i = 0; i <= N + 1; i++) {
		cout << "Node: " << i << endl;
		for (int j = head[i]; j != -1; j = edges[j].next)
			cout << " -Edge:" << edges[j].s << " " << edges[j].e << " cap:" << edges[j].cap << " cost:" << edges[j].cost << endl;
	}
}

int minFlow() {
	int minCostFlow = 0;
	//debug.
	// printGraph();
	while (SPFA()) {
		//get bottleNeck;
		int bottleNeck = INF;
		int pt = Prev[N + 1];
		while (pt != -1) {
			bottleNeck = min(bottleNeck, edges[pt].cap);
			pt = Prev[edges[pt].s];
		}
		//augment edges.
		pt = Prev[N + 1];
		while (pt != -1) {
			edges[pt].cap -= bottleNeck;
			edges[pt ^ 1].cap += bottleNeck;
			pt = Prev[edges[pt].s];
		}
		// cout << "bottleNeck: " << bottleNeck << endl;
		//compute minCostFlow.
		minCostFlow += Cost[N + 1] * bottleNeck;
	}
	return minCostFlow;
}

int main() {
	//init.
	edgeCnt = 0;
	memset(head, -1, sizeof(head));
	memset(edges, 0, sizeof(edges));
	//input.
	scanf("%d%d", &N, &M);
	int s, e, c;
	for (int i = 1; i <= M; i++) {
		scanf("%d%d%d", &s, &e, &c);
		addEdge(s, e, 1, c);
		addEdge(e, s, 1, c);
	}
	// add new S & T node.
	addEdge(0, 1, 2, 0);
	addEdge(N, N + 1, 2, 0);
	// compute minMaxFlow.
	printf("%d\n", minFlow());
	system("pause");
	return 0;
}

/*
Test Case:

4 5
1 2 1
2 3 1
3 4 1
1 3 2
2 4 2
*/
