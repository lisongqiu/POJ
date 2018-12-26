#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 0x3f3f3f3f

#define N 23500
#define M 1000000

typedef long long LL;

using namespace std;

int head[N], level[N], cur[N];
int num_of_edges;

struct edge {
	int v, cap, next;
};
edge e[M];

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

int main() {
	dinic_init();
	int n, m;
	scanf("%d%d", &n, &m);
	int a, b, c;
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &a, &b);
		add_edge(i, n + 1, a, 0);
		add_edge(0, i, b, 0);
	}
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &a, &b, &c);
		add_edge(a, b, c, c);
		add_edge(b, a, c, c);
	}
	printf("%d\n", dinic(0, n+1));
	system("pause");
	return 0;
}

/*
3 1
1 10
2 10
10 3
2 3 1000
*/
