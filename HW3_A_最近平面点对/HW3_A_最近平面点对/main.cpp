#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string.h>

using namespace std;

struct Node {
	double x, y; //should be double !!!
	Node(){}
	Node(double xx, double yy):x(xx), y(yy){}
	bool operator<(Node& n) const {
		return this->x < n.x;
	}
};

#define INF 0x3f3f3f3f
int T, N;
vector<Node> nodes;
double a, b;

double func(int start, int end) {
	//cout << "func: " << start << " " << end << endl;
	if (start == end)
		return INF;
	int mid = (start + end) >> 1;
	double mid_x = nodes[mid].x;
	double d = min(func(start, mid), func(mid + 1, end));
	vector<Node> tmp;
	int pl = start, pr = mid + 1;
	while (pl <= mid && pr <= end) {
		if (nodes[pl].y <= nodes[pr].y)
			tmp.push_back(nodes[pl++]);
		else
			tmp.push_back(nodes[pr++]);
	}
	while (pl <= mid)
		tmp.push_back(nodes[pl++]);
	while (pr <= end)
		tmp.push_back(nodes[pr++]);
	for (int i = start; i <= end; i++)
		nodes[i] = tmp[i - start];
	//compute crossed d.
	tmp.clear();
	for (int i = start; i <= end; i++) {
		if (abs(nodes[i].x - mid_x) >= d)
			continue;
		for (int j = tmp.size() - 1; j >= 0; j--) {
			double dx = nodes[i].x - tmp[j].x;
			double dy = nodes[i].y - tmp[j].y;
			if (dy >= d)
				break;
			d = min(d, sqrt(dx * dx + dy * dy));
		}
		tmp.push_back(nodes[i]);
	}
	return d;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		//init.
		nodes.clear();
		for (int i = 0; i < N; i++) {
			scanf("%lf%lf", &a, &b);
			nodes.push_back(Node(a, b));
		}
		sort(nodes.begin(), nodes.end());
		printf("%.6lf\n", func(0, nodes.size() - 1));
	}
	system("pause");
	return 0;
}