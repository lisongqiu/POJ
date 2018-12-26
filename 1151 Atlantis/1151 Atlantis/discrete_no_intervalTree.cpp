/*
#define _CRT_SECURE_NO_DEPRECATE

#include<stdio.h>
#include<iomanip>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string.h>

using namespace std;

struct Area {
	double x1, y1;
	double x2, y2;
	Area(){}
	Area(int xx1, int yy1, int xx2, int yy2) {
		this->x1 = xx1;
		this->y1 = yy1;
		this->x2 = xx2;
		this->y2 = yy2;
	}
};

int findIdx(double val, double* array, int len) {
	int l = 0, r = len - 1;
	while (l < r) {
		int mid = (l + r) / 2;
		//cout << "l:" << l << " r:" << r << " mid:" << mid << endl;
		if (array[mid] == val)
			return mid;
		if (array[mid] < val)
			l = mid + 1;
		else
			r = mid;
	}
	return l;
}

#define MAXN 101
int N;
Area areas[MAXN];
double x[2 * MAXN];
double y[2 * MAXN];
double map[2 * MAXN][2 * MAXN];

int main() {
	int testCnt = 0;
	while (cin >> N) {
		if (N == 0)
			break;
		memset(map, 0, sizeof(map));
		int xNum = 0, yNum = 0;
		for (int i = 0; i < N; i++) {
			scanf("%lf%lf%lf%lf", &areas[i].x1, &areas[i].y1, &areas[i].x2, &areas[i].y2);
			x[xNum++] = areas[i].x1;
			x[xNum++] = areas[i].x2;
			y[yNum++] = areas[i].y1;
			y[yNum++] = areas[i].y2;
		}
		sort(x, x + xNum);
		sort(y, y + yNum);
		xNum = unique(x, x + xNum) - x;
		yNum = unique(y, y + yNum) - y;
		for (int i = 0; i < N; i++) {
			int idx1 = findIdx(areas[i].x1, x, xNum);
			int idx2 = findIdx(areas[i].x2, x, xNum);
			int idy1 = findIdx(areas[i].y1, y, yNum);
			int idy2 = findIdx(areas[i].y2, y, yNum);
			for (int xx = idx1; xx < idx2; xx++) {
				for (int yy = idy1; yy < idy2; yy++) {
					map[xx][yy] = 1;
				}
			}
		}
		double res = 0;
		for (int i = 0; i < xNum; i++)
			for (int j = 0; j < yNum; j++)
				if (map[i][j])
					res += (x[i + 1] - x[i])*(y[j + 1] - y[j]);
		cout << "Test case #" << ++testCnt << endl;
		printf("Total explored area: %.2f\n\n", res);
	}
	system("pause");
	return 0;
}
*/