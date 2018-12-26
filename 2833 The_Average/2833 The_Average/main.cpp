#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<functional>

using namespace std;

#define MAXN 5000010
int n1, n2, n;
long long a;

int main() {
	while (~scanf("%d%d%d", &n1, &n2, &n)) {
		if (n1 == 0 && n2 == 0 && n == 0)
			break;
		//n1: largest, n2: least.
		priority_queue<int> max_heap; //n2
		priority_queue<int, vector<int>, greater<int> > min_heap; //n1
		for (int i = 0; i < n1 + n2; i++) {
			scanf("%lld", &a);
			max_heap.push(a);
		}
		for (int i = 0; i < n1; i++) {
			min_heap.push(max_heap.top());
			max_heap.pop();
		}
		long long res = 0;
		for (int i = n1 + n2; i < n; i++) {
			scanf("%lld", &a);
			if (a < max_heap.top()) {
				max_heap.push(a);
				a = max_heap.top();
				max_heap.pop();
			}
			else if (a > min_heap.top()) {
				min_heap.push(a);
				a = min_heap.top();
				min_heap.pop();
			}	
			res += a;
		}
		printf("%.6f\n", res * 1.0 / (n - n1 - n2)); //What fuck!! change lf->f then accepted !!
	}
	system("pause");
	return 0;
}