#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<string>
#include<string.h>
#include<map>

using namespace std;

#define INF 0x3f3f3f3f
#define MAXN 33

struct Edge{
	int e;
	double r;
	Edge(){}
	Edge(int ee, double rr):e(ee), r(rr){}
};

int N, M;
vector<Edge> edges[MAXN];
map<string, int> names;
double maxVal[MAXN];
int cnts[MAXN];

bool SPFA(int k) {
	memset(maxVal, 0, sizeof(maxVal));
	memset(cnts, 0, sizeof(cnts));
	queue<int> que;
	while (!que.empty())
		que.pop();
	que.push(k);
	maxVal[k] = 1;
	cnts[k] = 1;
	while (!que.empty()) {
		int tmp = que.front();
		que.pop();
		//cout << "tmp: " << tmp << " val:" << maxVal[tmp] << endl;
		for (int i = 0; i < edges[tmp].size(); i++) {
			int newIdx = edges[tmp][i].e;
			double newVal = maxVal[tmp] * edges[tmp][i].r;
			if (newVal > maxVal[newIdx]) {
				maxVal[newIdx] = newVal;
				cnts[newIdx]++;
				que.push(newIdx);
				if (cnts[newIdx] > N)
					return true;				
			}
		}
	}
	return false;
}

int main() {
	int caseId = 0;
	while (cin >> N) {
		if (N == 0)
			break;
		//init.
		for (int i = 0; i < MAXN; i++)
			edges[i].clear();
		names.clear();
		string line;
		for (int i = 0; i < N; i++) {
			cin >> line;
			names[line] = i; // what fuck!!!
		}
		cin >> M;
		string s1, s2;
		double rate;
		for (int i = 0; i < M; i++) {
			cin >> s1 >> rate >> s2;
			edges[names[s1]].push_back(Edge(names[s2], rate));
		}
		bool is_ok = false;
		for (int i = 0; i < N; i++)
			if (SPFA(i)) {
				is_ok = true;
				break;
			}
		printf("Case %d: ", ++caseId);
		if (is_ok)
			printf("Yes\n");
		else
			printf("No\n");

	}
	system("pause");
	return 0;
}