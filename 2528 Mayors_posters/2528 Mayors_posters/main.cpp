#define _CRT_SECURE_NO_DEPRECATE

#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<math.h>

using namespace std;

struct Node {
	int l, r;
	bool used;
	int lc, rc;
	Node(){}
};

#define MAXN 10100
#define MAXM 10000010
int poster[MAXN][2];
int x[20200];
int hashed[MAXM];
Node tree[1000001];

int idxCnt = 0;

void build(int root, int l, int r) {
	//
	//cout << "build: " << root << " " << l << " " << r << endl;
	tree[root].l = l;
	tree[root].r = r;
	tree[root].used = false;
	if (l == r)
		return;
	idxCnt++;
	tree[root].lc = idxCnt;
	idxCnt++;
	tree[root].rc = idxCnt;
	int mid = (l + r) / 2;
	build(tree[root].lc, l, mid);
	build(tree[root].rc, mid + 1, r);
}

bool post(int root, int l, int r) {
	//
	//cout << "post: " << root << " " << l << " " << r << " used:" << tree[root].used << endl;
	if (tree[root].used)
		return false;
	if (tree[root].l == l && tree[root].r == r) {
		tree[root].used = true;
		return true;
	}
	int mid = (tree[root].l + tree[root].r) / 2;
	bool res;
	if (r <= mid)
		res = post(tree[root].lc, l, r);
	else if (l > mid)
		res = post(tree[root].rc, l, r);
	else {
		bool r1 = post(tree[root].lc, l, mid);
		bool r2 = post(tree[root].rc, mid + 1, r);
		res = r1 || r2;
	}
	if (tree[tree[root].lc].used && tree[tree[root].rc].used)
		tree[root].used = true;
	return res;
}

int main() {
	int T, n;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		int nCount = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &poster[i][0], &poster[i][1]);
			x[nCount++] = poster[i][0];
			x[nCount++] = poster[i][1];
		}
		//sort the poster.
		sort(x, x + nCount);
		/*
		//build hash.
		int ptr = 1, old = 0;
		int intervalID = 0;
		hashed[ordered[0]] = intervalID;
		while (ptr < 2 * n) {
			if (ordered[ptr] == ordered[old]) { //eliminate the duplicate ones.
				ptr++;
				continue;
			}
			if (ordered[ptr] - ordered[old] == 1)
				intervalID += 1;
			else
				intervalID += 2;
			hashed[ordered[ptr]] = intervalID;
			old = ptr;
			ptr++;
		}
		*/
		nCount = unique(x, x + nCount) - x;
		int intervalId = 0;
		for (int i = 0; i < nCount; i++) {
			hashed[x[i]] = intervalId;
			if (i < nCount - 1) {
				if (x[i + 1] - x[i] == 1)
					intervalId++;
				else
					intervalId += 2;
			}
		}
		//
		//cout << "intervalID: " << intervalID << endl;
		//build tree.
		//idxCnt = 0;
		build(0, 0, intervalId);
		//add poster.
		int res = 0;
		for (int i = n - 1; i >= 0; i--) {
			int l = hashed[poster[i][0]];
			int r = hashed[poster[i][1]];
			//
			//cout << "p" << i << ": " << l << " " << r << endl;
			if (post(0, l, r)) {
				//
				//cout << "returned true" << endl;
				res++;
			}
			//
			//cout << "returned false" << endl;
		}
		printf("%d\n", res);
	}
	system("pause");
	return 0;
}