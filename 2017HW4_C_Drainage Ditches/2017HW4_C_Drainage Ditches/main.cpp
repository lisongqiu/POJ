#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<string.h>


using namespace std;

#define INF 0x3f3f3f3f
#define MAXN 210
#define MAXM (210*2)

int N, M;

struct Edge {
	int s, e;
	int cap;
	int next;
	Edge(){}
};

Edge edges[MAXM];
int heads[MAXN];
int edgeCnt;
int startIdx, endIdx;
int Prev[MAXN];

void init() {
	edgeCnt = 0;
	memset(heads, -1, sizeof(heads));
}

void insertNode(int s, int e, int c) {
	//forward.
	edges[edgeCnt].s = s;
	edges[edgeCnt].e = e;
	edges[edgeCnt].cap = c;
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
	memset(Prev, -1, sizeof(Prev));
	queue<int> que;
	que.push(startIdx);
	while (!que.empty()) {
		int tmp = que.front();
		que.pop();
		// cout << "tmp:" << tmp << endl;
		for (int i = heads[tmp]; i != -1; i = edges[i].next) {
			int nt = edges[i].e;
			if (edges[i].cap > 0 && Prev[nt] == -1 && nt!=startIdx) {
				Prev[nt] = i;
				que.push(nt);
				if (nt == endIdx)
					return true;
			}
		}
	}
	return false;
}

int dinic() {
	int maxFlow = 0;
	while (bfs()) {
		//get bottleNeck;
		int bottleNeck = INF;
		int pt = Prev[endIdx];
		while (pt != -1) {
			bottleNeck = min(bottleNeck, edges[pt].cap);
			pt = Prev[edges[pt].s];
		}
		//augment.
		pt = Prev[endIdx];
		while (pt != -1) {
			edges[pt].cap -= bottleNeck;
			edges[pt ^ 1].cap += bottleNeck;
			pt = Prev[edges[pt].s];
		}
		//update.
		maxFlow += bottleNeck;
	}
	return maxFlow;
}

int main() {
	while (cin >> M >> N) {
		init();
		startIdx = 1, endIdx = N;
		int a, b, c;
		for (int i = 0; i < M; i++) {
			cin >> a >> b >> c;
			insertNode(a, b, c);
		}
		cout << dinic() << endl;
	}
	system("pause");
	return 0;
}