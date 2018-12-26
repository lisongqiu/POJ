#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;

const int UP = 0, DOWN = 1;
const int MAXN = 25;
long long C[MAXN][MAXN][2];
int K;
int n;
long long c;

void init(int n) {
	memset(C, 0, sizeof(C));
	C[1][1][UP] = C[1][1][DOWN] = 1;
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			for (int k = j; k <= i - 1; k++) //note the start index k=j here !!!
				C[i][j][UP] += C[i - 1][k][DOWN];
			for (int k = 1; k <= j - 1; k++)
				C[i][j][DOWN] += C[i - 1][k][UP];
		}
	}
	return;
}

void func(int n, long long c) {
	bool isUp = false;
	long long nowRes = c;
	vector<long long> buf;
	long long k = 0;
	while (true) {
		k++;
		long long tmp = C[n][k][UP] + C[n][k][DOWN];
		//cout << "k:" << k << " nowRes: " << nowRes << " tmp:" << tmp << endl;
		if (tmp >= nowRes) {
			if (C[n][k][DOWN] >= nowRes)
				isUp = false;
			else {
				nowRes -= C[n][k][DOWN];
				isUp = true;
			}
			break;
		}
		nowRes -= tmp;
	}
	buf.push_back(k);
	for (int i = 1; i < n; i++) {
		long long start = isUp ? k : 1;
		int dir = isUp ? DOWN : UP;
		k = start;
		while (true) {
			long long tmp = C[n-i][k][dir];
			//cout << "k: " << k << " isUP: " << isUp << " nowRes: " << nowRes << " tmp:" << tmp << endl;
			if (tmp >= nowRes)
				break;
			nowRes -= tmp;
			k += 1;
		}
		isUp = !isUp;
		buf.push_back(k);
	}
	vector<int> res;
	for (int i = 1; i <= n; i++)
		res.push_back(i);
	for (int i = 0; i < buf.size(); i++) {
		cout << res[buf[i] - 1] << " ";
		res.erase(res.begin() + buf[i] - 1);
	}
	cout << endl;
}

int main() {
	cin >> K;
	init(MAXN);
	while (K--) {
		cin >> n >> c;
		/*
		long long cnt = 0;
		for (int i = 1; i <= n; i++)
			cnt += C[n][i][UP] + C[n][i][DOWN];
		cout << "LIMIT:" << cnt << endl;
		*/
		func(n, c);
	}
	system("pause");
	return 0;
}