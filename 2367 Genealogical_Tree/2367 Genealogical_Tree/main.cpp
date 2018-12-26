#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string.h>

using namespace std;

struct Node {
	int degree;
	vector<int> child;
	Node() {
		this->degree = 0;
	}
};

#define MAXN 101
int N;
Node nodes[MAXN];
int used[MAXN];

int main() {
	cin >> N;
	memset(used, 0, sizeof(used));
	int a;
	for (int i = 1; i <= N; i++) {
		while (cin >> a) {
			if (a == 0)
				break;
			nodes[i].child.push_back(a);
			nodes[a].degree++;
		}
	}
	queue<int> ques;
	vector<int> res;
	for (int i = 1; i <= N; i++)
		if (nodes[i].degree == 0) {
			ques.push(i);
			used[i] = true;
		}
	while (!ques.empty()) {
		int tmp = ques.front();
		ques.pop();
		res.push_back(tmp);
		for (int i = 0; i < nodes[tmp].child.size(); i++) {
			nodes[nodes[tmp].child[i]].degree--;
			if (nodes[nodes[tmp].child[i]].degree == 0 && !used[nodes[tmp].child[i]]) {
				ques.push(nodes[tmp].child[i]);
				used[nodes[tmp].child[i]] = true;
			}
		}
	}
	for (int i = 0; i < res.size(); i++)
		cout << res[i] << " ";
	cout << endl;
	system("pause");
	return 0;
}