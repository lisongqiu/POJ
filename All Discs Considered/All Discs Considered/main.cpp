#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<string.h>

using namespace std;

#define MAXN 50010
#define MAXD 100010

int N1, N2, D;
vector<int> edges[MAXN * 2];
int cnt[MAXN * 2];

int topoSort(int color) {
	int lowerBound[2] = { 1 + N1 * color, 1 + N1 * (1 - color) };
	int upperBound[2] = { N1 + N2 * color, N1 + N2 * (1 - color) };
	int tmpCnt[MAXN * 2];
	int used[MAXN * 2];
	memset(used, 0, sizeof(used));
	memcpy(tmpCnt, cnt, sizeof(cnt));
	int res = 1, ptr = 0;
	queue<int> q[2];
	for(int i=1;i<=N1+N2;i++)
		if (tmpCnt[i] == 0) {
			q[ptr].push(i);
			used[i] = true;
		}
	while (!q[ptr].empty() || !q[1-ptr].empty()) {
		while (!q[ptr].empty()) {
			int tmp = q[ptr].front();
			q[ptr].pop();
			if (tmp >= lowerBound[ptr] && tmp <= upperBound[ptr]) {
				for (int i = 0; i < edges[tmp].size(); i++) {
					int nextIdx = edges[tmp][i];
					tmpCnt[nextIdx]--;
					if (!used[nextIdx] && tmpCnt[nextIdx] == 0) {
						used[nextIdx] = true;
						q[ptr].push(nextIdx);
					}
				}
			}
			else
				q[1 - ptr].push(tmp);
		}
		ptr = 1 - ptr;
		res++;
	}
	return res;
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