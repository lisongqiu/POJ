#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string.h>

using namespace std;

struct Edge {
	int a, b;
	Edge(){}
	Edge(int aa, int bb) :a(aa), b(bb) {}
	bool operator<(const Edge& e) const {
		if (this->a != e.a)
			return this->a < e.a;
		else
			return this->b < e.b;
	}
};

struct Node {
	int l, r;
	Node *lc, *rc;
	int cnt;
};

#define MAXN 1010
int T, N, M, K;
int caseIdx = 1;
vector<Edge> edges;

int nodeCnt = 0;
Node tree[MAXN * 4];

void buildTree(Node* root, int l, int r) {
	root->l = l;
	root->r = r;
	root->cnt = 0;
	if (l == r) {
		root->lc = NULL;
		root->rc = NULL;
		return;
	}
	int mid = (l + r) >> 1;
	nodeCnt++;
	root->lc = tree + nodeCnt;
	buildTree(root->lc, l, mid);
	nodeCnt++;
	root->rc = tree + nodeCnt;
	buildTree(root->rc, mid + 1, r);
	return;
}

long long queryNode(Node* root, int val) {
	if (root->l == root->r) {
		if (root->l != val) {
			cout << "Insert Error!" << endl;
			return 0;
		}
		return 0;
	}
	int mid = (root->l + root->r) >> 1;
	if (val <= mid)
		return queryNode(root->lc, val) + root->rc->cnt;
	else
		return queryNode(root->rc, val);
}

void insertNode(Node* root, int val) {
	if (root->l == root->r) {
		if (root->l != val) {
			cout << "Insert Error!" << endl;
			return;
		}
		root->cnt++;
		return;
	}
	int mid = (root->l + root->r) >> 1;
	if (val <= mid)
		insertNode(root->lc, val);
	else
		insertNode(root->rc, val);
	root->cnt++;
	return;
}

int main() {
	scanf("%d", &T);
	while (caseIdx <= T) {
		//init.
		nodeCnt = 0;
		edges.clear();
		//input.
		scanf("%d%d%d", &N, &M, &K);
		int a, b;
		for (int i = 0; i < K; i++) {
			scanf("%d%d", &a, &b);
			edges.push_back(Edge(a, b));
		}
		sort(edges.begin(), edges.end());
		//interval tree.
		buildTree(tree, 1, M);
		long long rnt = 0; //long long is necessary !!
		for (int i = 0; i < K; i++) {
			int v = edges[i].b;
			rnt += queryNode(tree, v);
			insertNode(tree, v);
		}
		printf("Test case %d: %lld\n", caseIdx++, rnt);
	}
	system("pause");
	return 0;
}