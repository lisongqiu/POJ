#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string.h>

using namespace std;

#define INF 0x3f3f3f3f
#define MAXN 110

int N, M, S;
double V;
double R[MAXN][MAXN];
double C[MAXN][MAXN];

bool SPFA() {
	double maxs[MAXN];
	int times[MAXN];
	memset(maxs, 0, sizeof(maxs));
	memset(times, 0, sizeof(times));
	queue<int> que;
	maxs[S] = V;
	que.push(S);
	while (!que.empty()) {
		int tmp = que.front();
		que.pop();
		//cout << "que: " << tmp << " maxs:" << maxs[tmp] << endl;
		for (int i = 1; i <= N; i++) {
			if (maxs[tmp] > C[tmp][i] && R[tmp][i] > 0) {
				double new_max = (maxs[tmp] - C[tmp][i]) * R[tmp][i];
				if (new_max > maxs[i]) {
					que.push(i);
					times[i]++;
					maxs[i] = new_max;
					if (times[i] > N)
						return true;
				}
			}
		}
	}
	return false;
}

int main() {
	memset(R, 0, sizeof(R));
	memset(C, 0, sizeof(C));
	cin >> N >> M >> S >> V;
	int a, b;
	double r, c;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		cin >> r >> c;
		R[a][b] = r;
		C[a][b] = c;
		cin >> r >> c;
		R[b][a] = r;
		C[b][a] = c;
	}
	if (SPFA())
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
	system("pause");
	return 0;
}