#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<math.h>
#include<string.h>

using namespace std;

#define INF 0x3f3f3f3f
#define MAXN 1010

struct Node {
	int x, y;
	Node() {}
	Node(int xx, int yy) :x(xx), y(yy){}
};

bool cmp(Node& a, Node& b) {
	return a.x < b.x;
}

int T, N;
vector<Node> nodes;

double func(int s, int e) {
	if (s == e)
		return INF;
	int mid = (s + e) / 2;
	double mid_x = nodes[mid].x;
	double min_dist = min<double>(func(s, mid), func(mid + 1, e));
	vector<Node> vec;
	int pl = s, pr = mid + 1;
	while (pl <= mid && pr <= e) {
		if (nodes[pl].y <= nodes[pr].y) {
			vec.push_back(nodes[pl]);
			pl++;
		}
		else {
			vec.push_back(nodes[pr]);
			pr++;
		}
	}
	while (pl <= mid) {
		vec.push_back(nodes[pl]);
		pl++;
	}
	while (pr <= e) {
		vec.push_back(nodes[pr]);
		pr++;
	}
	for (int i = 0; i < vec.size(); i++) {
		nodes[s + i] = vec[i];
	}
	vec.clear();
	for (int i = s; i <= e; i++) {
		if (abs(nodes[i].x - mid_x) >= min_dist)
			continue;
		for (int j = vec.size() - 1; j >= 0; j--) {
			if (abs(nodes[i].y - vec[j].y) >= min_dist)
				break;
			double tmp_dist = sqrt(pow(nodes[i].x - vec[j].x, 2) + pow(nodes[i].y - vec[j].y, 2));
			min_dist = min<double>(min_dist, tmp_dist);
		}
		vec.push_back(nodes[i]);
	}
	return min_dist;
}

int main() {
	scanf("%d", &T);
	int x, y;
	while (T--) {
		nodes.clear();
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d%d", &x, &y);
			nodes.push_back(Node(x, y));
		}
		sort(nodes.begin(), nodes.end(), cmp);
		printf("%.6lf\n", func(0, nodes.size() - 1));
	}
	system("pause");
	return 0;
}