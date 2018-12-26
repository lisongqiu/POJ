#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

const int MAXN = 3403;
const int MAXM = 12881;
int N, M;
int charms[MAXN][2];
int dp[MAXM];

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
		cin >> charms[i][0] >> charms[i][1];
	for (int j = 0; j <= M; j++)
		dp[j] = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = M; j >= 1; j--) {
			if (j >= charms[i][0]) 
				dp[j] = max(charms[i][1] + dp[j - charms[i][0]], dp[j]);
			else
				dp[j] = dp[j];
		}
	}
	cout << dp[M] << endl;
	system("pause");
}