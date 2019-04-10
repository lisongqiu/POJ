#define _CRT_SECURE_NO_DEPRECATE

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#include <stack>
#include <queue>

using namespace std;

#define INF 0x3f3f3f3f
#define MAXN 30010

int N, M;
vector<int> edges[MAXN];
int vals[MAXN];
int nidx, sci;
int dfn[MAXN];
int low[MAXN];
int istk[MAXN];
int sccs[MAXN];
int dp[MAXN];
stack<int> stk;
vector<int> dags[MAXN];
int vs[MAXN];

void init() {
	memset(vs, 0, sizeof(vs));
	nidx = sci = 0;
	memset(dfn, -1, sizeof(dfn));
	memset(low, -1, sizeof(low));
	memset(istk, 0, sizeof(istk));
	memset(sccs, -1, sizeof(sccs));
	while (!stk.empty())
		stk.pop();
	for (int i = 0; i < N; i++) {
		edges[i].clear();
		dags[i].clear();
	}
	return;
}

void tarjan(int s) {
	if (dfn[s] != -1)
		return;
	dfn[s] = low[s] = nidx++;
	istk[s] = true;
	stk.push(s);
	for (int i = 0; i < edges[s].size(); i++) {
		int v = edges[s][i];
		if (dfn[v] == -1) {
			tarjan(v);
			low[s] = min(low[s], low[v]);
		}
		else if (istk[v]) {
			low[s] = min(low[s], dfn[v]);
		}
	}
	if (dfn[s] == low[s]) {
		while(true){
			int v = stk.top();
			sccs[v] = sci;
			istk[v] = false;
			stk.pop();
			if (v == s)
				break;
		}
		sci++;
	}
	return;
}

int main() {
	while (~scanf("%d%d", &N, &M)) {
		// init.
		init();
		// input.
		int a, b;
		for (int i = 0; i < N; i++)
			scanf("%d", &vals[i]);
		for (int i = 0; i < M; i++) {
			scanf("%d%d", &a, &b);
			edges[a].push_back(b);
		}
		// get sccs with Tarjan.
		for (int i = 0; i < N; i++)
			tarjan(i);
		// build dags.
		for (int i = 0; i < N; i++) {
			if (vals[i] > 0) // NOTE HERE!!!!!!
				vs[sccs[i]] += vals[i];
			for (int j = 0; j < edges[i].size(); j++) {
				int v = edges[i][j];
				if (sccs[i] != sccs[v]) {
					dags[sccs[i]].push_back(sccs[v]);
				}
			}
		}
		// dp.
		for (int i = 0; i < sci; i++)
			dp[i] = vs[i];
		while (true) {
			bool updated = false;
			for (int i = 0; i < sci; i++) {
				for (int j = 0; j < dags[i].size(); j++) {
					int v = dags[i][j];
					if (dp[i] + vs[v] > dp[v]) {
						updated = true;
						dp[v] = dp[i] + vs[v];
					}
				}
			}
			if (!updated)
				break;
		}
		int res = 0;
		for (int i = 0; i < sci; i++)
			res = max(res, dp[i]);
		printf("%d\n", res);
	}
	system("pause");
	return 0;
}