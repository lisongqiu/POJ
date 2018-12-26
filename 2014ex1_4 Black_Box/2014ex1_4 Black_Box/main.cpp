#define _CRT_SECURE_NO_DEPRECATE

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
	priority_queue<int> max_heap;
	priority_queue<int, vector<int>, greater<int> > min_heap;
	int i = 0, p = 0, q;
	while (N--) {
		scanf("%d", &q);
		i++;
		while (p < q) {
			if (max_heap.empty())
				max_heap.push(a[p]);
			else {
				if (a[p] < max_heap.top()) {
					min_heap.push(max_heap.top());
					max_heap.pop();
					max_heap.push(a[p]);
				}
				else
					min_heap.push(a[p]);
			}
			p++;
		}
		while (max_heap.size() < i) {
			max_heap.push(min_heap.top());
			min_heap.pop();
		}
		printf("%d\n", max_heap.top());
	}
	system("pause");
	return 0;
}