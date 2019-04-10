#define _CRT_SECURE_NO_DEPRECATE

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#include <stack>
#include <queue>

using namespace std;

struct Edge {
	int e, c;
	Edge(){}
	Edge(int ee, int cc):e(ee), c(cc){}
};

#define INF 0x3f3f3f3f
#define MAXN 510

vector<Edge> edges[MAXN];
int N, M, K;
int nidx, sci;
int dfn[MAXN];
int low[MAXN];
int istk[MAXN];
int sccs[MAXN];
stack<int> stk;
int dags[MAXN][MAXN];

void tarjan(int s) {
	if (dfn[s] != -1)
		return;
	dfn[s] = low[s] = ++nidx;
	istk[s] = true;
	stk.push(s);
	for (int i = 0; i < edges[s].size(); i++) {
		int v = edges[s][i].e;
		if (dfn[v] == -1) {
			tarjan(v);
			low[s] = min(low[s], low[v]);
		}
		else if (istk[v]) {
			low[s] = min(low[s], dfn[v]);
		}
	}
	if (dfn[s] == low[s]) {
		sci++;
		while (stk.top() != s) {
			sccs[stk.top()] = sci;
			istk[stk.top()] = false;
			stk.pop();
		}
		sccs[stk.top()] = sci;
		istk[stk.top()] = false;
		stk.pop();
	}
	return;
}

int SPFA(int s, int e) {
	if (s == e)
		return 0;
	int res[MAXN];
	for (int i = 0; i <= N; i++)
		res[i] = INF;
	res[s] = 0;
	queue<int> que;
	que.push(s);
	while (!que.empty()) {
		int tmp = que.front();
		que.pop();
		for (int i = 1; i <= sci; i++) {
			if (dags[tmp][i] == INF)
				continue;
			if ((dags[tmp][i] + res[tmp]) < res[i]) {
				res[i] = dags[tmp][i] + res[tmp];
				que.push(i);
			}
		}
	}
	return res[e];
}

int main() {
	while (scanf("%d%d", &N, &M)) {
		if (N == 0 && M == 0)
			break;
		// init.
		nidx = 0, sci = 0;
		memset(dfn, -1, sizeof(dfn));
		memset(low, -1, sizeof(low));
		memset(istk, 0, sizeof(istk));
		memset(sccs, -1, sizeof(sccs));
		while (!stk.empty())
			stk.pop();
		for (int i = 1; i <= N; i++)
			edges[i].clear();
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				dags[i][j] = INF;
		int a, b, c;
		while (M--) {
			scanf("%d%d%d", &a, &b, &c);
			edges[a].push_back(Edge(b, c));
		}
		for (int i = 1; i <= N; i++)
			tarjan(i);
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < edges[i].size(); j++) {
				int v = edges[i][j].e;
				if (sccs[i] != sccs[v]) {
					dags[sccs[i]][sccs[v]] = min(dags[sccs[i]][sccs[v]], edges[i][j].c);
				}
			}
		}
		scanf("%d", &K);
		while (K--) {
			scanf("%d%d", &a, &b);
			int res = SPFA(sccs[a], sccs[b]);
			if (res == INF)
				printf("Nao e possivel entregar a carta\n");
			else
				printf("%d\n", res);
		}
		printf("\n");
	}
	system("pause");
	return 0;
}