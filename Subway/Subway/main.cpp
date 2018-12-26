#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<math.h>
#include<string.h>
#include<queue>

using namespace std;

#define MAXN 210
#define SUBWAY 40000
#define WALK 10000
#define INF 0x3f3f3f3f

struct Node {
	int x, y;
};

Node nodes[MAXN];
double map[MAXN][MAXN];
int nodeCnt = 2;
double minLen[MAXN];
int used[MAXN];

int main() {
	//init.
	memset(map, 0, sizeof(map));
	for (int i = 0; i < MAXN; i++) {
		minLen[i] = INF;
		used[i] = false;
	}
	//input.
	ios::sync_with_stdio(false);
	cin >> nodes[0].x >> nodes[0].y >> nodes[1].x >> nodes[1].y;
	int a, b;
	while (cin >> nodes[nodeCnt].x >> nodes[nodeCnt].y) {
		nodeCnt++;
		while (cin >> a >> b) {
			//cout << "a: " << a << " b: " << b << " cnt:" << nodeCnt << endl;
			if (a == -1 && b == -1)
				break;
			nodes[nodeCnt].x = a;
			nodes[nodeCnt].y = b;
			nodeCnt++;
			//add subway_cost to map.
			double timeCost = sqrt(pow(nodes[nodeCnt - 1].x - nodes[nodeCnt - 2].x, 2) + pow(nodes[nodeCnt - 1].y - nodes[nodeCnt - 2].y, 2)) / SUBWAY;
			map[nodeCnt - 1][nodeCnt - 2] = timeCost;
			map[nodeCnt - 2][nodeCnt - 1] = timeCost;
		}
	}
	for (int i = 0; i < nodeCnt; i++) {
		for (int j = 0; j < nodeCnt; j++) {
			if (i == j || map[i][j] != 0)
				continue;
			double timeCost = sqrt(pow(nodes[i].x - nodes[j].x, 2) + pow(nodes[i].y - nodes[j].y, 2)) / WALK;
			map[i][j] = timeCost;
			map[j][i] = timeCost;
		}
	}
	//debug.
	//for (int i = 0; i < nodeCnt; i++) {
	//	cout << "IDX: " << i << " (x, y)=(" << nodes[i].x << ", " << nodes[i].y << ")" << endl;
	//}
	//dijkstra.
	used[0] = true;
	for (int i = 1; i < nodeCnt; i++)
		minLen[i] = min(minLen[i], map[0][i]);
	while (!used[1]) {
		//find the next node.
		int minIdx = 0;
		double minCost = INF;
		for (int i = 0; i < nodeCnt; i++) {
			if (!used[i] && minLen[i] < minCost) {
				minIdx = i;
				minCost = minLen[i];
			}
		}
		//cout << "idx=" << minIdx << " (x, y)=(" << nodes[minIdx].x << ", " << nodes[minIdx].y << ")" << " timeCost:" << minCost << endl;
		used[minIdx] = true;
		for (int i = 0; i < nodeCnt; i++) {
			if (used[i])
				continue;
			minLen[i] = min(minLen[i], map[minIdx][i] + minLen[minIdx]);
		}
	}
	cout << round(minLen[1] * 60) << endl;
	system("pause");
	return 0;
}