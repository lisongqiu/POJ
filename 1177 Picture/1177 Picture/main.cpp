#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string.h>

using namespace std;

struct Line {
	int a, b, c;
	bool isFront;
	Line(){}
	Line(int aa, int bb, int cc, bool front):a(aa), b(bb), c(cc), isFront(front){}
	bool operator<(const Line& line) const {
		return this->c < line.c;
	}
};

struct Node {
	int l, r;
	Node *lc, *rc;
	int covers;
	int length;
};

#define MAXN 5010

int N;
vector<Line> rows;
vector<Line> cols;
int xs[2 * MAXN], ys[2 * MAXN];
int xCnt = 0, yCnt = 0;

int rnt = 0;

int nodeCnt = 0;
Node tree[4 * MAXN];

void buildTree(Node* root, int l, int r) {
	//cout << "buildTree: " << root - tree << " l:" << l << " r:" << r << endl;
	root->l = l;
	root->r = r;
	root->length = 0;
	root->covers = 0;
	if (l == r) {
		root->lc = NULL;
		root->rc = NULL;
		return;
	}
	int mid = (l + r) / 2;
	nodeCnt++;
	root->lc = tree + nodeCnt;
	buildTree(root->lc, l, mid);
	nodeCnt++;
	root->rc = tree + nodeCnt;
	buildTree(root->rc, mid + 1, r);
	return;
}

void insertEdge(Node* root, int l, int r, int* vals) {
	//cout << "insertEdge: " << root - tree << " root->l:" << root->l << " root->r:" << root->r << " l:" << l << " r:" << r << endl;
	if (root->l == l && root->r == r) {
		root->covers++;
		root->length = vals[r + 1] - vals[l];
		return;
	}
	int mid = (root->l + root->r) / 2;
	if (r <= mid)
		insertEdge(root->lc, l, r, vals);
	else if (l > mid)
		insertEdge(root->rc, l, r, vals);
	else {
		insertEdge(root->lc, l, mid, vals);
		insertEdge(root->rc, mid + 1, r, vals);
	}
	if (root->covers == 0)
		root->length = root->lc->length + root->rc->length;
	return;
}

void removeEdge(Node* root, int l, int r) {
	//cout << "removeEdge: " << root - tree << " l:" << l << " r:" << r << endl;
	if (root->l == l && root->r == r) {
		root->covers--;
		if (root->covers == 0) {
			if (root->l == root->r)
				root->length = 0;
			else
				root->length = root->lc->length + root->rc->length;
		}
		return;
	}
	int mid = (root->l + root->r) / 2;
	if (r <= mid)
		removeEdge(root->lc, l, r);
	else if (l > mid)
		removeEdge(root->rc, l, r);
	else {
		removeEdge(root->lc, l, mid);
		removeEdge(root->rc, mid + 1, r);
	}
	if (root->covers == 0)
		root->length = root->lc->length + root->rc->length;
	return;
}

int biSearch(int* ary, int val, int lp, int rp) {
	while (lp < rp) {
		int mid = (lp + rp) >> 1;
		if (val == ary[mid])
			return mid;
		else if (val < ary[mid])
			rp = mid - 1;
		else
			lp = mid + 1;
	}
	return lp;
}

int main() {
	scanf("%d", &N);
	int x1, y1, x2, y2;
	for (int i = 0; i < N; i++) {
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		rows.push_back(Line(x1, x2, y1, true)); //down
		rows.push_back(Line(x1, x2, y2, false));
		cols.push_back(Line(y1, y2, x1, true)); //left
		cols.push_back(Line(y1, y2, x2, false));
		xs[xCnt++] = x1;
		xs[xCnt++] = x2;
		ys[yCnt++] = y1;
		ys[yCnt++] = y2;
	}
	sort(rows.begin(), rows.end());
	sort(cols.begin(), cols.end());
	sort(xs, xs + xCnt);
	sort(ys, ys + yCnt);
	xCnt = unique(xs, xs + xCnt) - xs;
	yCnt = unique(ys, ys + yCnt) - ys;
	//debug.
	//cout << "xCnt: " << xCnt << " yCnt: " << yCnt << endl;
	//cols.
	int nodeCnt = 0;
	buildTree(tree, 0, yCnt - 1);
	for (int i = 0; i < cols.size(); i++) {
		int ia = biSearch(ys, cols[i].a, 0, yCnt - 1);
		int ib = biSearch(ys, cols[i].b, 0, yCnt - 1) - 1;
		//debug.
		//cout << "ia: " << ia << " ib:" << ib << endl;
		if (cols[i].isFront) {
			int old_len = tree->length;
			insertEdge(tree, ia, ib, ys);
			rnt += tree->length - old_len;
			//cout << "append: " << tree->length - old_len << endl;
		}
		else
			removeEdge(tree, ia, ib);
	}
	//rows.
	buildTree(tree, 0, xCnt - 1);
	for (int i = 0; i < rows.size(); i++) {
		int ia = biSearch(xs, rows[i].a, 0, xCnt - 1);
		int ib = biSearch(xs, rows[i].b, 0, xCnt - 1) - 1;
		//debug.
		//cout << "ia: " << ia << " ib:" << ib << endl;
		if (rows[i].isFront) {
			int old_len = tree->length;
			insertEdge(tree, ia, ib, xs);
			rnt += tree->length - old_len;
			//cout << "append: " << tree->length - old_len << endl;
		}
		else
			removeEdge(tree, ia, ib);
	}
	printf("%d\n", rnt * 2);
	system("pause");
	return 0;
}
