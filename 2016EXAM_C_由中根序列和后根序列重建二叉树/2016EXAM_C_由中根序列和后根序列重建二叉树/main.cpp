#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>

using namespace std;

vector<int> v;

void func(int s1, int e1, int s2, int e2) {
	if (s1 > e1)
		return;
	cout << v[e2] << " ";
	if (s1 == e1)
		return;
	int div = s1;
	while (v[div] != v[e2])
		div++;
	func(s1, div - 1, s2, s2 + (div - 1 - s1));
	func(div + 1, e1, s2 + (div - s1), e2 - 1);
	return;
}

int main() {
	int tmp;
	while (cin >> tmp)
		v.push_back(tmp);
	func(0, v.size() / 2 - 1, v.size() / 2, v.size() - 1);
	cout << endl;
	system("pause");
	return 0;
}
