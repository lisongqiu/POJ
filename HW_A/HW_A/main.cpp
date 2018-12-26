#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

const int MAXL = 500;
string str;

int main() {
	getline(cin, str);
	int ptr = 0;
	while (ptr < str.length()) {
		//cout << ptr << endl;
		if (str[ptr] == ' ') {
			cout << str[ptr];
			ptr++;
			continue;
		}
		int end = ptr + 1;
		while (end < str.length()) {
			if (str[end] == ' ')
				break;
			end++;
		}
		//cout << end << endl;
		for (int i = end - 1; i >= ptr; i--) {
			cout << str[i];
		}
		ptr = end;
	}
	system("pause");
}