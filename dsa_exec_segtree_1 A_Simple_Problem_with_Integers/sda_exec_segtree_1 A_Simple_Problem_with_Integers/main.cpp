#define _CRT_SECURE_NO_DEPRECATE

#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

struct Node {
	int a, b;
	long long sum;
	long long buffer;
	Node *lc, *rc;
};

#define MAXN 100010

int N, Q;
int A[MAXN];
int nodeCnt = 0;
Node tree[4 * MAXN];

void buildTree(Node* root, int a, int b) {
	//cout << "BuildTree: " << root - tree << " " << a << " " << b << endl;
	root->a = a;
	root->b = b;
	root->sum = 0;
	root->buffer = 0;
	for (int i = a; i <= b; i++)
		root->sum += A[i];
	if (a == b) {
		root->lc = NULL;
		root->rc = NULL;
		return;
	}
	int mid = (a + b) / 2;
	nodeCnt++;
	root->lc = tree + nodeCnt;
	buildTree(root->lc, a, mid);
	nodeCnt++;
	root->rc = tree + nodeCnt;
	buildTree(root->rc, mid + 1, b);
	return;
}

void add(Node* root, int a, int b, int c) {
	//cout << "Add: " << a << " " << b << " " << c << endl;
	if (root->a == a && root->b == b) {
		root->buffer += c;
		return;
	}
	root->sum += (b - a + 1)*c;
	int mid = (root->a + root->b) / 2;
	if (b <= mid)
		add(root->lc, a, b, c);
	else if (a > mid)
		add(root->rc, a, b, c);
	else {
		add(root->lc, a, mid, c);
		add(root->rc, mid + 1, b, c);
	}
	return;
}

long long query(Node* root, int a, int b) {
	//cout << "Query: " << a << " " << b << endl;
	if (root->a == a && root->b == b) {
		return root->sum + (root->b - root->a + 1)*root->buffer;
	}
	int mid = (root->a + root->b) / 2;
	
	root->sum += (root->b - root->a + 1)*root->buffer;
	add(root->lc, root->a, mid, root->buffer);
	add(root->rc, mid + 1, root->b, root->buffer);
	root->buffer = 0;

	long long res = 0;
	if (mid >= b)
		res += query(root->lc, a, b);
	else if (mid < a)
		res += query(root->rc, a, b);
	else {
		res += query(root->lc, a, mid);
		res += query(root->rc, mid + 1, b);
	}
	return res;
}

int main() {
	scanf("%d%d", &N, &Q);
	for (int i = 1; i <= N; i++)
		scanf("%d", A + i);
	buildTree(tree, 1, N);
	char op;
	int a, b, c;
	while (Q--) {
		scanf(" %c", &op);
		if (op == 'Q') {
			scanf("%d%d", &a, &b);
			printf("%lld\n", query(tree, a, b));
		}
		else {
			scanf("%d%d%d", &a, &b, &c);
			add(tree, a, b, c);
		}
	}
	system("pause");
	return 0;
}