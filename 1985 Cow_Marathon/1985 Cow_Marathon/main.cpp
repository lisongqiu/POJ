#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <string.h>

using namespace std;

struct Edge {
	int e, v;
	Edge() {}
	Edge(int ee, int vv) :e(ee), v(vv) {}
};

#define INF 0x3f3f3f3f
#define MAXN 40010

int N, M;
vector<Edge> edges[MAXN];
int visited[MAXN];

int dfs(int id) {
	memset(visited, 0, sizeof(visited));
	stack<int> stk;
	stk.push(id);
	int maxId = id, maxVal = 0;
	while (!stk.empty()) {
		int tmp = stk.top();
		stk.pop();
		for (int i = 0; i < edges[tmp].size(); i++) {
			int e = edges[tmp][i].e;
			if (visited[e] != 0 || e == id)
				continue;
			int v = edges[tmp][i].v;
			visited[e] = visited[tmp] + v;
			if (visited[e] > maxVal) {
				maxVal = visited[e];
				maxId = e;
			}
			stk.push(e);
		}
	}
	return maxId;
}

int main() {
	while (~scanf("%d %d", &N, &M)) {
		int a, b, c;
		char d;
		for (int i = 1; i <= N; i++)
			edges[i].clear();
		for (int i = 0; i < M; i++) {
			scanf("%d %d %d %c", &a, &b, &c, &d);
			edges[a].push_back(Edge(b, c));
			edges[b].push_back(Edge(a, c));
		}
		int maxId = dfs(1);
		printf("%d\n", visited[dfs(maxId)]);
	}
	return 0;
}