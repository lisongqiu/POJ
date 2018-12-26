#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>

using namespace std;

struct Node {
	int left, right;
	Node(){}
	Node(int l, int r) :left(l), right(r) {}
};

bool opt(Node& a, Node& b) {
	return a.left < b.left;
}

const int MAXN = 50001;
const int RANGE = 10001;
vector<Node> nodes;
int n;

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		Node tmp;
		cin >> tmp.left >> tmp.right;
		nodes.push_back(tmp);
	}
	sort(nodes.begin(), nodes.end(), opt);
	int left = nodes[0].left;
	int right = nodes[0].right;
	int ptr = 1;
	while (ptr < n) {
		if (nodes[ptr].left > right)
			break;
		right = max(nodes[ptr].right, right);
		ptr++;
	}
	if (ptr < n)
		cout << "no" << endl;
	else
		cout << left << " " << right << endl;
	system("pause");
}