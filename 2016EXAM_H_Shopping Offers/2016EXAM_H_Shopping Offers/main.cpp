#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string.h>
#include<map>

using namespace std;

#define MAXN 6
#define MAXM 110

struct Offer{
	vector<int> c;
	vector<int> k;
	int price;
};

int B, S;

map<int, int> codes;
int K[MAXN];
int P[MAXN];
int dp[MAXN][MAXN][MAXN][MAXN][MAXN][MAXM];
Offer offers[MAXM];

int main() {
	memset(K, 0, sizeof(K));
	memset(P, 0, sizeof(P));

	cin >> B;
	int c, k, p;
	for (int i = 0; i < B; i++) {
		cin >> c >> k >> p;
		codes[c] = i;
		K[i] = k;
		P[i] = p;
	}
	cin >> S;
	for (int i = 1; i <= S; i++) {
		cin >> c;
		while (c--) {
			cin >> k >> p;
			offers[i].c.push_back(codes[k]);
			offers[i].k.push_back(p);
		}
		cin >> c;
		offers[i].price = c;
	}
	// do dp.
	int idx[MAXN];
	for (idx[0] = 0; idx[0] <= K[0]; idx[0]++) {
		for (idx[1] = 0; idx[1] <= K[1]; idx[1]++) {
			for (idx[2] = 0; idx[2] <= K[2]; idx[2]++) {
				for (idx[3] = 0; idx[3] <= K[3]; idx[3]++) {
					for (idx[4] = 0; idx[4] <= K[4]; idx[4]++) {
						// init.
						dp[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][0] = P[0] * idx[0] + P[1] * idx[1] + P[2] * idx[2] + P[3] * idx[3] + P[4] * idx[4];
					}
				}
			}
		}
	}
	//system("pause");
	for (idx[0] = 0; idx[0] <= K[0]; idx[0]++) {
		for (idx[1] = 0; idx[1] <= K[1]; idx[1]++) {
			for (idx[2] = 0; idx[2] <= K[2]; idx[2]++) {
				for (idx[3] = 0; idx[3] <= K[3]; idx[3]++) {
					for (idx[4] = 0; idx[4] <= K[4]; idx[4]++) {
						// dp.
						for (int i = 1; i <= S; i++) {
							// init.
							dp[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][i] = dp[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][i - 1];
							// check offer i.
							int j = 1;
							while (1) {
								bool is_ok = true;
								int subs[5];
								memset(subs, 0, sizeof(subs));
								for (int k = 0; k < offers[i].c.size(); k++) {
									if (offers[i].k[k] * j <= idx[offers[i].c[k]]) {
										subs[offers[i].c[k]] -= offers[i].k[k] * j;
										continue;
									}
									is_ok = false;
									break;
								}
								if (!is_ok)
									break;
								dp[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][i] = min(dp[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][i],
									dp[idx[0] + subs[0]][idx[1] + subs[1]][idx[2] + subs[2]][idx[3] + subs[3]][idx[4] + subs[4]][i - 1] + offers[i].price*j);
								j++;
							}
						}
					}
				}
			}
		}
	}
	cout << dp[K[0]][K[1]][K[2]][K[3]][K[4]][S] << endl;
	system("pause");
	return 0;
}
