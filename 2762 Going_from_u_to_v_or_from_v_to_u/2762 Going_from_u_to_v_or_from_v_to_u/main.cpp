#define _CRT_SECURE_NO_DEPRECATE

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#include <stack>
#include <queue>

using namespace std;

#define MAXN 1010

int T;
int N, M;
vector<int> edges[MAXN];
vector<int> dag[MAXN];
int dfn[MAXN];
int low[MAXN];
bool inStk[MAXN];
stack<int> stk;
int nidx, lidx;
int levels[MAXN];
int degrees[MAXN];
queue<int> que;

void tarjan(int s) {
	if (dfn[s] != -1)
		return;
	dfn[s] = low[s] = ++nidx;
	inStk[s] = true;
	stk.push(s);
	for (int i = 0; i < edges[s].size(); i++) {
		int v = edges[s][i];
		if (dfn[v] == -1) {
			tarjan(v);
			low[s] = min(low[s], low[v]);
		}
		else if (inStk[v]) {
			low[s] = min(low[s], low[v]);
		}
	}
	if (dfn[s] == low[s]) {
		lidx++;
		while (stk.top() != s) {
			levels[stk.top()] = lidx;
			inStk[stk.top()] = false;
			stk.pop();
		}
		levels[stk.top()] = lidx;
		inStk[stk.top()] = false;
		stk.pop();
	}
	return;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &N, &M);
		// init.
		nidx = lidx = 0;
		for (int i = 0; i <= N; i++) {
			edges[i].clear();
			dag[i].clear();
		}
		memset(dfn, -1, sizeof(dfn));
		memset(low, -1, sizeof(low));
		memset(inStk, 0, sizeof(inStk));
		memset(degrees, 0, sizeof(degrees));
		memset(levels, -1, sizeof(levels));
		while (!stk.empty())
			stk.pop();
		while (!que.empty())
			que.pop();
		int a, b;
		while (M--){
			scanf("%d%d", &a, &b);
			edges[a].push_back(b);
		}
		// build dag.
		for (int i = 1; i <= N; i++)
			tarjan(i);
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < edges[i].size(); j++) {
				if (levels[edges[i][j]] != levels[i]) {
					dag[levels[i]].push_back(levels[edges[i][j]]);
					degrees[levels[edges[i][j]]]++;
				}
			}
		}
		// topo.
		for (int i = 1; i <= lidx; i++)
			if (degrees[i] == 0)
				que.push(i);
		while (!que.empty()) {
			int tmp = que.front();
			que.pop();
			if (!que.empty())
				break;
			for (int i = 0; i < dag[tmp].size(); i++) {
				degrees[dag[tmp][i]]--;
				if (degrees[dag[tmp][i]] == 0)
					que.push(dag[tmp][i]);
			}
		}
		if (que.empty())
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
	system("pause");
	return 0;
}