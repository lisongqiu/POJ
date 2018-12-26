#define _CRT_SECURE_NO_DEPRECATE

#include<iostream>
#include<algorithm>
#include<string.h>
#include<vector>
#include<queue>

using namespace std;

#define MAXN 100
#define INF 0x3f3f3f3f

struct Edge {
	int s, e;
	int cap, cost;
	int next;
	Edge(){}
	Edge(int ss, int ee, int cp, int ct, int nt):s(ss), e(ee), cap(cp), cost(ct), next(nt){}
};

int N, M, K;
int OUTPUT[MAXN][MAXN];
int INPUT[MAXN][MAXN];
int COST[MAXN][MAXN];

Edge edges[MAXN*MAXN + 2*MAXN];
int head[2 * MAXN + MAXN];
int EdgeCnt;
int Cost[2 * MAXN + MAXN];
int Prev[2 * MAXN + MAXN];

void addEdge(int s, int e, int cap, int cost) {
	//forward edge.
	edges[EdgeCnt].s = s;
	edges[EdgeCnt].e = e;
	edges[EdgeCnt].cap = cap;
	edges[EdgeCnt].cost = cost;
	edges[EdgeCnt].next = head[s];
	head[s] = EdgeCnt++;
	//backward edge.
	edges[EdgeCnt].s = e;
	edges[EdgeCnt].e = s;
	edges[EdgeCnt].cap = 0;
	edges[EdgeCnt].cost = -cost;
	edges[EdgeCnt].next = head[e];
	head[e] = EdgeCnt++;
	return;
}

void initFlow(int k) {
	EdgeCnt = 0;
	memset(edges, 0, sizeof(edges));
	memset(head, -1, sizeof(head));
	for (int i = 1; i <= M; i++)
		addEdge(0, i, INPUT[k][i], 0);
	for (int i = 1; i <= N; i++)
		addEdge(M + i, M + N + 1, OUTPUT[k][i], 0);
	for (int i = 1; i <= M; i++)
		for (int j = 1; j <= N; j++)
			addEdge(i, M + j, INPUT[k][i], COST[i][j]);
}

bool SPFA() {
	//init.
	for (int i = 0; i < 2 * MAXN + MAXN; i++)
		Cost[i] = INF;
	memset(Prev, -1, sizeof(Prev));
	//do SPFA.
	queue<int> que;
	que.push(0);
	Cost[0] = 0;
	while (!que.empty()) {
		int curIdx = que.front();
		que.pop();
		for (int i = head[curIdx]; i != -1; i = edges[i].next) {
			int nextIdx = edges[i].e;
			if (edges[i].cap && (edges[i].cost + Cost[curIdx]) < Cost[nextIdx]) {
				Cost[nextIdx] = (edges[i].cost + Cost[curIdx]);
				Prev[nextIdx] = i;
				que.push(nextIdx);
			}
		}
	}
	if (Cost[M + N + 1] == INF)
		return false;
	else
		return true;
}

int minFlow(int k) {
	initFlow(k);
	int minMaxFlow = 0;
	while (SPFA()) {
		//find bottleNeck;
		int bottleNeck = INF;
		int pt = Prev[M + N + 1];
		while (pt != -1) {
			bottleNeck = min(bottleNeck, edges[pt].cap);
			pt = Prev[edges[pt].s];
		}
		//augment edges.
		pt = Prev[M + N + 1];
		while (pt != -1) {
			edges[pt].cap -= bottleNeck;
			edges[pt ^ 1].cap += bottleNeck;
			pt = Prev[edges[pt].s];
		}
		minMaxFlow += bottleNeck * Cost[M + N + 1];
	}
	return minMaxFlow;
}

int main() {
	while (cin >> N >> M >> K) {
		if (N == 0 && M == 0 && K == 0)
			break;
		for (int i = 1; i <= N; i++) {
			for (int k = 1; k <= K; k++)
				cin >> OUTPUT[k][i];
		}
		for (int i = 1; i <= M; i++) {
			for (int k = 1; k <= K; k++)
				cin >> INPUT[k][i];
		}
		int maxFlow = 0;
		for (int k = 1; k <= K; k++) {
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= M; j++) {
					cin >> COST[j][i];
				}
			}
			if (maxFlow == -1)
				continue;
			else {
				int input = 0, output = 0;
				for (int i = 1; i <= N; i++)
					output += OUTPUT[k][i];
				for (int i = 1; i <= M; i++)
					input += INPUT[k][i];
				if (input < output)
					maxFlow = -1;
				else
					maxFlow += minFlow(k);
			}
		}
		cout << maxFlow << endl;
	}
	system("pause");
	return 0;
}
