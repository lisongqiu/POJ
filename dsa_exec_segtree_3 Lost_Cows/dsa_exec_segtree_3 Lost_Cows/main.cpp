#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<algorithm>
#include<string.h>

using namespace std;

struct Node {
	bool used;
	int lcnt, rcnt;
	int lleft;
	Node *lc, *rc;
};

#define MAXN 8010
int N;
int precede[MAXN];
int trueIdx[MAXN];
int nodeCnt = 0;
Node tree[4 * MAXN];

int insertNode(Node* root, int idx, int total, int begin) {
	//printf("%d, %d, %d\n", idx, total, begin);
	if (root->used) {
		if (idx < root->lleft) {
			root->lleft--;
			return insertNode(root->lc, idx, root->lcnt, begin);
		}
		else {
			return insertNode(root->rc, idx - root->lleft, root->rcnt, root->lcnt + 1 + begin);
		}
	}
	root->used = true;
	nodeCnt++;
	root->lc = tree + nodeCnt;
	nodeCnt++;
	root->rc = tree + nodeCnt;
	root->lcnt = idx;
	root->rcnt = total - idx - 1;
	root->lleft = root->lcnt;
	//printf("idx:%d, lcnt:%d, rcnt:%d\n", begin + idx + 1, root->lcnt, root->rcnt);
	return begin + idx + 1;
}

void init() {
	memset(trueIdx, 0, sizeof(trueIdx));
	for (int i = 0; i < 4 * N; i++)
		tree[i].used = false;
}

int main() {
	scanf("%d", &N);
	precede[1] = 0;
	for (int i = 2; i <= N; i++)
		scanf("%d", precede + i);
	init();
	for (int i = N; i >= 1; i--) {
		int pos = insertNode(tree, precede[i], N, 0);
		trueIdx[i] = pos;
	}
	for (int i = 1; i <= N; i++) {
		printf("%d\n", trueIdx[i]);
	}
	system("pause");
	return 0;
}
/*
7
0
1
0
4
5
5


*/