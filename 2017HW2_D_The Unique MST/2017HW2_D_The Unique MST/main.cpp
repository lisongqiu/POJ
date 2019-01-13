#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<string.h>

using namespace std;

#define MAXN 110

struct Edge {
	int x, y;
	int w;
	Edge(){}
	Edge(int xx, int yy, int ww):x(xx), y(yy), w(ww){}
	bool operator<(const Edge& e) const {
		return this->w > e.w;
	}
};

int T;
int N, M;
bool used[MAXN];
int max_val[MAXN][MAXN];
vector<Edge> edges[MAXN];
bool mapped[MAXN][MAXN];

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &N, &M);
		// init.
		priority_queue<Edge> que;
		memset(used, 0, sizeof(used));
		memset(max_val, 0, sizeof(max_val));
		memset(mapped, 0, sizeof(mapped));
		for (int i = 1; i <= N; i++)
			edges[i].clear();
		int x, y, w;
		for (int i = 0; i < M; i++) {
			scanf("%d%d%d", &x, &y, &w);
			edges[x].push_back(Edge(x, y, w));
			edges[y].push_back(Edge(y, x, w));
		}
		used[1] = true;
		for (int i = 0; i < edges[1].size(); i++)
			que.push(edges[1][i]);
		int res = 0;
		while (!que.empty()) {
			Edge tmp = que.top();
			que.pop();
			if (used[tmp.y])
				continue;
			used[tmp.y] = true;
			res += tmp.w;
			for (int i = 0; i < edges[tmp.y].size(); i++)
				if (!used[edges[tmp.y][i].y])
					que.push(edges[tmp.y][i]);
			mapped[tmp.x][tmp.y] = true;
			mapped[tmp.y][tmp.x] = true;
			for (int i = 1; i <= N; i++) {
				if (!used[i] || i == tmp.y)
					continue;
				max_val[i][tmp.y] = max(max_val[i][tmp.x], tmp.w);
				max_val[tmp.y][i] = max_val[i][tmp.y];
			}
		}
		bool is_unique = true;
		for (int i = 1; i <= N; i++) {
			if (!is_unique)
				break;
			for (int j = 1; j < edges[i].size(); j++) {
				Edge tmp = edges[i][j];
				if (mapped[tmp.x][tmp.y])
					continue;
				if (tmp.w == max_val[tmp.x][tmp.y]) {
					is_unique = false;
					break;
				}
			}
		}
		if (is_unique)
			cout << res << endl;
		else
			cout << "Not Unique!" << endl;
	}
	system("pause");
	return 0;
}