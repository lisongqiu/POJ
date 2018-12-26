#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

const int MAXN = 101;
const int INF = MAXN * MAXN;
int map[MAXN][MAXN];
int N, M;

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			map[i][j] = INF;
		map[i][i] = 1;
	}
	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		map[a][b] = 1;
		map[b][a] = -1;
	}
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (map[i][k] == 1 && map[k][j] == 1)
					map[i][j] = 1;
				else if (map[i][k] == -1 && map[k][j] == -1)
					map[i][j] = -1;
				else
					continue;
			}
		}
	}
	int cnt = 0;
	for (int i = 1; i <= N; i++) {
		bool isOK = true;
		for (int j = 1; j <= N; j++) {
			if (!(map[i][j] == 1 || map[i][j] == -1)) {
				isOK = false;
				break;
			}
		}
		if (isOK)
			cnt++;
	}
	cout << cnt << endl;
	system("pause");
	return 0;
}