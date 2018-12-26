#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>

using namespace std;

int n;
char a, b, c;

void hanoi(int idx, int num, char src, char tgt, char from) {
	//cout << idx << "-" << num << "-" << src << "-" << tgt << "-" << from << endl;
	if (num == 1) {
		cout << idx << ":" << src << "->" << tgt << endl;
		return;
	}
	hanoi(idx - 1, num - 1, src, from, tgt);
	hanoi(idx, 1, src, tgt, from);
	hanoi(idx - 1, num - 1, from, tgt, src);
}

int main() {
	cin >> n;
	cin >> a >> b >> c;
	hanoi(n, n, a, c, b);
	system("pause");
}