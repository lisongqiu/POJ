#define _CRT_SECURE_NO_DEPRECATE

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
	int e, v;
	Edge() {}
	Edge(int ee, int vv):e(ee), v(vv){}
};

#define MAXN 10010

vector<Edge> edges[MAXN];
int dist[MAXN];

int bfs(int id) {
	memset(dist, -1, sizeof(dist));
	queue<int> que;
	dist[id] = 0;
	que.push(id);
	int maxId = id, maxVal = 0;
	while (!que.empty()) {
		int tmp = que.front();
		que.pop();
		for (int i = 0; i < edges[tmp].size(); i++) {
			int e = edges[tmp][i].e;
			int v = edges[tmp][i].v;
			if (dist[e] != -1)
				continue;
			dist[e] = dist[tmp] + v;
			que.push(e);
			if (dist[e] > maxVal) {
				maxVal = dist[e];
				maxId = e;
			}
		}
	}
	return maxId;
}

int main() {
	int a, b, c;
	while (cin >> a >> b >> c) {
		edges[a].push_back(Edge(b, c));
		edges[b].push_back(Edge(a, c));
	}
	int maxId = bfs(1);
	cout << dist[bfs(maxId)] << endl;
	system("pause");
	return 0;
}