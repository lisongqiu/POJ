#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<functional>

using namespace std;

int T, N;
priority_queue<int> maxQ;
priority_queue<int, vector<int>, greater<int> > minQ;

int main() {
	scanf("%d", &T);
	while (T--) {
		while (!maxQ.empty())
			maxQ.pop();
		while (!minQ.empty())
			minQ.pop();
		scanf("%d", &N);
		char op;
		int num;
		while (N--) {
			scanf(" %c", &op);
			if (op == 'I') {
				scanf("%d", &num);
				if (maxQ.empty())
					maxQ.push(num);
				else if (num <= maxQ.top())
					maxQ.push(num);
				else
					minQ.push(num);
				while (maxQ.size() - 1 > minQ.size()) {
					minQ.push(maxQ.top());
					maxQ.pop();
				}
				while (minQ.size() > maxQ.size()) {
					maxQ.push(minQ.top());
					minQ.pop();
				}
			}
			else if (op == 'D') {
				maxQ.pop();
				while (maxQ.size() < minQ.size()) {
					maxQ.push(minQ.top());
					minQ.pop();
				}
			}
			else {
				printf("%d\n", maxQ.top());
			}
		}
	}
	system("pause");
	return 0;
}