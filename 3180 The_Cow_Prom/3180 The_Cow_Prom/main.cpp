#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <string.h>

using namespace std;

#define MAXN 10010

int N, M;
vector<int> edges[MAXN];
int dfn[MAXN];
int low[MAXN];
int nidx = 0;
stack<int> stk;
int res = 0;

void tarjan(int s) {
	if (dfn[s] != -1)
		return;
	dfn[s] = low[s] = ++nidx;
	stk.push(s);
	for (int i = 0; i < edges[s].size(); i++) {
		if (dfn[edges[s][i]] == -1)
			tarjan(edges[s][i]);
		low[s] = min(low[s], low[edges[s][i]]);
	}
	if (dfn[s] == low[s]) {
		bool isOk = false;
		while (stk.top() != s) {
			stk.pop();
			isOk = true;
		}
		stk.pop();
		if (isOk)
			res++;
	}
	return;
}

int main() {
	cin >> N >> M;
	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		edges[a].push_back(b);
	}
	// tarjan.
	nidx = 0;
	memset(dfn, -1, sizeof(dfn));
	memset(low, -1, sizeof(low));
	for (int i = 1; i <= N; i++)
		tarjan(i);
	cout << res << endl;
	system("pause");
	return 0;
}
