#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>

using namespace std;

struct Edge {
	int e, w;
	Edge() {};
	Edge(int ee, int ww) :e(ee), w(ww) {};
};

const int MAXN = 510;
const int INF = 0x3f3f3f3f;
int F;
int N, M, W;
vector<Edge> edges[MAXN];
int counter[MAXN];
int dist[MAXN];

bool spfa(int v) {
	for (int i = 0; i <= N; i++)
		dist[i] = INF;
	dist[v] = 0;
	queue<int> que;
	que.push(v);
	while (!que.empty()) {
		int n = que.front();
		que.pop();
		for (int i = 0; i < edges[n].size(); i++) {
			Edge tmp = edges[n][i];
			if (dist[tmp.e] > dist[n] + tmp.w) {
				dist[tmp.e] = dist[n] + tmp.w;
				counter[tmp.e] += 1;
				if (counter[tmp.e] >= N)
					return true;
				que.push(tmp.e);
			}
		}
	}
	for (int i = 1; i <= N; i++) {
		if (counter[i] >= N)
			return true;
	}
	return false;
}

int main() {
	cin >> F;
	while (F--) {
		cin >> N >> M >> W;
		for (int i = 0; i <= N; i++) {
			edges[i].clear();
			counter[i] = 0;
		}
		int a, b, c;
		for (int i = 0; i < M; i++) {
			cin >> a >> b >> c;
			edges[a].push_back(Edge(b, c));
			edges[b].push_back(Edge(a, c));
		}
		for (int i = 0; i < W; i++) {
			cin >> a >> b >> c;
			edges[a].push_back(Edge(b, -c));
		}
		if (spfa(1))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	system("pause");
}