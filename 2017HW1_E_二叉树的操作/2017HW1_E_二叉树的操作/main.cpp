#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string.h>

using namespace std;

struct Node {
	int p;
	int lc, rc;
	Node() {}
};

#define MAXN 101
Node nodes[MAXN];
int t;
int n, m;

int main() {
	cin >> t;
	while (t--) {
		cin >> n >> m;
		int x, y, z;
		for (int i = 0; i < n; i++) {
			cin >> x >> y >> z;
			nodes[x].lc = y;
			if (y != -1)
				nodes[y].p = x;
			nodes[x].rc = z;
			if (z != -1)
				nodes[z].p = x;
		}
		while (m--) {
			cin >> z;
			if (z == 1) {
				cin >> x >> y;
				int px = nodes[x].p;
				int py = nodes[y].p;
				nodes[x].p = py;
				nodes[y].p = px;
				// cout << "x: " << x << " y:" << y << endl;
				// cout << "p: " << px << " " << py << endl;
				if (px != py) {
					if (nodes[px].lc == x)
						nodes[px].lc = y;
					else
						nodes[px].rc = y;
					if (nodes[py].lc == y)
						nodes[py].lc = x;
					else
						nodes[py].rc = x;
				}
				else {
					if (nodes[px].lc == x) {
						nodes[px].lc = y;
						nodes[px].rc = x;
					}
					else {
						nodes[px].lc = x;
						nodes[px].rc = y;
					}
				}
			}
			else if (z == 2) {
				cin >> x;
				while (nodes[x].lc != -1) {
					x = nodes[x].lc;
				}
				cout << x << endl;
			}
		}
	}
	system("pause");
	return 0;
}