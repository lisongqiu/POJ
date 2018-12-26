/*
#include<iostream>
#include<algorithm>
#include<queue>
#include<string.h>

using namespace std;

#define MAXN 210

int N, M;
int G[MAXN][MAXN];
int Prev[MAXN];
int Used[MAXN];

int augment() {
	//init.
	int v;
	memset(Prev, 0, sizeof(Prev));
	memset(Used, 0, sizeof(Used));
	queue<int> que;
	Prev[1] = 0;
	Used[1] = true;
	que.push(1);
	bool findPath = false;
	while (!que.empty()) {
		v = que.front();
		// cout << "bfs: " << v << endl;
		que.pop();
		for (int i = 1; i <= M; i++) {
			// cout << " i: " << i << " " << G[v][i] << " " << Used[i] << endl;
			if (G[v][i] > 0 && !Used[i]) {
				// cout << "get in" << endl;
				Prev[i] = v;
				Used[i] = true;
				if (i == M) {
					findPath = true;
					while (!que.empty())
						que.pop();
					break;
				}
				que.push(i);
			}
		}
	}
	if (!findPath) // end of Ford-Fulkerson.
		return 0;
	int bottleNeck = 0x3f3f3f3f;
	v = M;
	while (Prev[v]) {
		bottleNeck = min(bottleNeck, G[Prev[v]][v]);
		v = Prev[v];
	}
	v = M;
	while (Prev[v]) {
		G[Prev[v]][v] -= bottleNeck;
		G[v][Prev[v]] += bottleNeck;
		v = Prev[v];
	}
	return bottleNeck;
}

int main() {
	while (cin >> N >> M) {
		memset(G, 0, sizeof(G));
		int a, b, c;
		for (int i = 1; i <= N; i++) {
			cin >> a >> b >> c;
			G[a][b] += c;
		}
		long long MAXFLOW = 0;
		int aug;
		while (aug = augment()) {
			// cout << "aug: " << aug << endl;
			MAXFLOW += aug;
		}
		cout << MAXFLOW << endl;
	}
	system("pause");
	return 0;
}
*/