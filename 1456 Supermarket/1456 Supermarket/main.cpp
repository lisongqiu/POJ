#include<iostream>
#include<algorithm>
#include<vector>
#include<math.h>
#include<string.h>

using namespace std;

struct Item {
	int p, d;
	Item(){}
	Item(int pp, int dd):p(pp), d(dd){}
};

bool cmp(const Item& a, const Item& b) {
	return a.p > b.p;
}

#define MAXN 10010

int N;
int used[MAXN];
vector<Item> items;

int getPar(int a) {
	if (used[a] == a)
		return a;
	used[a] = getPar(used[a]);
	return used[a];
}

int main() {
	int p, d;
	while (cin >> N) {
		int maxD = 0;
		items.clear();
		for (int i = 0; i < N; i++) {
			cin >> p >> d;
			items.push_back(Item(p, d));
			maxD = max<int>(maxD, d);
		}
		for (int i = 0; i <= maxD; i++)
			used[i] = i;
		//greedy.
		sort(items.begin(), items.end(), cmp);
		int res = 0;
		for (int i = 0; i < N; i++) {
			int td = getPar(items[i].d);
			if (td > 0) {
				used[td] = td - 1;
				res += items[i].p;
			}
		}
		cout << res << endl;
	}
	system("pause");
	return 0;
}