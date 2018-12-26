#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<math.h>

using namespace std;

#define MAXN 201000

struct Node {
	int x, y;
	Node() {}
	Node(int xx, int yy):x(xx), y(yy){}
};

int N, D;
int par[MAXN];
int vis[MAXN];
vector<Node> nodes;

bool isNear(int a, int b) {
	double distance = pow(nodes[a].x - nodes[b].x, 2) + pow(nodes[a].y - nodes[b].y, 2);
	return distance <= pow(D, 2);
}

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
	cin >> N >> D;
	int x, y;
	nodes.clear();
	nodes.push_back(Node());
	for (int i = 1; i <= N; i++) {
		scanf("%d%d", &x, &y);
		nodes.push_back(Node(x, y));
		par[i] = i;
		vis[i] = 0;
	}
	char op;
	int a, b;
	//while (scanf(" %c", &op)==1) {
	while(cin>>op){
		//cout << "OPPPPP: " << op << endl;
		if (op == 'O') {
			scanf("%d", &a);
			vis[a] = 1;
			for (int i = 1; i <= N; i++) {
				if (i!=a && vis[i] && isNear(a, i))
					merge(a, i);
			}
		}
		if(op=='S') {
			scanf("%d%d", &a, &b);
			if (query(a, b))
				cout << "SUCCESS" << endl;
			else
				cout << "FAIL" << endl;
		}
	}
	system("pause");
	return 0;
}