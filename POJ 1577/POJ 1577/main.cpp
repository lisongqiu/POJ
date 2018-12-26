#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>
#include<string>

using namespace std;

struct node {
	char name;
	node *left, *right;
	node() { this->left = NULL; this->right = NULL; }
	node(char n, node* l, node* r) { this->name = n; this->left = l; this->right = r; }
};

vector<string> buf;

void func() {
	node* root;
	root = new node(buf[buf.size() - 1][0], NULL, NULL);
	for (int i = buf.size() - 2; i >= 0; i--) {
		//cout << buf[i] << endl;
		for (int j = 0; j < buf[i].size(); j++) {
			//cout << buf[i][j] << endl;
			char c = buf[i][j];
			node* ptr = root;
			while (true) {
				if (ptr->right && c > ptr->name)
					ptr = ptr->right;
				else if (ptr->left && c < ptr->name)
					ptr = ptr->left;
				else
					break;
			}
			if (c > ptr->name)
				ptr->right = new node(c, NULL, NULL);
			else
				ptr->left = new node(c, NULL, NULL);
		}
	}
	stack<node*> stk;
	stk.push(root);
	while (!stk.empty()) {
		node* tmp = stk.top();
		stk.pop();
		if (tmp == NULL)
			continue;
		cout << tmp->name;
		stk.push(tmp->right);
		stk.push(tmp->left);
		delete tmp;
	}
	cout << endl;
	return;
}


int main() {
	string input;
	while (cin >> input) {
		if (input == "*") {
			func();
			buf.clear();
			continue;
		}
		else if (input == "$") {
			func();
			break;
		}
		buf.push_back(input);
	}
	system("pause");
	return 0;
}

/*
Sample Input

BDHPY
CM
GQ
K
*
AC
B
$

*/