#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstdio>

using namespace std;

const int MAXN = 30010;
const int INF = 0x3f3f3f;

struct Edge {
	int end;
	int weight;
};

bool operator<(const Edge& a, const Edge& b) {
	return a.weight > b.weight;
}

int N, M;
int a, b, c;
vector<vector<Edge> > edges;
priority_queue<Edge> pq;
bool used[MAXN] = { 0 };

int main() {
	scanf("%d%d", &N, &M);
	edges.clear();
	edges.resize(N+1);
	Edge p;
	for (int i = 0; i < M; i++) {
		scanf("%d%d%d", &a, &b, &c);
		p.end = b;
		p.weight = c;
		edges[a].push_back(p);
	}
	p.end = 1;
	p.weight = 0;
	pq.push(p);
	while (!pq.empty()) {
		p = pq.top();
		pq.pop();
		if (used[p.end])
			continue;
		used[p.end] = true;
		if (p.end == N) {
			std::cout << p.weight << std::endl;
			break;
		}
		for (int i = 0; i < edges[p.end].size(); i++) {
			Edge tmp = edges[p.end][i];
			if (used[tmp.end])
				continue;
			tmp.weight += p.weight;
			pq.push(tmp);
		}
	}
	return 0;
}
