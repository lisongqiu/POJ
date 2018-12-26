#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<iomanip>

using namespace std;

struct Node {
	double l, r;
	Node *lc, *rc;
	int cover;
	double len;
};
struct Line {
	double x;
	double l, r;
	bool isLeft;
	bool operator<(const Line& l) const {
		return this->x < l.x;
	}
};

#define MAXN 210
int N;
int nodeCnt = 0;
int yCnt = 0;
int lc = 0;
Node tree[MAXN*2];
double y[MAXN];
Line lines[MAXN];

void build(Node* root, int l, int r) {
	root->l = l;
	root->r = r;
	root->cover = 0;
	root->len = 0;
	if (l == r)
		return;
	nodeCnt++;
	root->lc = tree + nodeCnt;
	nodeCnt++;
	root->rc = tree + nodeCnt;
	int mid = (root->l + root->r) / 2;
	build(root->lc, l, mid);
	build(root->rc, mid + 1, r);
	return;
}

void insert(Node* root, int l, int r) {
	//cout << "insert: " << l << " " << r << " IDX:" << root - tree << " L:" << root->l << " R:" << root->r << " COVER:" << root->cover << " LEN:" << root->len << endl;
	if (root->l == l && root->r == r) {
		/*
		if(!root->cover)
			root->len += y[r+1]-y[l];
		*/
		root->len = y[r+1]-y[l];
		root->cover++;
		//cout << "end- " << " IDX:" << root - tree << " L:" << root->l << " R:" << root->r << " COVER:" << root->cover << " LEN:" << root->len << endl;
		return;
	}
	int mid = (root->l + root->r) / 2;
	if (r <= mid)
		insert(root->lc, l, r);
	else if (l > mid)
		insert(root->rc, l, r);
	else {
		insert(root->lc, l, mid);
		insert(root->rc, mid + 1, r);
	}
	if (!root->cover)
		root->len = root->lc->len + root->rc->len;
	//cout << "end- " << " IDX:" << root - tree << " L:" << root->l << " R:" << root->r << " COVER:" << root->cover << " LEN:" << root->len << endl;
	return;
}

void detach(Node* root, int l, int r) {
	//cout << "detach: " << l << " " << r << " IDX:" << root - tree << " L:" << root->l << " R:" << root->r << " COVER:" << root->cover << " LEN:" << root->len << endl;
	if (root->l == l && root->r == r) {
		root->cover--;
		if (!root->cover) { //here.!!!
			if (l == r)
				root->len = 0;
			else
				root->len = root->lc->len + root->rc->len;
		}
		//cout << "end- " << " IDX:" << root - tree << " L:" << root->l << " R:" << root->r << " COVER:" << root->cover << " LEN:" << root->len << endl;
		return;
	}
	int mid = (root->l + root->r) / 2;
	if (r <= mid)
		detach(root->lc, l, r);
	else if (l > mid)
		detach(root->rc, l, r);
	else {
		detach(root->lc, l, mid);
		detach(root->rc, mid + 1, r);
	}
	if (!root->cover)
		root->len = root->lc->len + root->rc->len;
	//cout << "end- " << " IDX:" << root - tree << " L:" << root->l << " R:" << root->r << " COVER:" << root->cover << " LEN:" << root->len << endl;
	return;
}
/*
int findIdx(double val) {
	int l = 0, r = yCnt;
	while (l < r) {
		int mid = (l + r) / 2;
		if (y[mid] == val)
			return mid;
		if (y[mid] < val)
			l = mid + 1;
		else
			r = mid;
	}
	return l;
}
*/
template<class F, class T>
F findIdx(F s, F e, T val) {
	F L = s;
	F R = e;
	while (L <= R) {
		F mid = L + (R - L) / 2;
		if (!(*mid < val || val < *mid))
			return mid;
		else if (val < *mid)
			R = mid - 1;
		else
			L = mid + 1;
	}
	return e;
}

int main() {
	int caseIdx = 1;
	while (cin >> N) {
		if (N == 0)
			break;
		nodeCnt = 0;
		yCnt = 0;
		lc = 0;
		double x1, x2, y1, y2;
		for (int i = 0; i < N; i++) {
			cin >> x1 >> y1 >> x2 >> y2;
			lines[lc].x = x1;
			lines[lc].l = y1;
			lines[lc].r = y2;
			lines[lc].isLeft = true;
			lc++;
			lines[lc].x = x2;
			lines[lc].l = y1;
			lines[lc].r = y2;
			lines[lc].isLeft = false;
			lc++;
			y[yCnt++] = y1;
			y[yCnt++] = y2;
		}
		//cout << "end of input" << endl;
		sort(lines, lines + lc);
		sort(y, y + yCnt);
		yCnt = unique(y, y + yCnt) - y;
		build(tree, 0, yCnt - 1 - 1);
		//cout << "end of building" << endl;
		double res = 0;
		for (int i = 0; i < lc - 1; i++) {
			//cout << "  i:" << i << " x:" << lines[i].x << " l:" << lines[i].l << " r:" << lines[i].r << endl;
			int leftIdx = findIdx(y, y + yCnt, lines[i].l) - y;
			int rightIdx = findIdx(y, y + yCnt, lines[i].r) - y;
			if (lines[i].isLeft)
				insert(tree, leftIdx, rightIdx - 1);
			else
				detach(tree, leftIdx, rightIdx - 1);
			res += tree->len * (lines[i + 1].x - lines[i].x);
		}
		//cout << "end of scanning" << endl;
		cout << "Test case #" << caseIdx++ << endl;
		printf("Total explored area: %.2f\n\n", res);
	}
	system("pause");
	return 0;
}