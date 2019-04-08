#include <algorithm>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

#define MAXN 110

int N;
vector<int> edges[MAXN];
vector<int> reverses[MAXN];
int sccs[MAXN];
int idx = 0;
vector<int> orders;
int inDegrees[MAXN];
int outDegrees[MAXN];

void dfs(int s) {
	if (sccs[s])
		return;
	sccs[s] = true;
	for (int i = 0; i < edges[s].size(); i++)
		dfs(edges[s][i]);
	orders.push_back(s);
	return;
}

bool redfs(int s) {
	if (sccs[s] != -1)
		return false;
	sccs[s] = idx;
	for (int i = 0; i < reverses[s].size(); i++)
		redfs(reverses[s][i]);
	return true;
}

int main() {
	cin >> N;
	int a;
	for (int i = 1; i <= N; i++) {
		while (cin >> a) {
			if (a == 0)
				break;
			edges[i].push_back(a);
			reverses[a].push_back(i);
		}
	}
	memset(sccs, 0, sizeof(sccs));
	for (int i = 1; i <= N; i++)
		dfs(i);
	idx = 0;
	memset(sccs, -1, sizeof(sccs));
	for (int i = N - 1; i >= 0; i--)
		if (redfs(orders[i]))
			idx++;
	memset(inDegrees, 0, sizeof(inDegrees));
	memset(outDegrees, 0, sizeof(outDegrees));
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < edges[i].size(); j++) {
			if (sccs[edges[i][j]] != sccs[i]) { //note here!
				inDegrees[sccs[edges[i][j]]]++;
				outDegrees[sccs[i]]++;
			}
		}
	}
	int zeroIn = 0, zeroOut = 0;
	for (int i = 0; i < idx; i++) {
		if (inDegrees[i] == 0)
			zeroIn++;
		if (outDegrees[i] == 0)
			zeroOut++;
	}
	if (idx == 1)  // NOTE HERE!!!!!
		cout << 1 << endl << 0 << endl;
	else {
		cout << zeroIn << endl;
		cout << max(zeroIn, zeroOut) << endl;
	}
	system("pause");
	return 0;
}
