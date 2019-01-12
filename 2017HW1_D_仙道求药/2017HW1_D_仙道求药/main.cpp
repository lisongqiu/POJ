#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string>
#include<string.h>

using namespace std;

struct Node{
	int r, c;
	int step;
	Node(){}
	Node(int rr, int cc, int ss):r(rr), c(cc), step(ss){}
};

#define MAXN 21

int M, N;
int m[MAXN][MAXN];
Node END;
int dirs[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

int main() {
	while (cin >> M >> N) {
		if (M == 0 && N == 0)
			break;
		string line;
		queue<Node> que;
		for (int i = 0; i < M; i++) {
			cin >> line;
			for (int j = 0; j < N; j++) {
				if (line[j] == '@') {
					m[i][j] = false;
					que.push(Node(i, j, 0));
				}
				else if (line[j] == '.') {
					m[i][j] = true;
				}
				else if (line[j] == '#') {
					m[i][j] = false;
				}
				else {
					m[i][j] = true;
					END.r = i;
					END.c = j;
				}
			}
		}
		int rnt = -1;
		while (!que.empty()) {
			Node tmp = que.front();
			que.pop();
			if (tmp.r == END.r && tmp.c == END.c) {
				rnt = tmp.step;
				break;
			}
			for (int i = 0; i < 4; i++) {
				int nr = tmp.r + dirs[i][0];
				int nc = tmp.c + dirs[i][1];
				if (nr >= 0 && nc >= 0 && nr < M && nc < N &&m[nr][nc]) {
					m[nr][nc] = false;
					que.push(Node(nr, nc, tmp.step + 1));
				}
			}
		}
		cout << rnt << endl;
	}
	system("pause");
	return 0;
}