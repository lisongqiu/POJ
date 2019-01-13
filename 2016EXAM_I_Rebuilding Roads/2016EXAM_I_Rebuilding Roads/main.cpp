#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string.h>

using namespace std;

#define INF 0x3f3f3f3f
#define MAXN 151

int N, P;
vector<int> nodes[MAXN];
int dp[MAXN][MAXN];

void dfs(int root) {
	// cout << "root: " << root << endl;
	// leaf node.
	if (nodes[root].size() == 0) {
		dp[root][1] = 0;
		for (int i = 2; i <= P; i++)
			dp[root][i] = INF;
		return;
	}
	// init.
	dp[root][1] = nodes[root].size();
	for (int i = 2; i <= P; i++)
		dp[root][i] = INF;
	for (int i = 0; i < nodes[root].size(); i++) {
		dfs(nodes[root][i]);
		for (int j = P; j >= 1; j--) {
			for (int k = 1; k <= j - 1; k++) {
				//cout << "root:"<<root<<" j:" << j << " k:" << k << " dp[root][k]:" << dp[root][k] << " dp[nodes[root][i]][j - k]:" << dp[nodes[root][i]][j - k] << endl;
				dp[root][j] = min(dp[root][j], dp[root][k] + dp[nodes[root][i]][j - k] - 1);
			}
		}
	}
	return;
}

int main() {
	cin >> N >> P;
	int a, b;
	for (int i = 0; i < N - 1; i++) {
		cin >> a >> b;
		nodes[a].push_back(b);
	}
	dfs(1);
	int rtn = dp[1][P];
	for (int i = 2; i <= N; i++) {
		rtn = min(rtn, dp[i][P] + 1);
	}
	cout << rtn << endl;
	system("pause");
	return 0;
}