#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

const int MAXN = 101;
const int INF = 0x3f3f3f3f;

int N, M, S;
double V;
int s, e;
double r1, c1, r2, c2;

struct Edge{
	int s, e;
	double r, c;
	Edge() {};
	Edge(int ss, int ee, double rr, double cc) :s(ss), e(ee), r(rr), c(cc) {};
	double compute(double num) {
		return (num - c)*r;
	}
};

vector<Edge> edges;
double dist[MAXN];

bool bellman_ford(int v) {
	for (int i = 0; i < N; i++)
		dist[i] = 0;
	dist[v] = V;
	for (int k = 1; k < N; k++) { //fewer than k pathes.
		bool changed = false;
		for (int i = 0; i < edges.size(); i++) {
			Edge tmp = edges[i];
			if (dist[tmp.e] < tmp.compute(dist[tmp.s])) {
				dist[tmp.e] = tmp.compute(dist[tmp.s]);
				changed = true;
			}
		}
		if (!changed)
			break;
	}
	for (int i = 0; i < edges.size(); i++) {
		Edge tmp = edges[i];
		if (dist[tmp.e] < tmp.compute(dist[tmp.s]))
			return true;
	}
	return false;
}

int main() {
	cin >> N >> M >> S >> V;
	for (int i = 0; i < M; i++) {
		cin >> s >> e >> r1 >> c1 >> r2 >> c2;
		edges.push_back(Edge(s, e, r1, c1));
		edges.push_back(Edge(e, s, r2, c2));
	}
	if (bellman_ford(S))
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
	//system("pause");
}
