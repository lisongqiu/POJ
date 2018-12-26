#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<math.h>
#include<vector>
#include<queue>
#include<stack>

using namespace std;

struct Node {
	int l, r;
	int maxN, minN;
	Node *lc, *rc;
	Node() {
		this->maxN = 0;
		this->minN = 0x3f3f3f3f;
		this->lc = NULL;
		this->rc = NULL;
	};
	Node(int ll, int rr) :l(ll), r(rr){
		this->maxN = 0;
		this->minN = 0x3f3f3f3f;
		this->lc = NULL;
		this->rc = NULL;
	}
};

#define MAXN 50010
int N, Q;
int cows[MAXN];
Node* root = new Node();
int minV, maxV;

void buildTree() {
	//build.
	queue<Node*> ques;
	root->l = 1;
	root->r = N;
	ques.push(root);
	while (!ques.empty()) {
		Node* tmp = ques.front();
		//cout << "build:" << tmp->l << " " << tmp->r << endl;
		ques.pop();
		if (tmp->l == tmp->r)
			continue;
		int mid = (tmp->l + tmp->r) / 2;
		tmp->lc = new Node(tmp->l, mid);
		tmp->rc = new Node(mid + 1, tmp->r);
		ques.push(tmp->lc);
		ques.push(tmp->rc);
	}
	//insert.
	for (int i = 1; i <= N; i++) {
		//cout << "insert: " << i << " " << cows[i] << endl;
		int tmp = cows[i];
		Node* ptr = root;
		while (ptr != NULL) {
			ptr->maxN = max<int>(ptr->maxN, tmp);
			ptr->minN = min<int>(ptr->minN, tmp);
			int mid = (ptr->l + ptr->r) / 2;
			if (i <= mid)
				ptr = ptr->lc;
			else
				ptr = ptr->rc;
		}
	}
	return;
}

/*
void query(int a, int b) {
	//cout << "QUERY: " << a << " " << b << endl;
	int resMin = 0x3f3f3f3f, resMax = 0;
	queue<Node*> ques;
	ques.push(root);
	while(!ques.empty()){
		Node* tmp = ques.front();
		ques.pop();
		if (a <= tmp->l && b >= tmp->r) { //if terminal-node.
			resMin = min<int>(resMin, tmp->minN);
			resMax = max<int>(resMax, tmp->maxN);
			continue;
		}
		if (tmp->minN >= resMin && tmp->maxN <= resMax) //if no updates.
			continue;
		if (tmp->r<a || tmp->l>b) //if not cross.
			continue;
		int mid = (tmp->l + tmp->r) / 2;
		if (mid < a)
			ques.push(tmp->rc);
		else if (mid > b)
			ques.push(tmp->lc);
		else {
			ques.push(tmp->lc);
			ques.push(tmp->rc);
		}
	}
	cout << (resMax - resMin) << endl;
	return;
}
*/
void query(Node* r, int a, int b) { //use recursion ! queue is time-consuming.
	if (r->minN >= minV && r->maxN <= maxV)
		return;
	if (r->l >= a && r->r <= b) {
		minV = min<int>(minV, r->minN);
		maxV = max<int>(maxV, r->maxN);
		return;
	}
	int mid = (r->l + r->r) / 2;
	if (mid >= b)
		query(r->lc, a, b);
	else if (mid < a)
		query(r->rc, a, b);
	else {
		query(r->lc, a, mid);
		query(r->rc, mid + 1, b);
	}
	return;
}


int main() {
	cin >> N >> Q;
	for (int i = 1; i <= N; i++)
		scanf("%d", &cows[i]);
	buildTree();
	while (Q--) {
		int a, b;
		scanf("%d%d", &a, &b);
		minV = 0x3f3f3f3f;
		maxV = 0;
		query(root, a, b);
		printf("%d\n", maxV - minV);
	}
	system("pause");
	return 0;
}