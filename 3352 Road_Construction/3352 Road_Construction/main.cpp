#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#include <math.h>

using namespace std;

#define MAXN 1010
#define MAXR 1010

int N, R;
vector<int> edges[MAXN];
vector<int> bridges[MAXN];
int dfn[MAXN];
int low[MAXN];
int par[MAXN];
int levels[MAXN];
int cnts[MAXN];
int nidx = 0;

void tarjan(int s) {
	if (dfn[s] != -1)
		return;
	// cout << "tarjan " << s << endl;
	dfn[s] = low[s] = nidx++;
	for (int i = 0; i < edges[s].size(); i++) {
		// unvisited.
		if (par[edges[s][i]] == -1) {
			par[edges[s][i]] = s;
			tarjan(edges[s][i]);
			low[s] = min(low[s], low[edges[s][i]]);
			// cout << "s=" << s << " low[s]=" << low[s] << " edges[s][i]=" << edges[s][i] << " low[edges[s][i]]=" << low[edges[s][i]] << endl;
			if (low[edges[s][i]] > dfn[s]) {
				bridges[s].push_back(edges[s][i]);
				bridges[edges[s][i]].push_back(s);
			}
		}
		// visited.
		else if (par[s] != edges[s][i]) {
			low[s] = min(low[s], low[edges[s][i]]);
			// cout << "visited ! " << "s=" << s << " low[s]=" << low[s] << " edges[s][i]=" << edges[s][i] << " low[edges[s][i]]=" << low[edges[s][i]] << endl;
		}
	}
	return;
}

bool dfs(int s) {
	if (levels[s] != -1)
		return false;
	levels[s] = nidx;
	for (int i = 0; i < edges[s].size(); i++) {
		if (find(bridges[s].begin(), bridges[s].end(), edges[s][i]) == bridges[s].end())
			dfs(edges[s][i]);
	}
	return true;
}

int main() {
	cin >> N >> R;
	int a, b;
	for (int i = 0; i < R; i++) {
		cin >> a >> b;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	// tarjan algorithm to get bridges.
	nidx = 0;
	memset(dfn, -1, sizeof(dfn));
	memset(par, -1, sizeof(par));
	par[1] = 1;
	for (int i = 1; i <= N; i++)
		tarjan(i);
	// build trees;
	nidx = 0;
	memset(levels, -1, sizeof(levels));
	for (int i = 1; i <= N; i++) {
		if (dfs(i))
			nidx++;
	}
	memset(cnts, 0, sizeof(cnts));
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < bridges[i].size(); j++) {
			cnts[levels[i]]++;
			cnts[levels[bridges[i][j]]]++;
		}
	}
	int res = 0;
	for (int i = 0; i < nidx; i++) {
		if (cnts[i] == 2) // if leaf node.
			res++;
	}
	cout << ceil(res / 2.0) << endl;
	system("pause");
	return 0;
}
