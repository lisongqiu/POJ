#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;

#define MAXN 1000010
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
	int caseIdx = 1;
	while (~scanf("%d", &N)) {
		if (N == 0)
			break;
		scanf("%s", S);
		printf("Test case #%d\n", caseIdx++);
		getNexts();
		for (int i = 2; i <= N; i++) {
			if (i % (i - nexts[i]) == 0 && nexts[i] != 0)
				printf("%d %d\n", i, i / (i - nexts[i]));
		}
		printf("\n");
	}
	system("pause");
	return 0;
}