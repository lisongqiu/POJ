#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string.h>
#include<vector>
#include<stack>
#include<queue>

using namespace std;

#define INF 0x3f3f3f3f
#define MAXP 11
#define MAXN 51

int P, N;

struct Node {
	int cap;
	int inputs[MAXP];
	int outputs[MAXP];
	bool isStart() {
		bool res = true;
		for(int i=0;i<P;i++)
			if (inputs[i] == 1) {
				res = false;
				break;
			}
		return res;
	}
	bool isEnd() {
		bool res = true;
		for(int i=0;i<P;i++)
			if (outputs[i] != 1) {
				res = false;
				break;
			}
		return res;
	}
};

struct Edge {
	int s, e;
	int cap, origin;
	int next;
	Edge(){}
};

Node nodes[MAXN];
int Heads[MAXN];
Edge Edges[2 * MAXN*MAXN];
int edgeCnt = 0;
int maxFlow = 0;
int levels[MAXN];
int Prev[MAXN];
bool Used[MAXN];

void init() {
	maxFlow = 0;
	edgeCnt = 0;
	memset(Heads, -1, sizeof(Heads));
	memset(Edges, 0, sizeof(Edges));
	return;
}

void printGraph() {
	cout << maxFlow << endl;
	for (int i = 0; i <= N + 1; i++) {
		cout << "Node: " << i << endl;
		for (int j = Heads[i]; j != -1; j = Edges[j].next)
			cout << "--Edge: s:" << Edges[j].s << " e:" << Edges[j].e << " capacity:" << Edges[j].cap << " origin:" << Edges[j].origin << endl;
	}
	return;
}

void addEdge(int s, int e, int cap) {
	//forward edge.
	Edges[edgeCnt].s = s;
	Edges[edgeCnt].e = e;
	Edges[edgeCnt].cap = cap;
	Edges[edgeCnt].origin = cap;
	Edges[edgeCnt].next = Heads[s];
	Heads[s] = edgeCnt++;
	//backward edge.
	Edges[edgeCnt].s = e;
	Edges[edgeCnt].e = s;
	Edges[edgeCnt].cap = 0;
	Edges[edgeCnt].origin = 0;
	Edges[edgeCnt].next = Heads[e];
	Heads[e] = edgeCnt++;
	return;
}

bool bfs() {
	memset(levels, -1, sizeof(levels));
	queue<int> que;
	levels[0] = 0;
	que.push(0);
	while (!que.empty()) {
		int tmp = que.front();
		que.pop();
		for (int i = Heads[tmp]; i != -1; i = Edges[i].next) {
			int nextIdx = Edges[i].e;
			if (Edges[i].cap > 0 && levels[nextIdx] == -1) {
				que.push(nextIdx);
				levels[nextIdx] = levels[tmp] + 1;
				if (nextIdx == N + 1)
					return true;
			}
		}
	}
	return false;
}

void Dinic() {
	stack<int> que;
	while (bfs()) {
		memset(Used, 0, sizeof(Used));
		memset(Prev, -1, sizeof(Prev));
		que.push(0);
		Used[0] = true;
		while (!que.empty()) {
			int tmp = que.top();
			// debug.
			//cout << "Dinic: " << tmp << endl;
			if (tmp == N + 1) {
				//get bottleNeck.
				int bottleNeck = INF;
				int neckIdx = 0;
				int pt = Prev[N + 1];
				while (pt != -1) {
					if (bottleNeck >= Edges[pt].cap) {
						neckIdx = Edges[pt].s;
						bottleNeck = Edges[pt].cap;
					}
					pt = Prev[Edges[pt].s];
				}
				// debug.
				// cout << "bottleNeck: " << bottleNeck << " neckIdx: " << neckIdx << endl;
				//augment edges.
				pt = Prev[N + 1];
				while (pt != -1) {
					Edges[pt].cap -= bottleNeck;
					Edges[pt ^ 1].cap += bottleNeck;
					pt = Prev[Edges[pt].s];
				}
				//backtracking.
				while (!que.empty() && que.top() != neckIdx) {
					Used[que.top()] = false;
					que.pop();
				}
				//update flow.
				maxFlow += bottleNeck;
			}
			else {
				int i;
				for (i = Heads[tmp]; i != -1; i = Edges[i].next) {
					int nextIdx = Edges[i].e;
					if (Edges[i].cap > 0 && levels[nextIdx] == levels[tmp] + 1 && !Used[nextIdx]) {
						que.push(nextIdx);
						Prev[nextIdx] = i;
						Used[nextIdx] = true;
						break;
					}
				}
				if (i == -1)
					que.pop();
			}
		}
	}
	return;
}

int main() {
	cin >> P >> N;
	for (int i = 1; i <= N; i++) {
		cin >> nodes[i].cap;
		for (int j = 0; j < P; j++)
			cin >> nodes[i].inputs[j];
		for (int j = 0; j < P; j++)
			cin >> nodes[i].outputs[j];
	}
	init();
	for (int i = 1; i <= N; i++) {
		if (nodes[i].isStart())
			addEdge(0, i, nodes[i].cap);
		if (nodes[i].isEnd())
			addEdge(i, N + 1, nodes[i].cap);
		for (int j = 1; j <= N; j++) {
			if (i == j)
				continue;
			bool res = true;
			for(int p=0;p<P;p++)
				if (nodes[j].inputs[p] != 2 && nodes[j].inputs[p] != nodes[i].outputs[p]) {
					res = false;
					break;
				}
			if (res)
				addEdge(i, j, nodes[i].cap);
		}
	}
	//
	//// debug.
	//printGraph();
	//system("pause");
	
	Dinic();
	
	//// debug.
	//printGraph();
	//system("pause");

	cout << maxFlow << " ";
	int cnt = 0;
	vector<int> outEdges;
	for (int i = 0; i < edgeCnt; i++) {
		if (Edges[i].origin > 0 && Edges[i].origin > Edges[i].cap && Edges[i].s != 0 && Edges[i].e != N + 1) {
			outEdges.push_back(i);
			cnt++;
		}
	}
	cout << cnt << endl;
	for (int i = 0; i < outEdges.size(); i++) {
		int edgeIdx = outEdges[i];
		cout << Edges[edgeIdx].s << " " << Edges[edgeIdx].e << " " << Edges[edgeIdx].origin - Edges[edgeIdx].cap << endl;
	}
	system("pause");
	return 0;
}


/*
Sample Input

Sample input 1
3 4
15  0 0 0  0 1 0
10  0 0 0  0 1 1
30  0 1 2  1 1 1
3   0 2 1  1 1 1
Sample input 2
3 5
5   0 0 0  0 1 0
100 0 1 0  1 0 1
3   0 1 0  1 1 0
1   1 0 1  1 1 0
300 1 1 2  1 1 1
Sample input 3
2 2
100  0 0  1 0
200  0 1  1 1
Sample Output

Sample output 1
25 2
1 3 15
2 3 10
Sample output 2
4 5
1 3 3
3 5 3
1 2 1
2 4 1
4 5 1
Sample output 3
0 0

*/