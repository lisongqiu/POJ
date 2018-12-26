#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

const int MAXN = 510;
const int INF = 0x3f3f3f3f;

int F, N, M, W;
int s, e, w;

struct Edge {
	int s, e;
	int w;
	Edge() {};
	Edge(int ss, int ee, int ww) :s(ss), e(ee), w(ww) {};
};

vector<Edge> edges;
int dist[MAXN];

bool bellman_ford(int v) {
	for (int i = 0; i <= N; i++)
		dist[i] = INF;
	dist[v] = 0;
	for (int k = 0; k < N; k++) { //reach with fewer than k edges.
		bool changed = false;
		for (int i = 0; i < edges.size(); i++) {
			Edge tmp = edges[i];
			if (dist[tmp.e] > dist[tmp.s] + tmp.w) {
				dist[tmp.e] = dist[tmp.s] + tmp.w;
				changed = true;
			}
		}
		if (!changed)
			return false;
	}
	for (int i = 0; i < edges.size(); i++) {
		Edge tmp = edges[i];
		if (dist[tmp.e] > dist[tmp.s] + tmp.w) {
			return true;
		}
	}
	return false;
}

int main() {
	cin >> F;
	while (F--) {
		edges.clear();
		cin >> N >> M >> W;
		for (int i = 0; i < M; i++) {
			cin >> s >> e >> w;
			edges.push_back(Edge(s, e, w));
			edges.push_back(Edge(e, s, w));
		}
		for (int i = 0; i < W; i++) {
			cin >> s >> e >> w;
			edges.push_back(Edge(s, e, -w));
		}
		if (bellman_ford(1)) {
			cout << "YES" << endl;
		}
		else
			cout << "NO" << endl;
	}
	system("pause");
}