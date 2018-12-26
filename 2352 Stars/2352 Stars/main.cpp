#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

struct Node {
	int l, r;
	Node *lc, *rc;
	int cnt;
};

#define MAXN 15010
Node tree[MAXN * 4];
int nodeCnt = 0;
int N, xCnt;
int xs[MAXN], ys[MAXN], uniX[MAXN];
int rnt[MAXN];

void buildTree(Node* root, int l, int r) {
	//cout << "BuildTree: " << root - tree << " " << l << " " << r << endl;
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

int biFind(int* ary, int val, int l, int r) {
	while (l < r) {
		int mid = (l + r) >> 1;
		if (val == ary[mid])
			return mid;
		else if (val < ary[mid])
			r = mid - 1;
		else
			l = mid + 1;
	}
	return l;
}

void insertNode(Node* root, int val) {
	if (root->l == root->r) {
		if (root->l != val) {
			//cout << "Insert Error!" << " root->l:" << root->l << " root->r:" << root->r << " val:" << val << endl;
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

int findNode(Node* root, int val) {
	//cout << "findNode: " << root->l << " " << root->r << " val:" << val << endl;
	if (root->l == root->r) {
		if (root->l != val) {
			//cout << "Find Error!" << "root:" << root - tree << " root->l:" << root->l << " root->r:" << root->r << " val:" << val << endl;
			return 0;
		}
		return root->cnt;
	}
	int mid = (root->l + root->r) >> 1;
	if (val <= mid) {
		//cout << "go left!" << root->lc->l << " " << root->lc->r << endl;
		return findNode(root->lc, val);
	}
	else {
		//cout << "go right!" << root->rc->l << " " << root->rc->r << endl;
		return findNode(root->rc, val) + root->lc->cnt;
	}
}

int main() {
	scanf("%d", &N);
	memset(rnt, 0, sizeof(rnt));
	for (int i = 0; i < N; i++)
		scanf("%d%d", &xs[i], &ys[i]);
	memcpy(uniX, xs, sizeof(int)*N);
	sort(uniX, uniX + N);
	xCnt = unique(uniX, uniX + N) - uniX;
	buildTree(tree, 0, xCnt - 1);
	for (int i = 0; i < N; i++) {
		int idx = biFind(uniX, xs[i], 0, xCnt);
		int level = findNode(tree, idx);
		rnt[level]++;
		insertNode(tree, idx);
	}
	//output.
	for (int i = 0; i < N; i++) {
		printf("%d\n", rnt[i]);
	}
	system("pause");
	return 0;
}