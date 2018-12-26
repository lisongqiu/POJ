#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

struct Edge {
	int e, w;
	Edge() {};
	Edge(int ee, int ww) :e(ee), w(ww) {};
};

const int MAXN = 1001;
const int INF = 0x3f3f3f3f;
int T, N;
vector<Edge> edges[MAXN];
int counter[MAXN] = { 0 };
int dist[MAXN];

int main() {
	cin >> T >> N;
	int a, b, c;
	for (int i = 0; i <= N; i++) {
		dist[i] = INF;
		counter[i] = 0;
	}
	for (int i = 0; i < T; i++) {
		cin >> a >> b >> c;
		edges[a].push_back(Edge(b, c));
		edges[b].push_back(Edge(a, c));
	}
	queue<int> que;
	que.push(N);
	dist[N] = 0;
	while (!que.empty()) {
		int n = que.front();
		que.pop();
		for (int i = 0; i < edges[n].size(); i++) {
			Edge tmp = edges[n][i];
			//cout << "Start:" << N << endl;
			if (dist[tmp.e] > dist[n] + tmp.w) {
				//cout << n << " | " << tmp.e << endl;
				dist[tmp.e] = dist[n] + tmp.w;
				counter[tmp.e] += 1;
				que.push(tmp.e);
			}
		}
	}
	cout << dist[1] << endl;
	system("pause");
}