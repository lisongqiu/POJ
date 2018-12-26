#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

#define MAXN 50010

int par[MAXN];
int rel[MAXN];
int n, k;
int d, x, y;

int getPar(int x) {
	if (par[x] == x)
		return x;
	int t = getPar(par[x]);
	int r = rel[par[x]];
	par[x] = t;
	rel[x] = (rel[x] + r) % 3;
	return par[x];
}

void merge(int d, int a, int b) {
	int pa = getPar(a);
	int pb = getPar(b);
	par[pa] = pb;
	rel[pa] = (3 + rel[b] - rel[a] + d - 1) % 3;
	return;
}

int main() {
	//cin >> n >> k;
	scanf("%d%d", &n, &k);
	//init array.
	for (int i = 1; i <= n; i++) {
		par[i] = i;
		rel[i] = 0;
	}
	//do judge.
	int cnt = 0;
	for (int i = 0; i < k; i++) {
		//cin >> d >> x >> y;
		scanf("%d%d%d", &d, &x, &y);
		if ((x > n || y > n) || (d == 2 && x == y)) {
			//cout << "PRED: " << d << " " << x << " " << y << endl;
			cnt++;
			continue;
		}
		int px = getPar(x);
		int py = getPar(y);
		if (px != py) {
			merge(d, x, y);
			continue;
		}
		int r = (rel[x] - rel[y] + 3) % 3;
		if ((d == 1 && r != 0) || (d == 2 && r != 1)) {
			//cout << r << "DETAILED: " << d << " " << x << " " << y << endl;
			cnt++;
			continue;
		}
	}
	cout << cnt << endl;
	system("pause");
	return 0;
}