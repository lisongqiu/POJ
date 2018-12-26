#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<algorithm>
#include<vector>

using namespace std;

struct Node {
	int l, r;
	vector<int> vec;
	Node *lc, *rc;
};

#define MAXN 100010

int N, M;
int	a[MAXN];
int nodeCnt = 0;
Node tree[4 * MAXN + 50];

void buildTree(Node* root, int l, int r) {
	root->l = l;
	root->r = r;
	root->vec.clear();
	if (l == r) {
		root->vec.push_back(a[l]);
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
	int lp = 0, rp = 0;
	while (lp < root->lc->vec.size() && rp < root->rc->vec.size()) {
		if (root->lc->vec[lp] < root->rc->vec[rp])
			root->vec.push_back(root->lc->vec[lp++]);
		else
			root->vec.push_back(root->rc->vec[rp++]);
	}
	while (lp < root->lc->vec.size())
		root->vec.push_back(root->lc->vec[lp++]);
	while (rp < root->rc->vec.size())
		root->vec.push_back(root->rc->vec[rp++]);
	return;
}

int query(Node* root, int l, int r, int k) {
	if (root->l == l && root->r == r) {
		int lp = 0, rp = root->vec.size(), mid;
		while (lp < rp) {
			mid = (lp + rp) >> 1;
			if (root->vec[mid] <= k)
				lp = mid + 1;
			else if (root->vec[mid] > k)
				rp = mid;
		}
		return lp;
	}
	int mid = (root->l + root->r) >> 1;
	int res = 0;
	if (r <= mid)
		res += query(root->lc, l, r, k);
	else if (l > mid)
		res += query(root->rc, l, r, k);
	else {
		res += query(root->lc, l, mid, k);
		res += query(root->rc, mid + 1, r, k);
	}
	return res;
}

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
		scanf("%d", a + i);
	buildTree(tree, 1, N);
	sort(a + 1, a + N + 1);
	int l, r, k;
	while (M--) {
		scanf("%d%d%d", &l, &r, &k);
		int lp = 1, rp = N;
		while (lp < rp) {
			int mid = (lp + rp) >> 1;
			int cnt = query(tree, l, r, a[mid]);
			//printf("lp:%d, rp:%d, mid:%d, a[mid]:%d, cnt:%d\n", lp, rp, mid, a[mid], cnt);
			if (cnt < k)
				lp = mid + 1;
			else
				rp = mid;
		}
		printf("%d\n", a[lp]);
	}
	system("pause");
	return 0;
}

/*
#######################
input
#######################

7 3
1 5 2 6 3 7 4
2 5 3
4 4 1
1 7 3

#######################
output
#######################

5
6
3

*/
