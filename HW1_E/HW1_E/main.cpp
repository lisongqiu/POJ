#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

vector<int> vec;
vector<int> mid;
vector<int> post;

void divide(int root, int left, int right) {
	//cout << "NOW: " << root << " " << left << " | " << right << endl;
	if (root < 0 || root >= post.size() || right < left)
		return;
	cout << post[root] << " ";
	int cnt;
	for (cnt = 0; cnt <= right - left; cnt++)
		if (mid[left + cnt] == post[root])
			break;
	if (left != right) {
		int newRoot = root - (right - left - cnt + 1);
		divide(newRoot, left, left + cnt - 1);
		divide(root - 1, left + cnt + 1, right);
	}
}

int main() {
	int tmp;
	while (cin >> tmp)
		vec.push_back(tmp);
	for (int i = 0; i < vec.size() / 2; i++)
		mid.push_back(vec[i]);
	for (int i = vec.size() / 2; i < vec.size(); i++)
		post.push_back(vec[i]);
	divide(post.size() - 1, 0, post.size() - 1);
	cout << endl;
	system("pause");
}