/*
#include<iostream>
#include<algorithm>
#include<vector>
#include<math.h>
#include<string.h>
using namespace std;

struct Item{
	int p, d;
	Item(){}
	Item(int pp, int dd) :p(pp), d(dd) {}
};

bool cmp(const Item& a, const Item& b) {
	return a.d < b.d;
}

#define MAXN 10010
int N;
int dp[MAXN][MAXN];

vector<Item> items;

int main() {
	while (cin >> N) {
		//init.
		int p, d;
		int maxD = 0;
		items.clear();
		memset(dp, 0, sizeof(dp));
		//input.
		for (int i = 0; i < N; i++) {
			cin >> p >> d;
			maxD = max<int>(maxD, d);
			items.push_back(Item(p, d));
		}
		//dp.
		sort(items.begin(), items.end(), cmp);
		for (int j = 1; j <= maxD; j++)
			dp[0][j] = items[0].p;
		for (int i = 1; i < N; i++) {
			for (int j = 1; j <= maxD; j++) {
				if (j <= items[i].d) {
					dp[i][j] = max<int>(dp[i - 1][j - 1] + items[i].p, dp[i][j - 1]);
					dp[i][j] = max<int>(dp[i][j], dp[i - 1][j]);
				}
				else
					dp[i][j] = max<int>(dp[i - 1][j], dp[i][j - 1]);
			}
		}
		cout << dp[N - 1][maxD] << endl;
	}
	system("pause");
	return 0;
}
*/