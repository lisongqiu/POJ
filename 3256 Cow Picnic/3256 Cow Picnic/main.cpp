#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

const int MAXK = 1001;
const int MAXN = 10001;
int K, N, M;
vector<int> edges[MAXK];
vector<int> starts;
bool flags[MAXN] = { true };

void spread(int v) {
	queue<int> que;
	bool tmp_flags[MAXN];
	for (int i = 1; i <= N; i++)
		tmp_flags[i] = 0;
	que.push(v);
	while (!que.empty()) {
		int tmp = que.front();
		que.pop();
		if (tmp_flags[tmp])
			continue;
		tmp_flags[tmp] = true;
		for (int i = 0; i < edges[tmp].size(); i++) {
			que.push(edges[tmp][i]);
		}
	}
	for (int i = 1; i <= N; i++) 
		flags[i] = flags[i] && tmp_flags[i];
	return;
}

int main() {
	cin >> K >> N >> M;
	int a, b;
	for (int i = 0; i < K; i++) {
		cin >> a;
		starts.push_back(a);
	}
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		edges[a].push_back(b);
	}
	for (int i = 1; i <= N; i++)
		flags[i] = true;
	for (int i = 0; i < starts.size(); i++) {
		spread(starts[i]);
	}
	int cnt = 0;
	for (int i = 1; i <= N; i++) {
		if (flags[i] == true) {
			cnt++;
		}
	}
	cout << cnt << endl;
	system("pause");
}
