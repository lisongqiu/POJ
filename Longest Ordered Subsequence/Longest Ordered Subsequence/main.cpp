#include<iostream>
#include<algorithm>
#include<vector>
#include<vector>
#include<string>

using namespace std;

const int MAXN = 1001;
int N;
int a[MAXN];
int dp[MAXN];

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> a[i];
	for (int i = 0; i < N; i++)
		dp[i] = 1;
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < i; j++) {
			if (a[i] > a[j])
				dp[i] = max(dp[j] + 1, dp[i]);
		}
	}
	int res = 0;
	for (int i = 0; i < N; i++)
		res = max(res, dp[i]);
	cout << res << endl;
	system("pause");
}