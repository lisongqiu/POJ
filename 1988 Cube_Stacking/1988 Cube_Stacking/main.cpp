#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>

using namespace std;

#define MAXN 40000
#define MAXP 100001

int p;
int par[MAXN];
int sum[MAXN];
int under[MAXN];

int findPar(int a) {
	if (par[a] == a)
		return a;
	int t = findPar(par[a]);
	under[a] += under[par[a]];
	par[a] = t;
	return par[a];
}

void move(int a, int b) {
	//move a on top of b.
	int pa = findPar(a);
	int pb = findPar(b);
	if (pa == pb)
		return;
	under[pa] = sum[pb];
	sum[pb] += sum[pa];
	par[pa] = pb;
	return;
}

int main() {
	//init child array.
	for (int i = 0; i < MAXN; i++) {
		par[i] = i;
		sum[i] = 1;
		under[i] = 0;
	}
	//get input.
	cin >> p;
	char op;
	int a, b;
	while (p--) {
		cin >> op;
		if (op == 'M') {
			cin >> a >> b;
			move(a, b);
		}
		else if (op == 'C') {
			cin >> a;
			findPar(a); //Here!!!!!!!!!!!!!!!
			cout << under[a] << endl;
		}
	}
	system("pause");
	return 0;
}

/*
Sample Input

6
M 1 6
C 1
M 2 4
M 2 6
C 3
C 4

*/