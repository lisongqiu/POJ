#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<algorithm>
#include<vector>

using namespace std;

#define MAXN 200010

int N, M;
int nCount = 0;
int starts[MAXN];
int endz[MAXN];
int lowbit[MAXN];
int c[MAXN] = { 0 };
bool used[MAXN] = { false };
vector<vector<int> > edges;

int sum(int k) {
	int rnt = 0;
	while (k > 0) {
		rnt += c[k];
		k -= lowbit[k];
	}
	return rnt;
}

void add(int k, int val) {
	while (k <= nCount) {
		c[k] += val;
		k += lowbit[k];
	}
	return;
}

void dfs(int root) {
	starts[root] = ++nCount;
	for (int i = 0; i < edges[root].size(); i++)
		dfs(edges[root][i]);
	endz[root] = ++nCount;
	return;
}

int main() {
	scanf("%d", &N);
	int a, b;
	char op;
	for (int i = 0; i <= N; i++)
		edges.push_back(vector<int>());
	for (int i = 0; i < N - 1; i++) {
		scanf("%d%d", &a, &b);
		edges[a].push_back(b);
	}
	//mark the start and end flags.
	dfs(1);
	//init.
	for (int i = 1; i <= nCount; i++)
		lowbit[i] = i & (-i);
	for (int i = 1; i <= N; i++)
		used[i] = true;
	for (int i = 1; i <= nCount; i++)
		c[i] = lowbit[i];
	scanf("%d", &M);
	while (M--) {
		scanf(" %c %d", &op, &a);
		int tmpStart = starts[a], tmpEnd = endz[a];
		//cout << "tmpStart: " << tmpStart << " tmpEnd:" << tmpEnd << endl;
		if (op == 'Q') {
			int res = sum(tmpEnd) - sum(tmpStart - 1);
			//cout << "sumEnd: " << sum(tmpEnd) << " tmpStart: " << sum(tmpStart - 1) << endl;
			printf("%d\n", res / 2);
		}
		else {
			if (used[a]) {
				add(tmpStart, -1);
				add(tmpEnd, -1);
			}
			else {
				add(tmpStart, 1);
				add(tmpEnd, 1);
			}
			used[a] = !used[a];
		}
	}
	system("pause");
	return 0;
}
