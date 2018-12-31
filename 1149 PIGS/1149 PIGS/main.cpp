#define _CRT_SECURE_NO_DEPRECATE

#include <cstdio>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>

#define INF 0x3f3f3f3f
#define N (100+2)
#define M (N*N+4*N)

typedef long long LL;

using namespace std;

struct edge {
	int v, cap, next;
};
edge e[M];

int head[N], level[N], cur[N];
int num_of_edges;

void dinic_init(void) {
	num_of_edges = 0;
	memset(head, -1, sizeof(head));
	return;
}

int add_edge(int u, int v, int c1, int c2) {
	int& i = num_of_edges;

	assert(c1 >= 0 && c2 >= 0 && c1 + c2 >= 0); // check for possibility of overflow
	e[i].v = v;
	e[i].cap = c1;
	e[i].next = head[u];
	head[u] = i++;

	e[i].v = u;
	e[i].cap = c2;
	e[i].next = head[v];
	head[v] = i++;
	return i;
}

void print_graph(int n) {
	for (int u = 0; u<n; u++) {
		printf("%d: ", u);
		for (int i = head[u]; i >= 0; i = e[i].next) {
			printf("%d(%d)", e[i].v, e[i].cap);
		}
		printf("\n");
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
	int m, n, s, t;
	int pigs[M + 1], pre[M + 1];
	int used[M + 1];
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= m; i++)
		scanf("%d", pigs + i);
	dinic_init();
	memset(pre, -1, sizeof(pre));
	s = 0, t = n + 1;
	int a, b;
	for (int i = 1; i <= n; i++) {
		memset(used, 0, sizeof(used));
		int cap = 0;
		scanf("%d", &a);
		// key to pigs.
		for (int j = 1; j <= a; j++) {
			scanf("%d", &b);
			int prev = pre[b];
			if (prev < 0) {
				cap += pigs[b];
			}
			else {
				if (!used[prev]) {
					used[prev] = true;
					add_edge(prev, i, INF, 0);
				}
			}
			pre[b] = i;
		}
		if (cap > 0)
			add_edge(s, i, cap, 0);
		// num to bug.
		scanf("%d", &b);
		if (b > 0)
			add_edge(i, t, b, 0);
	}
	printf("%d\n", dinic(s, t));
	system("pause");
	return 0;
}
