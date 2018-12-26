#define _CRT_SECURE_NO_DEPRECATE

#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string.h>
#include<cmath>
#include<iomanip>
using namespace std;

struct Node {
	int x, y;
	Node(){}
	Node(int xx, int yy):x(xx), y(yy){}
};
struct Edge {
	int a, b;
	double w;
	Edge(){}
	Edge(int aa, int bb, double ww):a(aa), b(bb), w(ww){}
	bool operator<(const Edge& e) const{
		return this->w > e.w;
	}
};

#define MAXP 1000
int N;
int S, P;
vector<Node> nodes;
vector<double> lens;
priority_queue<Edge> edges;
int par[MAXP];

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
	cin >> N;
	while (N--) {
		cin >> S >> P;
		//init.
		nodes.clear();
		lens.clear();
		while (!edges.empty())
			edges.pop();
		for (int i = 0; i < P; i++)
			par[i] = i;
		//input.
		for (int i = 0; i < P; i++) {
			int a, b;
			cin >> a >> b;
			nodes.push_back(Node(a, b));
		}
		for (int i = 0; i < P; i++) {
			for (int j = i + 1; j < P; j++) {
				double w = sqrt(double((nodes[i].x - nodes[j].x)*(nodes[i].x - nodes[j].x)+ (nodes[i].y - nodes[j].y)*(nodes[i].y - nodes[j].y)));
				edges.push(Edge(i, j, w));
			}
		}
		int cnt = P - 1;
		while (cnt) {
			Edge tmp = edges.top();
			//cout << tmp.w << endl;
			edges.pop();
			int na = tmp.a;
			int nb = tmp.b;
			if (query(na, nb))
				continue;
			merge(na, nb);
			lens.push_back(tmp.w);
			cnt--;
		}	
		printf("%.2lf%\n", lens[P - S - 1]);
		//printf("%.2lf%\n", lens[S]);
	}
	system("pause");
	return 0;
}