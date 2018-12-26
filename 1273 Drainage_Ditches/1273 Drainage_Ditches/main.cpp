#include<iostream>
#include<algorithm>
#include<queue>
#include<stack>

#include<string.h>

using namespace std;

#define MAXN 210
#define INF 0x3f3f3f3f

int N, M;
int G[MAXN][MAXN];
int Layer[MAXN];
bool Used[MAXN];

bool counterLayer() {
	memset(Layer, -1, sizeof(Layer));
	queue<int> que;
	Layer[1] = 0;
	que.push(1);
	while (!que.empty()) {
		int tmp = que.front();
		que.pop();
		for (int i = 1; i <= M; i++) {
			if (G[tmp][i] && Layer[i] == -1) {
				Layer[i] = Layer[tmp] + 1;
				if (i == M)
					return true;
				else
					que.push(i);
			}
		}
	}
	return false;
}

// go on one phrase.
int Dinic() {
	int i;
	int res = 0;
	deque<int> stk;
	while (counterLayer()) {
		memset(Used, 0, sizeof(Used));
		stk.push_back(1);
		Used[1] = true;
		while (!stk.empty()) {
			int tmp = stk.back();
			// cout << tmp << endl;
			if (tmp == M) {
				// find bottleNeck.
				int bottleNeck = INF;
				int neckIndex;
				for (int j = 0; j < stk.size() - 1; j++) {
					int vs = stk[j];
					int ve = stk[j + 1];
					if (bottleNeck > G[vs][ve]) {
						bottleNeck = G[vs][ve];
						neckIndex = vs;
					}
				}
				res += bottleNeck;
				// augment edges.
				for (int j = 0; j < stk.size() - 1; j++) {
					G[stk[j]][stk[j + 1]] -= bottleNeck;
					G[stk[j + 1]][stk[j]] += bottleNeck;
				}
				while (!stk.empty() && stk.back() != neckIndex) {
					Used[stk.back()] = false;
					stk.pop_back();
				}
			}
			else {
				for (i = 1; i <= M; i++) {
					if (G[tmp][i] && Layer[i] == Layer[tmp] + 1 && !Used[i]) {
						Used[i] = true;
						stk.push_back(i);
						break;
					}
				}
				if (i > M)
					stk.pop_back();
			}
		}
	}
	return res;
}

int main() {
	while (cin >> N >> M) {
		memset(G, 0, sizeof(G));
		int a, b, c;
		for (int i = 1; i <= N; i++) {
			cin >> a >> b >> c;
			G[a][b] += c;
		}
		cout << Dinic() << endl;
	}
	system("pause");
	return 0;
}
