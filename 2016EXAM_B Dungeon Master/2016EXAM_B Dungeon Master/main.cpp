#define _CRT_SECURE_NO_DEPRECATE

#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string>
#include<string.h>

using namespace std;

#define MAXN 31

struct Node {
	int l, r, c;
	int step;
	Node(){}
	Node(int ll, int rr, int cc, int ss):l(ll), r(rr), c(cc), step(ss){}
};

int L, R, C;
int maps[MAXN][MAXN][MAXN];
bool used[MAXN][MAXN][MAXN];
int dirs[6][3] = { {0, 1, 0},{0, -1, 0},{0, 0, 1},{0, 0, -1},{1, 0, 0},{-1, 0, 0} };
Node START, END;

int main() {
	while (cin >> L >> R >> C) {
		if (L == 0 && R == 0 && C == 0)
			break;
		string s;
		for (int i = 0; i < L; i++) {
			for (int j = 0; j < R; j++) {
				cin >> s;
				for (int k = 0; k < C; k++) {
					if (s[k] == 'S') {
						maps[i][j][k] = 1;
						START.l = i;
						START.r = j;
						START.c = k;
					}
					else if (s[k] == '.')
						maps[i][j][k] = 1;
					else if (s[k] == 'E') {
						maps[i][j][k] = 1;
						END.l = i;
						END.r = j;
						END.c = k;
					}
					else {
						maps[i][j][k] = 0;
					}
				}
			}
		}
		int times = -1;
		queue<Node> que;
		memset(used, 0, sizeof(used));
		used[START.l][START.r][START.c] = 1;
		que.push(Node(START.l, START.r, START.c, 0));
		while (!que.empty()) {
			Node tmp = que.front();
			que.pop();
			if (tmp.l == END.l && tmp.r == END.r && tmp.c == END.c) {
				times = tmp.step;
				break;
			}
			for (int i = 0; i < 6; i++) {
				int nl = tmp.l + dirs[i][0], nr = tmp.r + dirs[i][1], nc = tmp.c + dirs[i][2];
				if (nl < 0 || nr < 0 || nc < 0 || nl >= L || nr >= R || nc >= C || used[nl][nr][nc] || !maps[nl][nr][nc]) {
					continue;
				}
				used[nl][nr][nc] = true;
				que.push(Node(nl, nr, nc, tmp.step + 1));
			}
		}
		if (times == -1)
			cout << "Trapped!" << endl;
		else
			cout << "Escaped in " << times << " minute(s)." << endl;
	}
	system("pause");
	return 0;
}