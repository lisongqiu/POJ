#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#include <stack>
#include <functional>

using namespace std;

#define MAXN 5010

int N, M;
vector<int> edges[MAXN];
int nidx, scc;
int dfn[MAXN];
int low[MAXN];
int sccs[MAXN];
stack<int> stk;
int inStk[MAXN];
int degrees[MAXN];

void tarjan(int s) {
	if (dfn[s] != -1)
		return;
	dfn[s] = low[s] = ++nidx;
	stk.push(s);
	inStk[s] = true;
	for (int i = 0; i < edges[s].size(); i++) {
		int v = edges[s][i];
		if (dfn[v] == -1) {
			tarjan(v);
			low[s] = min(low[s], low[v]);
		}
		else if(inStk[v]) {
			low[s] = min(low[s], dfn[v]);
		}
	}
	if (dfn[s] == low[s]) {
		scc++;
		while (stk.top() != s) {
			sccs[stk.top()] = scc;
			inStk[stk.top()] = false;
			stk.pop();
		}
		sccs[stk.top()] = scc;
		inStk[stk.top()] = false;
		stk.pop();
	}
	return;
}

int main() {
	while (cin >> N) {
		if (N == 0)
			break;
		cin >> M;
		
		// init.
		nidx = 0, scc = 0;
		memset(dfn, -1, sizeof(dfn));
		memset(low, -1, sizeof(low));
		memset(sccs, -1, sizeof(sccs));
		memset(inStk, 0, sizeof(inStk));
		memset(degrees, 0, sizeof(degrees));
		for (int i = 1; i <= N; i++) {
			edges[i].clear();
		}
		while (!stk.empty())
			stk.pop();

		int a, b;
		while (M--) {
			cin >> a >> b;
			edges[a].push_back(b);
		}
		// tarjan.
		for (int i = 1; i <= N; i++)
			tarjan(i);

		// get degrees.
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < edges[i].size(); j++) {
				int v = edges[i][j];
				if (sccs[i] != sccs[v]) {
					degrees[sccs[i]]++;
				}
			}
		}
		vector<int> res;
		for (int i = 1; i <= N; i++) {
			if (degrees[sccs[i]] == 0)
				res.push_back(i);
		}
		sort(res.begin(), res.end(), less<int>());
		for (int i = 0; i < res.size(); i++)
			cout << res[i] << " ";
		cout << endl;
	}
	system("pause");
	return 0;
}