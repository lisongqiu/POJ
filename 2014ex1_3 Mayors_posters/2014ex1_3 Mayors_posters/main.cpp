#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;

#define MAXN 10010
#define MAXM 10000010

struct Poster {
	int l, r;
};

struct Node {
	int l, r;
	bool covered;
	Node *lc, *rc;
};

int C, N;
int nodeCnt;
int xs[2 * MAXN];
int hashed[MAXM];
Poster posters[MAXN];
Node tree[10 * MAXN];

void buildTree(Node* root, int l, int r) {
	root->l = l;
	root->r = r;
	root->covered = false;
	if (l == r) {
		root->lc = NULL;
		root->rc = NULL;
		return;
	}
	int mid = (root->l + root->r) / 2;
	nodeCnt++;
	root->lc = tree + nodeCnt;
	buildTree(root->lc, l, mid);
	nodeCnt++;
	root->rc = tree + nodeCnt;
	buildTree(root->rc, mid + 1, r);
	return;
}

bool insertNode(Node* root, int l, int r) {
	//cout << "insertNode: " << root - tree << " " << root->l << "|" << root->r << " " << l << " " << r << " covered: " << root->covered << endl;
	if (root->covered)
		return false;
	if (root->l == l && root->r == r) {
		root->covered = true;
		return true;
	}
	int mid = (root->l + root->r) / 2;
	bool res = false;
	if (mid >= r)
		res = insertNode(root->lc, l, r);
	else if (l > mid)
		res = insertNode(root->rc, l, r);
	else {
		bool lr = insertNode(root->lc, l, mid);
		bool rr = insertNode(root->rc, mid + 1, r);
		res = lr || rr;
	}
	if (root->lc->covered && root->rc->covered)
		root->covered = true;
	return res;
}
/*
template<typename T>
T* midFind(T* start, T* end, T val) {
	T* l = start;
	T* r = end - 1;
	while (l <= r) {
		//cout << "midFind: " << *l << " " << *r << endl;
		T* mid = l + (r - l) / 2;
		if (*mid == val)
			return mid;
		if (*mid < val)
			l = mid + 1;
		else
			r = mid - 1;
	}
	return l;
}
*/

int main() {
	scanf("%d", &C);
	while (C--) {
		scanf("%d", &N);
		nodeCnt = 0;
		int xCnt = 0;
		//input.
		for (int i = 1; i <= N; i++) {
			scanf("%d%d", &posters[i].l, &posters[i].r);
			xs[xCnt++] = posters[i].l;
			xs[xCnt++] = posters[i].r;
		}
		//prepare xs.
		sort(xs, xs + xCnt);
		xCnt = unique(xs, xs + xCnt) - xs;
		int realCnt = 0;
		for (int i = 0; i < xCnt; i++) {
			hashed[xs[i]] = realCnt;
			if (i != xCnt - 1 && xs[i + 1] - xs[i] == 1)
				realCnt++;
			else
				realCnt += 2;
		}
		//interval_tree.
		buildTree(tree, 0, realCnt - 1);
		//insert.
		int res = 0;
		for (int i = N; i >= 1; i--) {
			int leftIdx = hashed[posters[i].l];
			int rightIdx = hashed[posters[i].r];
			//debug.
			//cout << "idx: " << leftIdx << " " << rightIdx << endl;
			if (insertNode(tree, leftIdx, rightIdx))
				res++;
		}
		printf("%d\n", res);
	}
	system("pause");
	return 0;
}

/*
2
5
1 1
2 2
4 5
5 5
7 8
5
1 4
2 6
8 10
3 4
7 10
*/