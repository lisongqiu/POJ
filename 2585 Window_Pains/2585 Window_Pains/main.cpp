#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string>
#include<string.h>

using namespace std;

int map[4][4];
int overlap[4][4][4] = {
	{ { 1, -1, -1, -1 }, { 1, 2, -1, -1 }, { 2, 3, -1, -1 }, {3, -1, -1, -1} },
	{ { 1, 4, -1, -1 }, { 1, 2, 4, 5 }, { 2, 3, 5, 6 }, { 3, 6, -1, -1 } },
	{ { 4, 7, -1, -1 }, { 4, 5, 7, 8 }, { 5, 6, 8, 9 }, { 6, 9, -1, -1 } },
	{ { 7, -1, -1, -1 }, { 7, 8, -1, -1 }, { 8, 9, -1, -1 }, { 9, -1, -1, -1 } },
};

int dg[10][10];
int degree[10];
int used[10];

int main() {
	string input;
	while (cin >> input) {
		if (input == "ENDOFINPUT")
			break;
		memset(dg, 0, sizeof(dg));
		memset(degree, 0, sizeof(degree));
		memset(used, 0, sizeof(used));
		//input.
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				cin >> map[i][j];
		cin >> input;
		//build graph.
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				int tmp = map[i][j];
				for (int k = 0; k < 4; k++) {
					int e = overlap[i][j][k];
					if (e != tmp && e != -1) {
						if (!dg[tmp][e])
							degree[e]++;
						dg[tmp][e] = 1;
					}
				}
			}
		}
		/*
		//debug.
		for (int i = 1; i <= 9; i++) {
			for (int j = 1; j <= 9; j++)
				cout << dg[i][j] << " ";
			cout << endl;
		}
		*/
		//do topo.
		queue<int> ques;
		for (int i = 1; i <= 9; i++)
			if (degree[i] == 0) {
				ques.push(i);
				used[i] = true;
			}
		while (!ques.empty()) {
			int tmp = ques.front();
			ques.pop();
			//cout << "topo:" << tmp << endl;
			for (int i = 1; i <= 9; i++) {
				if (dg[tmp][i])
					degree[i]--;
				if (degree[i] == 0 && !used[i]) {
					ques.push(i);
					used[i] = true;
				}
			}
		}
		bool done = true;
		for (int i = 1; i <= 9; i++)
			if (!used[i])
				done = false;
		if (done)
			cout << "THESE WINDOWS ARE CLEAN" << endl;
		else
			cout << "THESE WINDOWS ARE BROKEN" << endl;
	}
	system("pause");
	return 0;
}