#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

#define MAXN 50001

int n, m;
int par[MAXN];

int getPar(int a) {
	if (par[a] != a)
		par[a] = getPar(par[a]);
	return par[a];
}

void merge(int a, int b) {
	int pa = getPar(a);
	int pb = getPar(b);
	if (pa == pb)
		return;
	par[pa] = pb;
	return;
}

int main() {
	int caseN = 0;
	while (cin >> n >> m) {
		caseN++;
		if (n == 0 && m == 0)
			break;
		//init par array.
		for (int i = 1; i <= n; i++)
			par[i] = i;
		//merge.
		int a, b;
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &a, &b);
			merge(a, b);
		}
		//count.
		int cnt = 0;
		vector<int> used;
		for (int i = 1; i <= n; i++) {
			int pi = getPar(i);
			bool found = false;
			for(int j=0;j<used.size();j++)
				if (pi == used[j]) {
					found = true;
					break;
				}
			if (!found) {
				used.push_back(pi);
				cnt++;
			}
		}
		cout << "Case " << caseN << ": " << cnt << endl;
	}
	system("pause");
	return 0;
}