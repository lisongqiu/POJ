#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

struct Node {
	int l, r;
	Node *lc, *rc;
	int free;
};

#define MAXN 50010
int N, M;

int nodeCnt = 0;
Node tree[MAXN * 4];

void buildTree(Node* root, int l, int r) {
	root->l = l;
	root->r = r;
	root->free = l;
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

void removeNode(Node* root, int l, int r) {
	if (root->l == l && root->r == r) {
		root->free = root->l;
		return;
	}
	int mid = (root->l + root->r) >> 1;
	if (r <= mid)
		removeNode(root->lc, l, r);
	else if (l > mid)
		removeNode(root->rc, l, r);
	else {
		removeNode(root->lc, l, mid);
		removeNode(root->rc, mid + 1, r);
	}
	root->free = root->lc->free;
	return;
}

int insertNode(Node* root, int width) {
	int mid = (root->l + root->r) >> 1;
	
}

int main() {
	scanf("%d%d", &N, &M);
	int op, a, b;
	while (M--) {
		scanf("%d", &op);
		if (op==1) {
			scanf("%d", &a);
			printf("%d\n", insertNode(tree, a));
		}
		else {
			scanf("%d%d", &a, &b);
			removeNode(tree, a, b);
		}
	}
	system("pause");
	return 0;
}