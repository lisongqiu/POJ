#include<iostream>
#include<stack>
#include<vector>

using namespace std;

const int MAXN = 1001;
int T, n;
int	a[MAXN];

int main() {
	cin >> T;
	while (T--) {
		stack<int> input;
		stack<int> output;
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> a[i];
		for (int i = n; i >= 1; i--)
			input.push(i);
		int ptr = 0;
		while (!input.empty()) {
			if (!output.empty() && output.top() == a[ptr]) {
				output.pop();
				ptr++;
				continue;
			}
			output.push(input.top());
			input.pop();
		}
		while (!output.empty()) {
			if (output.top() != a[ptr])
				break;
			output.pop();
			ptr++;
		}
		if (output.empty())
			cout << "yes" << endl;
		else
			cout << "no" << endl;
	}
	system("pause");
}