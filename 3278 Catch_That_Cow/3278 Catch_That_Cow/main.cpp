#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>

using namespace std;

struct Step {
	int x;
	int t;
	Step(int xx, int tt) {
		this->x = xx;
		this->t = tt;
	}
};

#define MAXN 100001
queue<Step> ques;
int used[MAXN] = { 0 };

int main() {
	int N, K;
	cin >> N >> K;
	ques.push(Step(N, 0));
	used[N] = 1;
	while (!ques.empty()) {
		Step tmp = ques.front();
		if (tmp.x == K)
			break;
		ques.pop();
		if (tmp.x - 1 >= 0 && tmp.x - 1<MAXN && !used[tmp.x - 1]) {
			ques.push(Step(tmp.x - 1, tmp.t + 1));
			used[tmp.x - 1] = 1;
		}
		if (tmp.x + 1 >= 0 && tmp.x + 1<MAXN && !used[tmp.x + 1]) {
			ques.push(Step(tmp.x + 1, tmp.t + 1));
			used[tmp.x + 1] = 1;
		}
		if (2 * tmp.x < MAXN && !used[2 * tmp.x]) {
			ques.push(Step(2 * tmp.x, tmp.t + 1));
			used[2 * tmp.x] = 1;
		}
	}
	cout << ques.front().t << endl;
	system("pause");
	return 0;
}