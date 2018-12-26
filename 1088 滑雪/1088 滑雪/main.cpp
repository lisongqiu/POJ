#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

struct Point {
	int x, y;
	Point() {};
	Point(int xx, int yy) :x(xx), y(yy) {};
};

const int MAXN = 101;
int R, C;
int map[MAXN][MAXN];
int dp[MAXN][MAXN];
vector<Point> orders;
int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

bool cmp(const Point& a, const Point& b) {
	return map[a.x][a.y] < map[b.x][b.y];
}

int main() {
	cin >> R >> C;
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++) {
			orders.push_back(Point(i, j));
			cin >> map[i][j];
			dp[i][j] = 0;
		}
	sort(orders.begin(), orders.end(), cmp);
	for (int i = 0; i < orders.size(); i++) {
		//cout << orders[i].x << " " << orders[i].y << map[orders[i].x][orders[i].y] << endl;
		int c_x = orders[i].x, c_y = orders[i].y;
		for (int j = 0; j < 4; j++) {
			int n_x = c_x + dir[j][0], n_y = c_y + dir[j][1];
			if (n_x < 0 || n_y < 0 || n_x >= R || n_y >= C || map[n_x][n_y] >= map[c_x][c_y])
				continue;
			dp[c_x][c_y] = max(dp[n_x][n_y] + 1, dp[c_x][c_y]);
		}
	}
	int res = 0;
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			res = max(res, dp[i][j]);
	cout << res+1 << endl;
	system("pause");
}