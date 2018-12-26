#include<iostream>
#include<algorithm>
#include<queue>
#include<string>

using namespace std;

const int MAXN = 101, MAXM = 11;
int N, M;
bool map[MAXN][MAXM];

int main() {
	cin >> N >> M;
	memset(map, 0, sizeof(map));
	for (int i = 0; i < N; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < M; j++) {
			if (s[j] == 'P')
				map[i][j] = true;
			else
				map[i][j] = false;
		}
	}

}