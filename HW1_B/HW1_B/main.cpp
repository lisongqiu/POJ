#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

const int MAXN = 201;
int n, k;
int a[MAXN];
int inverse[MAXN];

void f(string s) {
	while (s.length() < n)
		s.push_back(' ');
	vector<int> vec;
	for (int i = 0; i < n; i++) {
		int idx = i;
		int epoch = 0;
		for (int j = 0; j < k; j++) {
			idx = inverse[idx];
			if (idx == i) {
				epoch = j + 1;
				break;
			}
		}
		if (epoch) {
			//cout << "Epoch:" << epoch << endl;
			idx = i;
			for (int j = 0; j < k%epoch; j++)
				idx = inverse[idx];
		}
		vec.push_back(idx);
	}
	for (int i = 0; i < n; i++)
		cout << s[vec[i]];
	cout << endl;
}

int main() {
	while (cin >> n) {
		if (n == 0)
			break;
		for (int i = 0; i < n; i++)
			cin >> a[i];
		for (int i = 0; i < n; i++) {
			inverse[a[i] - 1] = i;
		}
		while (cin >> k) {
			if (k == 0)
				break;
			string s;
			getline(cin, s);
			s.erase(s.begin());
			f(s);
		}
		cout << endl;
	}
	system("pause");
}