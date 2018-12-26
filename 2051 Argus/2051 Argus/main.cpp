#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<string.h>
#include<queue>

using namespace std;

struct Query {
	int idx;
	int period;
	int time;
	Query(){}
	Query(int ii, int pp, int tt):idx(ii), period(pp), time(tt){}
	bool operator<(const Query& q) const {
		if (q.time == this->time)
			return q.idx < this->idx;
		else
			return q.time < this->time;
	}
};

char input[20];
char regist[20] = "Register";
char end[20] = "#";
int K;
int a, b;

int main() {
	priority_queue<Query> pri;
	while (~scanf("%s", input)) {
		if (strcmp(input, regist) != 0)
			break;
		scanf("%d%d", &a, &b);
		pri.push(Query(a, b, b));
	}
	scanf("%d", &K);
	while (K--) {
		int time = pri.top().time;
		int period = pri.top().period;
		int idx = pri.top().idx;
		pri.pop();
		pri.push(Query(idx, period, time+period));
		//cout << idx << " " << period << " " << time << endl;
		printf("%d\n", idx);
	}
	system("pause");
	return 0;
}