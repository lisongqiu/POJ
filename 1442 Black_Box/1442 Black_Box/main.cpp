#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<functional>

using namespace std;

#define MAXN 30010
int M, N;
int a[MAXN];

int main() {
	scanf("%d%d", &M, &N);
	for (int i = 0; i < M; i++)
		scanf("%d", a + i);
	priority_queue<int> maxPri;
	priority_queue<int, vector<int>, greater<int> > minPri;
	int p, i = 0, k = 0;
	while (N--) {
		scanf("%d", &p);
		i++;
		while (k < p) {
			minPri.push(a[k]);
			while (!maxPri.empty() && minPri.top() < maxPri.top()) {
				maxPri.push(minPri.top());
				minPri.pop();
				minPri.push(maxPri.top());
				maxPri.pop();
			}
			k++;
		}
		while (maxPri.size() < i) {
			maxPri.push(minPri.top());
			minPri.pop();
		}
		printf("%d\n", maxPri.top());
	}
	system("pause");
	return 0;
}