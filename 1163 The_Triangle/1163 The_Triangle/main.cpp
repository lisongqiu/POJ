#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

const int MAXN = 101;
int N;
int map[MAXN][MAXN];

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j <= i; j++)
			cin >> map[i][j];
	for (int i = N - 2; i >= 0; i--) {
		for (int j = 0; j <= i; j++) {
			map[i][j] = max(map[i + 1][j], map[i + 1][j + 1]) + map[i][j];
		}
	}
	cout << map[0][0] << endl;
	system("pause");
}