#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string.h>

using namespace std;

#define MAXN 100010
int N1, N2, D;
vector<int> edges[MAXN];
int cnt[MAXN];

int topoSort(int pt) {
	queue<int> que[2];
	int tmp[MAXN];
	bool used[MAXN];
	memcpy(tmp, cnt, sizeof(cnt));
	memset(used, 0, sizeof(used));
	//init.
	for (int i = 1; i <= N1; i++)
		if (tmp[i] == 0) {
			used[i] = true;
			que[0].push(i);
		}
	for (int i = N1 + 1; i <= N1 + N2; i++)
		if (tmp[i] == 0) {
			used[i] = true;
			que[1].push(i);
		}
	int rtn = 1;
	while (!que[pt].empty() || !que[1-pt].empty()) {
		while (!que[pt].empty()) {
			int t = que[pt].front();
			que[pt].pop();
			for (int i = 0; i < edges[t].size(); i++) {
				int nt = edges[t][i];
				if (used[nt])
					continue;
				tmp[nt]--;
				if (0 == tmp[nt]) {
					used[nt] = true;
					if (nt <= N1)
						que[0].push(nt);
					else
						que[1].push(nt);
				}
			}
		}
		pt = 1 - pt;
		rtn++;
	}
	return rtn;
}

int main() {
	while (~scanf("%d%d%d", &N1, &N2, &D) && !(N1 == 0 && N2 == 0 && D == 0)) {
		//init.
		for (int i = 1; i <= N1 + N2; i++) {
			edges[i].clear();
			cnt[i] = 0;
		}
		//input.
		int a, b;
		for (int i = 0; i < D; i++) {
			scanf("%d%d", &a, &b);
			cnt[a]++;
			edges[b].push_back(a);
		}
		cout << min(topoSort(0), topoSort(1)) << endl;
	}
	system("pause");
	return 0;
}