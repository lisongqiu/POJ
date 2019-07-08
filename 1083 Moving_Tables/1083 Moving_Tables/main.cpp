#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>

using namespace std;

int rooms[401];
int T, N;

int main() {
	cin >> T;
	while (T--) {
		memset(rooms, 0, sizeof(rooms));
		cin >> N;
		while (N--) {
			int a, b;
			cin >> a >> b;
			int aa = min(a, b);
			if (aa % 2 == 0)
				aa = aa - 1;
			int bb = max(a, b);
			if (bb % 2 == 0)
				bb = bb - 1;
			for (int i = aa; i <= bb; i += 2)
				rooms[i]++;
		}
		int rnt = 0;
		for (int i = 1; i <= 399; i += 2)
			rnt = max(rnt, rooms[i]);
		cout << rnt * 10 << endl;
	}
	system("pause");
	return 0;
}
