#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

#define INF 0x3f3f3f3f
#define SIZE 8
#define MAXN 15

int N;
int map[SIZE][SIZE];
long long dp[MAXN][SIZE][SIZE][SIZE][SIZE];

int main() {
	scanf("%d", &N);
	double sum = 0;
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++) {
			scanf("%d", &map[i][j]);
			sum += map[i][j];
		}
	//init dp[*][*][*][*][*].
	for (int k = 1; k < N; k++) {
		for (int x1 = 0; x1 < SIZE; x1++) {
			for (int y1 = 0; y1 < SIZE; y1++) {
				for (int x2 = x1; x2 < SIZE; x2++) {
					for (int y2 = y1; y2 < SIZE; y2++) {
						dp[k][x1][y1][x2][y2] = INF;
					}
				}
			}
		}
	}
	//init dp[0][*][*][*][*].
	for (int x1 = 0; x1 < SIZE; x1++) {
		for (int y1 = 0; y1 < SIZE; y1++) {
			for (int x2 = x1; x2 < SIZE; x2++) {
				for (int y2 = y1; y2 < SIZE; y2++) {
					if (x2 == x1 && y2 == y1)
						dp[0][x1][y1][x2][y2] = map[x2][y2];
					else if (x2 == x1)
						dp[0][x1][y1][x2][y2] = dp[0][x1][y1][x2][y2 - 1] + map[x2][y2];
					else if (y2 == y1)
						dp[0][x1][y1][x2][y2] = dp[0][x1][y1][x2 - 1][y2] + map[x2][y2];
					else
						dp[0][x1][y1][x2][y2] = dp[0][x1][y1][x2 - 1][y2] + dp[0][x1][y1][x2][y2 - 1] - dp[0][x1][y1][x2 - 1][y2 - 1] + map[x2][y2];
				}
			}
		}
	}
	for (int x1 = 0; x1 < SIZE; x1++)
		for (int y1 = 0; y1 < SIZE; y1++)
			for (int x2 = x1; x2 < SIZE; x2++)
				for (int y2 = y1; y2 < SIZE; y2++)
					dp[0][x1][y1][x2][y2] *= dp[0][x1][y1][x2][y2];
	//dp.
	for (int i = 1; i < N; i++) {
		for (int x1 = 0; x1 < SIZE; x1++) {
			for (int y1 = 0; y1 < SIZE; y1++) {
				for (int x2 = x1; x2 < SIZE; x2++) {
					for (int y2 = y1; y2 < SIZE; y2++) {
						for (int col = y1; col < y2; col++) {
							dp[i][x1][y1][x2][y2] = min<long long>(dp[i][x1][y1][x2][y2], dp[i - 1][x1][y1][x2][col] + dp[0][x1][col + 1][x2][y2]);
							dp[i][x1][y1][x2][y2] = min<long long>(dp[i][x1][y1][x2][y2], dp[0][x1][y1][x2][col] + dp[i - 1][x1][col + 1][x2][y2]);
						}
						for (int row = x1; row < x2; row++) {
							dp[i][x1][y1][x2][y2] = min<long long>(dp[i][x1][y1][x2][y2], dp[i - 1][x1][y1][row][y2] + dp[0][row + 1][y1][x2][y2]);
							dp[i][x1][y1][x2][y2] = min<long long>(dp[i][x1][y1][x2][y2], dp[0][x1][y1][row][y2] + dp[i - 1][row + 1][y1][x2][y2]);
						}
					}
				}
			}
		}
	}
	double avg = sum * 1.0 / N;
	double upper = dp[N - 1][0][0][SIZE - 1][SIZE - 1] - 2 * sum * avg + N * avg * avg;
	double res = sqrt(upper / N);
	printf("%.3lf\n", res);
	/*
	//debug.
	for (int x2 = 0; x2 < SIZE; x2++) {
		for (int y2 = 0; y2 < SIZE; y2++) {
			cout << dp[0][0][0][x2][y2] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int x2 = 0; x2 < SIZE; x2++) {
		for (int y2 = 0; y2 < SIZE; y2++) {
			cout << dp[1][0][0][x2][y2] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int x2 = 0; x2 < SIZE; x2++) {
		for (int y2 = 0; y2 < SIZE; y2++) {
			cout << dp[2][0][0][x2][y2] << " ";
		}
		cout << endl;
	}
	cout << endl;
	//debug.
	cout << "sum: " << sum << endl;
	cout << "dp: " << dp[N-1][0][0][SIZE-1][SIZE-1] << endl;
	cout << "upper: " << upper << endl;
	*/
	system("pause");
	return 0;
}


/*

3
1 1 1 1 1 1 1 3
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 0
1 1 1 1 1 1 0 3

*/