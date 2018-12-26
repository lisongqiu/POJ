#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<queue>
#include<string.h>

using namespace std;

struct Edge {
	int b, w;
	Edge() {}
	Edge(int bb, int ww):b(bb), w(ww){}
	bool operator<(const Edge& e) const {
		return this->w > e.w;
	}
};

bool cmp(const Edge& e1, const Edge& e2) {
	return e1.w < e2.w;
}

#define MAXN 101
int T;
int n, m;
int used[MAXN];
vector<vector<Edge> > edges(MAXN);
priority_queue<Edge> pq;

int main(){
	cin >> T;
	while (T--) {
		cin >> n >> m;
		//init.
		for (int i = 0; i <= n; i++)
			edges[i].clear();
		while (!pq.empty())
			pq.pop();
		memset(used, 0, sizeof(used));
		//input.
		int a, b, w;
		for (int i = 0; i < m; i++) {
			cin >> a >> b >> w;
			edges[a].push_back(Edge(b, w));
			edges[b].push_back(Edge(a, w));
		}
		for (int i = 1; i <= n; i++)
			sort(edges[i].begin(), edges[i].end(), cmp);
		//prim.
		pq.push(Edge(1, 0));
		int res = 0;
		bool unique = true;
		while (!pq.empty()) {
			Edge tmp = pq.top();
			pq.pop();
			if (used[tmp.b])
				continue;
			if (!pq.empty() && pq.top().b == tmp.b && pq.top().w == tmp.w) {
				unique = false;
				break;
			}
			res += tmp.w;
			used[tmp.b] = true;
			for (int i = 0; i < edges[tmp.b].size(); i++)
				if(!used[edges[tmp.b][i].b])
					pq.push(edges[tmp.b][i]);
		}
		if (unique)
			cout << res << endl;
		else
			cout << "Not Unique!" << endl;
	}
	system("pause");
	return 0;
}