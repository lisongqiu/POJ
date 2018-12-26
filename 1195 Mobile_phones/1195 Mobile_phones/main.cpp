#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

#define MAXN 1024 + 10
int op, a, b, c, d;
int N;
int C[MAXN][MAXN];

int lowbit(int x) {
	return x & (-x);
}

void add(int x, int y, int val) {
	for (int xx = x; xx <= N; xx += lowbit(xx))
		for (int yy = y; yy <= N; yy += lowbit(yy)) {
			//cout << "add: " << xx << " " << yy << endl;
			C[xx][yy] += val;
		}
	return;
}

int sum(int x, int y) {
	int rnt = 0;
	//cout << "SUM_INPUTS: " << x << " " << y << endl;
	for (int xx = x; xx > 0; xx -= lowbit(xx))
		for (int yy = y; yy > 0; yy -= lowbit(yy)) {
			//cout << "(x, y) = " << xx << " " << yy << " " << C[xx][yy] << endl;
			rnt += C[xx][yy];
		}
	return rnt;
}

int main() {
	while (~scanf("%d", &op)) {
		if (op == 3)
			break;
		else if (op == 0) {
			scanf("%d", &a);
			N = a;
			memset(C, 0, sizeof(C));
		}
		else if (op == 1) {
			scanf("%d%d%d", &a, &b, &c);
			add(a + 1, b + 1, c);
		}
		else if (op == 2) {
			scanf("%d%d%d%d", &a, &b, &c, &d);
			int leftDown = sum(a, b);
			int rightUpper = sum(c + 1, d + 1);
			int left = sum(a, d + 1);
			int down = sum(c + 1, b);
			printf("%d\n", rightUpper + leftDown - left - down);
		}
	}
	system("pause");
	return 0;
}
