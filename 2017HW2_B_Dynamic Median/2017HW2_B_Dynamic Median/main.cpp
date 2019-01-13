#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<algorithm>
#include<iostream>
#include<string.h>
#include<queue>
#include<functional>

using namespace std;

priority_queue<int, vector<int>, less<int>> maxQ;
priority_queue<int, vector<int>, greater<int>> minQ;

int main() {
	int T, N;
	char op;
	int val;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		while (!maxQ.empty())
			maxQ.pop();
		while (!minQ.empty())
			minQ.pop();
		while (N--) {
			scanf(" %c", &op);
			if (op == 'I') {
				scanf("%d", &val);
				if (maxQ.empty() || val <= maxQ.top()) {
					maxQ.push(val);
					if (maxQ.size() > minQ.size() + 1) {
						minQ.push(maxQ.top());
						maxQ.pop();
					}
				}
				else {
					minQ.push(val);
					if (minQ.size() > maxQ.size()) {
						maxQ.push(minQ.top());
						minQ.pop();
					}
				}
			}
			else if (op == 'Q')
				printf("%d\n", maxQ.top()); //can't use cout!
			else {
				maxQ.pop();
				if (maxQ.size() < minQ.size()) {
					maxQ.push(minQ.top());
					minQ.pop();
				}
			}
		}
	}
	system("pause");
	return 0;
}