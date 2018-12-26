#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<math.h>

using namespace std;

struct Edge {
	int a, b, w;
	Edge(){}
	Edge(int aa, int bb, int ww) :a(aa), b(bb), w(ww) {}
};

bool cmp(const Edge& e1, const Edge& e2) {
	return e1.w < e2.w;
}

#define MAXN 1010

vector<Edge> edges;
int N, M;
int par[MAXN];

int getPar(int a) {
	if (par[a] == a)
		return a;
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

bool query(int a, int b) {
	return getPar(a) == getPar(b);
}

int main() {
	cin >> N >> M;
	//init.
	for (int i = 1; i <= N; i++)
		par[i] = i;
	int a, b, w;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> w;
		edges.push_back(Edge(a, b, w));
	}
	sort(edges.begin(), edges.end(), cmp);
	vector<Edge> res;
	int maxLen = 0;
	for (int i = 0; i < M; i++) {
		Edge tmp = edges[i];
		if (query(tmp.a, tmp.b))
			continue;
		res.push_back(tmp);
		maxLen = max<int>(maxLen, tmp.w);
		merge(tmp.a, tmp.b);
	}
	//output.
	cout << maxLen << endl;
	cout << res.size() << endl;
	for (int i = 0; i < res.size(); i++)
		cout << res[i].a << " " << res[i].b << endl;
	system("pause");
	return 0;
}