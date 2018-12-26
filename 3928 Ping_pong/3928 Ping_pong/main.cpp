#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

#define MAXN 100010

struct Node {
	int rank;
	int pos;
	bool operator<(const Node& n) const {
		return this->rank < n.rank;
	}
};

int T, N;
Node nodes[MAXN];
int c[MAXN];

void add(int pos, int val) {
	while (pos <= N) {
		c[pos] += val;
		pos += pos & (-pos);
	}
}

long long sum(int pos) {
	long long rnt = 0;
	while (pos > 0) {
		rnt += c[pos];
		pos -= pos & (-pos);
	}
	return rnt;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		memset(c, 0, sizeof(c));
		for (int i = 1; i <= N; i++) {
			scanf("%d", &nodes[i].rank);
			nodes[i].pos = i;
		}
		sort(nodes + 1, nodes + N + 1);
		long long res = 0;
		for (int i = 1; i < N; i++) {
			long long leftLess = sum(nodes[i].pos);
			long long leftMore = nodes[i].pos - 1 - leftLess;
			long long rightLess = i - 1 - leftLess;
			long long rightMore = N - nodes[i].pos - rightLess;
			//cout << leftLess << " " << leftMore << " " << rightLess << " " << rightMore << endl;
			res += leftLess * rightMore + leftMore * rightLess;
			add(nodes[i].pos, 1);
		}
		printf("%lld\n", res);
	}
	system("pause");
	return 0;
}