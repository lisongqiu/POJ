#define _CRT_SECURE_NO_DEPRECATE

#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<math.h>

using namespace std;

struct Node {
	int l, r;
	long long sum, inc;
	int mid() {
		return (this->l + this->r) / 2;
	}
	Node() {};
	Node(int ll, int rr):l(ll), r(rr){}
};

#define MAXN 100010*4
Node nodes[MAXN] = { Node() };
int N, Q;

void build(int idx, int l, int r) {
	//cout << "build: " << idx << " " << l << " " << r << endl;
	nodes[idx].l = l;
	nodes[idx].r = r;
	nodes[idx].sum = 0;
	nodes[idx].inc = 0;
	if (l == r)
		return;
	build(2 * idx + 1, l, nodes[idx].mid());
	build(2 * idx + 2, nodes[idx].mid() + 1, r);
	return;
}

void insert(int root, int idx, int v) {
	nodes[root].sum += v;
	if (nodes[root].l == nodes[root].r)
		return;
	int mid = nodes[root].mid();
	if (idx <= mid)
		insert(root * 2 + 1, idx, v);
	else
		insert(root * 2 + 2, idx, v);
	return;
}

void add(int root, int a, int b, int c) {
	//cout << "add: " << root << " " << a << " " << b << " " << c << endl;
	if (nodes[root].l == a && nodes[root].r == b) {
		nodes[root].inc += c;
		return;
	}
	nodes[root].sum += (b - a + 1)*c;
	int mid = nodes[root].mid();
	if (mid >= b)
		add(root * 2 + 1, a, b, c);
	else if (mid < a)
		add(root * 2 + 2, a, b, c);
	else {
		add(root * 2 + 1, a, mid, c);
		add(root * 2 + 2, mid + 1, b, c);
	}
	return;
}

long long query(int root, int a, int b) {
	//cout << "query: " << root << " " << a << " " << b << endl;
	if (nodes[root].l == a && nodes[root].r == b)
		return nodes[root].sum + (b - a + 1)*nodes[root].inc;
	nodes[root].sum += (nodes[root].r - nodes[root].l + 1)*nodes[root].inc; //here.!!!
	add(root * 2 + 1, nodes[root].l, nodes[root].mid(), nodes[root].inc);
	add(root * 2 + 2, nodes[root].mid() + 1, nodes[root].r, nodes[root].inc);
	nodes[root].inc = 0; //here!!!.
	int mid = nodes[root].mid();
	if (mid >= b)
		return query(root * 2 + 1, a, b);
	else if (mid < a)
		return query(root * 2 + 2, a, b);
	else {
		long long res = 0;
		res += query(root * 2 + 1, a, mid);
		res += query(root * 2 + 2, mid + 1, b);
		return res;
	}
}

int main() {
	scanf("%d%d", &N, &Q);
	build(0, 1, N);
	int a;
	for (int i = 1; i <= N; i++) {
		scanf("%d", &a);
		insert(0, i, a);
	}
	char op;
	int b, c;
	for (int i = 0; i < Q; i++) {
		scanf(" %c", &op);
		if (op == 'Q') {
			scanf("%d%d", &a, &b);
			//cout << "QUERY: " << a << b << endl;
			printf("%lld\n", query(0, a, b));
		}
		else {
			scanf("%d%d%d", &a, &b, &c);
			//cout << "ADD: " << a << " " << b << " " << c << endl;
			add(0, a, b, c);
		}
	}
	system("pause");
	return 0;
}