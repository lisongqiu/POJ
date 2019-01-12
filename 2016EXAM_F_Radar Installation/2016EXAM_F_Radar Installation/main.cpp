#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<math.h>
#include<vector>

using namespace std;

#define INF 0x3f3f3f3f

struct Point {
	double l, r;
	Point() {}
	Point(double ll, double rr) :l(ll), r(rr) {}
	bool operator<(const Point& p) {
		return this->r < p.r;
	}
};

int N, D;

int main() {
	int caseId = 1;
	while (cin >> N >> D) {
		if (N == 0 && D == 0)
			break;
		vector<Point> v;
		v.clear();
		int x, y;
		bool is_ok = true;
		for (int i = 0; i < N; i++) {
			cin >> x >> y;
			if (y > D) // can't be y*y > D*D !!! overflow?
				is_ok = false;
			double l = x - sqrt(D*D - y * y);
			double r = x + sqrt(D*D - y * y);
			v.push_back(Point(l, r));
		}
		if (!is_ok) {
			cout << "Case " << caseId++ << ": " << -1 << endl;
			continue;
		}
		sort(v.begin(), v.end());
		int cnt = 0, pt = 0;
		double pv = -INF;
		while (pt < v.size()) {
			if (pv < v[pt].l) {
				cnt++;
				pv = v[pt].r;
			}
			pt++;
		}
		// output.
		cout << "Case " << caseId++ << ": " << cnt << endl;
	}
	system("pause");
	return 0;
}