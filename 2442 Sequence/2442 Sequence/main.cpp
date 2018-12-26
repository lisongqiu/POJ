#define _CRT_SECURE_NO_DEPRECATE

#include<stdio.h>
#include<algorithm>
#include<stack>
#include<queue>
#include<functional>

using namespace std;

#define MAXN 2010

int T;
int M, N;
int a[MAXN];

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &M, &N);
		priority_queue<int> pri[2];
		int i, j, k, c = 0;
		for (j = 0; j < N; j++) {
			scanf("%d", a + j);
			pri[c].push(a[j]);
		}
		for (i = 1; i < M; i++, c=1-c) {
			for (j = 0; j < N; j++)
				scanf("%d", a + j);
			sort(a, a + N);
			while (!pri[c].empty()) {
				int tmp = pri[c].top();
				//printf("tmp: %d\n", tmp);
				pri[c].pop();
				for (j = 0; j < N; j++) {
					int b = tmp + a[j];
					if (pri[1 - c].size() >= N && b > pri[1 - c].top()) //here is important!!!...
						break;
					pri[1 - c].push(b);
					//printf("pri[1-c]: %d\n", pri[1-c].top());
					if (pri[1 - c].size() > N)
						pri[1 - c].pop();		
				}
			}	
		}
		i = 0;
		while (!pri[c].empty()) {
			a[i++] = pri[c].top();
			pri[c].pop();
		}
		for (i = N - 1; i >= 0; i--)
			printf("%d ", a[i]);
		printf("\n");
	}
	system("pause");
	return 0;
}
