#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<math.h>
#include<cstring>
using namespace std;

const int MAXN = 201;
int T, n;
int boxes[MAXN];
int colors[MAXN];
int counts[MAXN];
int rewards[MAXN][MAXN][MAXN];

int recurse(int start, int end, int len) {
	//cout << "RECURSION:" << start << " " << end << " " << len << endl;
	if (rewards[start][end][len] > 0) // !!!!!!!!!!!!!!!!!!!!!!!!!!
		return rewards[start][end][len];
	int result = counts[end] + len;
	result = result * result;
	if (start == end) {
		rewards[start][end][len] = result;
		return result;
	}
	result += recurse(start, end - 1, 0);
	//if merge with left one.
	for (int i = end-1; i >= start; i--) { // loop from the right to the left with 'break' used where the left cases are covered when the suitable one is found.
		if (colors[i] != colors[end])
			continue;
		int temp = recurse(start, i, counts[end] + len) + recurse(i + 1, end - 1, 0);
		if (temp <= result)
			continue;
		result = temp;
		break;
	}
	rewards[start][end][len] = result;
	return result;
}

int main() {
	int cnt = 0;
	cin >> T;
	while (cnt < T) {
		cnt += 1;
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> boxes[i];
		int idx = 0, blockIdx = 0, blockLen = 1;
		while (idx < n) {
			if (idx == n - 1 || (boxes[idx] != boxes[idx + 1])) {
				colors[blockIdx] = boxes[idx];
				counts[blockIdx] = blockLen;
				blockIdx += 1;
				blockLen = 1;
			}
			else
				blockLen += 1;
			idx += 1;
		}
		memset(rewards, 0, sizeof(rewards));

		cout << "Case " << cnt << ": ";
		cout << recurse(0, blockIdx-1, 0) << endl;
	}
	system("pause");
}
