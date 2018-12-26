#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<algorithm>
#include<vector>
#include<math.h>
#include<string.h>

using namespace std;

struct Node {
	int x, y, z;
	Node(){}
	Node(int xx, int yy, int zz):x(xx), y(yy), z(zz){}
};

#define MAXN 1001
int N;
Node nodes[MAXN];
double dst[MAXN][MAXN];
double dz[MAXN][MAXN];

double mst(double r) {
	int used[MAXN];
	memset(used, 0, sizeof(used));
	used[1] = 1;
	double factor[MAXN];
	for (int i = 1; i <= N; i++)
		factor[i] = dz[1][i] - dst[1][i] * r;
	double res = 0;
	int cnt = N - 1;
	while (cnt--) {
		double Min = 0x3f3f3f3f;
		int idx = -1;
		for(int i=1;i<=N;i++)
			if (!used[i] && factor[i] < Min) {
				Min = factor[i];
				idx = i;
			}
		//printf("%f, %f, %d\n", r, maxL, idx);
		if (idx == -1)
			break;
		used[idx] = 1;
		res += Min;
		for (int i = 1; i <= N; i++)
			if (!used[i]) {
				double tmpF = dz[idx][i] - dst[idx][i] * r;
				if (tmpF < factor[i])
					factor[i] = tmpF;
			}
	}
	return res;
}

int main() {
	while (~scanf("%d", &N) && N) {
		int a, b, c;
		for (int i = 1; i <= N; i++) {
			scanf("%d %d %d", &a, &b, &c);
			nodes[i] = Node(a, b, c);
		}
		double minR = 0x3f3f3f3f;
		double maxR = 0;
		for (int i = 1; i <= N; i++) {
			for (int j = i+1; j <= N; j++) {
				double dist = sqrt(double((nodes[i].x - nodes[j].x)*(nodes[i].x - nodes[j].x) + (nodes[i].y - nodes[j].y)*(nodes[i].y - nodes[j].y)));
				double cost = abs(nodes[i].z - nodes[j].z);
				double tmpR = cost/dist;
				dst[i][j] = dist;
				dst[j][i] = dist;
				dz[i][j] = cost;
				dz[j][i] = cost;
				minR = min<double>(minR, tmpR);
				maxR = max<double>(maxR, tmpR);
			}
		}

		//mid_divide
		double l = minR, r = maxR;
		while (r - l > 1e-4) {
			double mid = (l + r) / 2;
			//printf("mid: %.3lf\n", mid);
			if (mst(mid)<0) //if mid>r_min
				r = mid;
			else
				l = mid;
		}
		printf("%.3f\n", l);
	}
	system("pause");
	return 0;
}

/*

4
0 0 0
0 1 1
1 1 2
1 0 3
0

*/