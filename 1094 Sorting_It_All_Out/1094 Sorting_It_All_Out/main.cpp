#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<queue>
#include<string.h>

using namespace std;

#define MAXN 27
int N, M;
int map[MAXN][MAXN];
int degree[MAXN];

vector<int> res;

int topo() {
	res.clear();
	int used[MAXN] = { 0 };
	int tmpD[MAXN];
	int unique = true;
	memcpy(tmpD, degree, sizeof(tmpD));
	queue<int> ques;
	for (int i = 0; i < N; i++)
		if (tmpD[i] == 0) {
			ques.push(i);
			used[i] = true;
		}
	while (!ques.empty()) {
		//cout << "size of queue: " << ques.size() << endl;
		if (ques.size() != 1)
			unique = false;
		int tmp = ques.front();
		ques.pop();
		res.push_back(tmp);
		for(int i=0;i<N;i++)
			if (map[tmp][i]) {
				tmpD[i]--;
				if (tmpD[i] == 0 && !used[i]) {
					ques.push(i);
					used[i] = true;
				}
			}
	}
	if (unique && res.size() == N)
		return 1;
	else if (res.size() != N)
		return 2;
	else
		return 0;
}

int main() {
	while (cin >> N >> M) {
		if (N == 0 && M == 0)
			break;
		memset(map, 0, sizeof(map));
		memset(degree, 0, sizeof(degree));
		string input;
		int cnt = 0;
		bool done = false;
		for (int i = 1; i <= M; i++) {
			cin >> input;
			if (done)
				continue;
			int a = int(input[0] - 'A');
			int b = int(input[2] - 'A');
			degree[b]++;
			map[a][b] = 1;
			int ans = topo();
			if (ans == 1) {
				cout << "Sorted sequence determined after " << i << " relations: ";
				for (int j = 0; j < res.size(); j++)
					cout << char('A' + res[j]);
				cout << "." << endl;
				done = true;
			}
			else if (ans == 2) {
				cout << "Inconsistency found after " << i << " relations." << endl;
				done = true;
			}
		}
		if (!done)
			cout << "Sorted sequence cannot be determined." << endl;
	}
	system("pause");
	return 0;
}