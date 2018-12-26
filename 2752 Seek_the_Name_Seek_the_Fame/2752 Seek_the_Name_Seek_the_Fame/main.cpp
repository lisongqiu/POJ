#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string.h>
#include<stack>

using namespace std;

#define MAXN 400010
int N;
char S[MAXN];
int nexts[MAXN];

void getNexts() {
	nexts[0] = -1;
	int i = 0;
	int k = -1;
	while (i < N) {
		while (k >= 0 && S[i] != S[k])
			k = nexts[k];
		i++;
		k++;
		nexts[i] = k;
	}
	return;
}

int main() {
	while (~scanf("%s", S)) {
		N = strlen(S);
		getNexts();
		stack<int> res;
		res.push(N);
		int k = nexts[N];
		while (k != 0) {
			res.push(k);
			k = nexts[k];
		}
		while (!res.empty()) {
			printf("%d ", res.top());
			res.pop();
		}
		printf("\n");
	}
	system("pause");
	return 0;
}