#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<stack>
#include<string.h>

using namespace std;

#define INF 0x3f3f3f3f
#define MAXN (220*2)
#define MAXM (MAXN*2*MAXN*2)

struct Edge {
	int s, e;
	int cap;
	int next;
	Edge(){}
};

int N, M;
Edge edges[MAXM];
int heads[MAXN];
int edgeCnt;
int startIdx, endIdx;
int layers[MAXN];
int Prev[MAXN];
bool used[MAXN];

void init() {
	edgeCnt = 0;
	memset(heads, -1, sizeof(heads));
	return;
}

void printGraph() {
	for (int i = startIdx; i <= endIdx; i++) {
		cout << "Node: " << i << endl;
		for (int j = heads[i]; j != -1; j = edges[j].next)
			cout << "--Edge: " << edges[j].s << " " << edges[j].e << " cap:" << edges[j].cap << endl;
	}
}

void add_edge(int s, int e, int c) {
	edges[edgeCnt].s = s;
	edges[edgeCnt].e = e;
	edges[edgeCnt].cap = c;
	edges[edgeCnt].next = heads[s];
	heads[s] = edgeCnt++;

	edges[edgeCnt].e = s;
	edges[edgeCnt].s = e;
	edges[edgeCnt].cap = 0;
	edges[edgeCnt].next = heads[e];
	heads[e] = edgeCnt++;
	return;
}

bool bfs() {
	memset(layers, -1, sizeof(layers));
	queue<int> q;
	q.push(startIdx);
	layers[startIdx] = 0;
	while (!q.empty()) {
		int tmp = q.front();
		q.pop();
		for (int i = heads[tmp]; i != -1; i = edges[i].next) {
			int nt = edges[i].e;
			if (layers[nt] == -1 && edges[i].cap > 0) {
				layers[nt] = layers[tmp] + 1;
				q.push(nt);
				if (nt == endIdx)
					return true;
			}
		}
	}
	return false;
}

int dinic() {
	int maxflow = 0;
	while (bfs()) {
		memset(Prev, -1, sizeof(Prev));
		memset(used, 0, sizeof(used));
		stack<int> stk;
		stk.push(startIdx);
		used[startIdx] = true;
		while (!stk.empty()) {
			int tmp = stk.top();
			if (tmp == endIdx) {
				// get bottleNeck.
				int bottleNeck = INF;
				int bottleIdx = -1;
				int pt = Prev[endIdx];
				while (pt != -1) {
					if (edges[pt].cap < bottleNeck) {
						bottleNeck = edges[pt].cap;
						bottleIdx = edges[pt].s;
					}
					pt = Prev[edges[pt].s];
				}
				// augment.
				pt = Prev[endIdx];
				while (pt != -1) {
					edges[pt].cap -= bottleNeck;
					edges[pt ^ 1].cap += bottleNeck;
					pt = Prev[edges[pt].s];
				}
				// backtracking.
				while (!stk.empty() && stk.top() != bottleIdx) {
					used[stk.top()] = false;
					stk.pop();
				}
				// cout << "bottleNeck: " << bottleNeck << endl;
				// update.
				maxflow += bottleNeck;
			}
			else {
				int i = 0;
				for (i = heads[tmp]; i != -1; i = edges[i].next) {
					int nt = edges[i].e;
					if (layers[tmp] + 1 == layers[nt] && edges[i].cap > 0 && !used[nt]) {
						Prev[nt] = i;
						used[nt] = true;
						stk.push(nt);
						break;
					}
				}
				if(i==-1)
					stk.pop();
			}
		}
	}
	return maxflow;
}


int main() {
	while (cin >> N >> M) {
		init();
		startIdx = 0;
		endIdx = N + M + 1;
		int a, b;
		for (int i = 1; i <= N; i++) {
			cin >> a;
			while (a--) {
				cin >> b;
				add_edge(i, N + b, 1);
			}
		}
		for (int i = 1; i <= N; i++)
			add_edge(startIdx, i, 1);
		for (int i = N + 1; i <= N + M; i++)
			add_edge(i, endIdx, 1);
		cout << dinic() << endl;
	}
	system("pause");
	return 0;
}