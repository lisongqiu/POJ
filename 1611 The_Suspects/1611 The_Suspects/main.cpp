#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>
#include<string>

using namespace std;

#define MAXN 30001

int n, m;
int par[MAXN];
int buf[MAXN];

int findPar(int x) {
	if (par[x] != x)
		par[x] = findPar(par[x]);
	return par[x];
}

void merge(int a, int b) {
	par[findPar(b)] = findPar(a);
	return;
}

bool query(int a, int b) {
	return findPar(a) == findPar(b);
}

int main() {
	while (cin >> n >> m) {
		if (n == 0 && m == 0)
			break;
		//init par[];
		for (int i = 0; i < n; i++)
			par[i] = i;
		//input groups.
		for (int i = 0; i < m; i++) {
			int cnt;
			cin >> cnt;
			for (int j = 0; j < cnt; j++)
				cin >> buf[j];
			for (int j = 1; j < cnt; j++)
				merge(buf[0], buf[j]);
		}
		int cnt = 1;
		for (int i = 1; i < n; i++) {
			if (query(0, i))
				cnt++;
		}
		cout << cnt << endl;
	}
	system("pause");
	return 0;
}