#define _CRT_SECURE_NO_DEPRECATE

#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string>
#include<math.h>
#include<vector>

using namespace std;

struct Edge {
	int a, b;
	double w;
	Edge(){}
	Edge(int aa, int bb, double ww) :a(aa), b(bb), w(ww) {}
};

#define MAXN 110
int N;
int par[MAXN];
double x[MAXN];
double y[MAXN];

vector<Edge> edges;

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

bool cmp(const Edge& e1, const Edge& e2) {
	return e1.w < e2.w;
}

int main() {
	scanf("%d", &N);
	double a, b;
	for (int i = 1; i <= N; i++) {
		scanf("%lf%lf", &a, &b);
		par[i] = i;
		x[i] = a;
		y[i] = b;
	}
	for (int i = 1; i <= N - 1; i++) {
		for (int j = i + 1; j <= N; j++) {
			double weight = pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2);
			edges.push_back(Edge(i, j, weight));
		}
	}
	sort(edges.begin(), edges.end(), cmp);
	int cnt = 0;
	double res = 0;
	for (int i = 0; i < edges.size(); i++) {
		Edge tmp = edges[i];
		int na = tmp.a;
		int nb = tmp.b;
		if (query(na, nb))
			continue;
		merge(na, nb);
		res += sqrt(tmp.w);
		cnt++;
		if (cnt > N - 1)
			break;
	}
	printf("%.2f\n", res);
	system("pause");
	return 0;
}