#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string.h>
using namespace std;

struct Edge {
	int b, w;
	Edge(){}
	Edge(int bb, int ww):b(bb), w(ww){}
	bool operator<(const Edge& e) const{ //the const is neccessary.!.
		return this->w > e.w;
	}
};

#define MAXN 111

int N;
int matrix[MAXN][MAXN];
bool used[MAXN];
priority_queue<Edge> pq;

int main() {
	while (cin >> N) { // The input includes several cases. !!
		memset(used, 0, sizeof(used));
		while (!pq.empty())
			pq.pop();
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				cin >> matrix[i][j];
			}
		int res = 0;
		pq.push(Edge(0, 0));
		while (!pq.empty()) {
			Edge tmp = pq.top();
			pq.pop();
			if (used[tmp.b])
				continue;
			used[tmp.b] = 1;
			res += tmp.w;
			for (int i = 0; i < N; i++)
				if (used[i] == 0)
					pq.push(Edge(i, matrix[tmp.b][i]));
		}
		bool allDown = true;
		for (int i = 0; i < N; i++)
			if (!used[i])
				allDown = false;
		if (allDown)
			cout << res << endl;
		else
			cout << -1 << endl;
	}
	system("pause");
	return 0;
}
