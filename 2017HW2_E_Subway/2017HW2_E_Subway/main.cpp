#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<math.h>
#include<queue>
#include<string.h>

using namespace std;

#define INF 0x3f3f3f3f
#define MAXN 210
#define	SUBWAY 40000
#define WALK 10000

struct Node {
	int x, y;
};

double MAP[MAXN][MAXN];
Node nodes[MAXN];
int nodeCnt = 0;
double minLen[MAXN];
double RES = 0;

int main() {
	int x, y;
	cin >> x >> y;
	nodes[nodeCnt].x = x, nodes[nodeCnt++].y = y;
	cin >> x >> y;
	nodes[nodeCnt].x = x, nodes[nodeCnt++].y = y;
	memset(MAP, 0, sizeof(MAP));
	while (cin >> x >> y) {
		nodes[nodeCnt].x = x, nodes[nodeCnt++].y = y;
		while (cin >> x >> y) {
			if (x == -1 && y == -1)
				break;
			nodes[nodeCnt].x = x, nodes[nodeCnt].y = y;
			double timeCost = sqrt(pow(nodes[nodeCnt].x - nodes[nodeCnt - 1].x, 2) + pow(nodes[nodeCnt].y - nodes[nodeCnt - 1].y, 2)) / SUBWAY;
			MAP[nodeCnt - 1][nodeCnt] = timeCost;
			MAP[nodeCnt][nodeCnt - 1] = timeCost;
			nodeCnt++;
		}
	}
	for (int i = 0; i < nodeCnt; i++) {
		for (int j = 0; j < nodeCnt; j++) {
			if (i == j || MAP[i][j] != 0)
				continue;
			double timeCost = sqrt(pow(nodes[i].x - nodes[j].x, 2) + pow(nodes[i].y - nodes[j].y, 2)) / WALK;
			MAP[i][j] = timeCost;
		}
	}
	for (int i = 0; i < nodeCnt; i++)
		minLen[i] = INF;
	minLen[0] = 0;
	while (true) {
		double minDist = INF;
		int minI, minJ;
		for (int i = 0; i < nodeCnt; i++) {
			if (minLen[i]==INF)
				continue;
			for (int j = 0; j < nodeCnt; j++) {
				if (minLen[j] != INF)
					continue;
				if (MAP[i][j] + minLen[i] < minDist) {
					minDist = minLen[i] + MAP[i][j];
					minI = i;
					minJ = j;
				}
			}
		}
		minLen[minJ] = minDist;
		if (minJ == 1)
			break;
		
	}
	cout << round(minLen[1] * 60) << endl;
	system("pause");
	return 0;
}