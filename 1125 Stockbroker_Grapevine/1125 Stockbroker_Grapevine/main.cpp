#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

const int MAXN = 101;
const int INF = 0x3f3f3f3f;
int N;
int map[MAXN][MAXN];

int main() {
	while (cin >> N) {
		if (N == 0)
			break;
		//init
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++)
				map[i][j] = INF;
			map[i][i] = 0;
		}
		//input
		int a, b, k;
		for (int a = 1; a <= N; a++) {
			cin >> k;
			for (int j = 0; j < k; j++) {
				cin >> b;
				cin >> map[a][b];
			}
		}
		//floyd
		for (int k = 1; k <= N; k++) {
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++) {
					map[i][j] = min(map[i][k] + map[k][j], map[i][j]);
				}
			}
		}
		int index=1, cost=INF;
		for (int k = 1; k <= N; k++) {
			int max_cost = 0;
			for (int i = 1; i <= N; i++)
				max_cost = max(max_cost, map[k][i]);
			if (max_cost < cost) {
				index = k;
				cost = max_cost;
			}
		}
		if (cost == INF) 
			cout << "disjoint" << endl;
		else 
			cout << index << " " << cost << endl;
	}
	system("pause");
}