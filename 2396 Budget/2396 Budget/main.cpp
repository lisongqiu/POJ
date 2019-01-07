#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include <queue>
#include <vector>
#include <algorithm>

#define INF 0x3f3f3f3f
#define N (255)
#define M (2 * N * N)

typedef long long LL;

using namespace std;

struct edge {
	int u, v, cap, next;
	int origin;
};
edge e[M];

int head[N], level[N], cur[N];
int num_of_edges;

/*
* When there are multiple test sets, you need to re-initialize before each
*/
void dinic_init(void) {
	num_of_edges = 0;
	memset(head, -1, sizeof(head));
	return;
}

int add_edge(int u, int v, int c1, int c2) {
	int& i = num_of_edges;

	assert(c1 >= 0 && c2 >= 0 && c1 + c2 >= 0); // check for possibility of overflow
	e[i].u = u;
	e[i].v = v;
	e[i].cap = c1;
	e[i].origin = e[i].cap;
	e[i].next = head[u];
	head[u] = i++;

	e[i].u = v;
	e[i].v = u;
	e[i].cap = c2;
	e[i].origin = e[i].cap;
	e[i].next = head[v];
	head[v] = i++;
	return i;
}

void print_graph(int n) {
	for (int i = 0; i <= n; i++) {
		cout << "node: " << i << endl;
		for (int j = head[i]; j != -1; j=e[j].next)
			cout << "  edge: " << e[j].u << "," << e[j].v << " cap:" << e[j].cap << " origin:" << e[j].origin << endl;
	}
	return;
}

/*
* Find all augmentation paths in the current level graph
* This is the recursive version
*/
int dfs(int u, int t, int bn) {
	if (u == t) return bn;
	int left = bn;
	for (int &i = cur[u]; i >= 0; i = e[i].next) {
		int v = e[i].v;
		int c = e[i].cap;
		if (c > 0 && level[u] + 1 == level[v]) {
			int flow = dfs(v, t, min(left, c));
			if (flow > 0) {
				e[i].cap -= flow;
				e[i ^ 1].cap += flow;
				cur[u] = i;
				left -= flow;
				if (!left) break;
			}
		}
	}
	if (left > 0) level[u] = 0;
	return bn - left;
}

bool bfs(int s, int t) {
	memset(level, 0, sizeof(level));
	level[s] = 1;
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (u == t) return true;
		for (int i = head[u]; i >= 0; i = e[i].next) {
			int v = e[i].v;
			if (!level[v] && e[i].cap > 0) {
				level[v] = level[u] + 1;
				q.push(v);
			}
		}
	}
	return false;
}

LL dinic(int s, int t) {
	LL max_flow = 0;

	while (bfs(s, t)) {
		memcpy(cur, head, sizeof(head));
		max_flow += dfs(s, t, INT_MAX);
	}
	return max_flow;
}

int upstream(int s, int n) {
	int cnt = 0;
	vector<bool> visited(n);
	queue<int> q;
	visited[s] = true;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = head[u]; i >= 0; i = e[i].next) {
			int v = e[i].v;
			if (e[i].cap > 0 && !visited[v]) {
				visited[v] = true;
				q.push(v);
				cnt++;
			}
		}
	}
	return cnt; // excluding s
}

int main() {
	int caseN;
	int m, n;
	int startIdx, endIdx;
	cin >> caseN;
	int matrix[201][21];
	int maxs[201][21];
	int mins[201][21];
	bool used[201][21];
	int constrains[N];
	while (caseN--) {
		cin >> m >> n;
		memset(constrains, -1, sizeof(constrains));
		memset(matrix, 0, sizeof(matrix));
		memset(used, 0, sizeof(used));
		for(int i=1;i<=m;i++)
			for (int j = 1; j <= n; j++) {
				maxs[i][j] = INF;
				mins[i][j] = 0;
			}
		dinic_init();
		startIdx = 0, endIdx = m + n + 1;
		int tgtFlow = 0, checkFlow = 0;
		int a, b, c;
		char op;
		bool isPossible = true;
		int k, si, ei, sj, ej;
		for (int i = 1; i <= m; i++) {
			cin >> c;
			tgtFlow += c;
			add_edge(startIdx, i, c, 0);
			constrains[i] = num_of_edges - 2;
		}
		for (int j = 1; j <= n; j++) {
			cin >> c;
			checkFlow += c;
			add_edge(m + j, endIdx, c, 0);
			constrains[m + j] = num_of_edges - 2;
		}
		if (tgtFlow != checkFlow)
			isPossible = false;
		cin >> k;
		while (k--) {
			cin >> a >> b >> op >> c;
			if (!isPossible)
				continue;
			si = a, ei = a;
			sj = b, ej = b;
			if (a == 0) {
				si = 1, ei = m;
			}
			if (b == 0) {
				sj = 1, ej = n;
			}
			for (int i = si; i <= ei; i++) {
				for (int j = sj; j <= ej; j++) {
					if (op == '=') {
						if (c > maxs[i][j] || c < mins[i][j]) {
							isPossible = false;
							break;
						}
						maxs[i][j] = c;
						mins[i][j] = c;
					}
					else if (op == '>') {
						if (c >= maxs[i][j]) {
							isPossible = false;
							break;
						}
						mins[i][j] = c + 1;
					}
					else {
						if (c <= mins[i][j]) {
							isPossible = false;
							break;
						}
						maxs[i][j] = c - 1;
					}
				}
			}
		}
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				matrix[i][j] += mins[i][j];
				e[constrains[i]].cap -= mins[i][j];
				e[constrains[m + j]].cap -= mins[i][j];
				if (e[constrains[i]].cap < 0 || e[constrains[m + j]].cap < 0) {
					isPossible = false;
					break;
				}
				tgtFlow -= mins[i][j];
				add_edge(i, m + j, maxs[i][j] - mins[i][j], 0);
			}
		}
		if (isPossible && tgtFlow == dinic(startIdx, endIdx)) {
			for (int i = 2*(m+n); i < num_of_edges; i++) {
				if (e[i].origin > 0)
					matrix[e[i].u][e[i].v - m] += e[i].origin - e[i].cap;
			}
			for (int i = 1; i <= m; i++) {
				for (int j = 1; j <= n; j++) {
					cout << matrix[i][j] << " ";
				}
				cout << endl;
			}
		}
		else {
			cout << "IMPOSSIBLE" << endl;
		}
	}
	system("pause");
	return 0;
}