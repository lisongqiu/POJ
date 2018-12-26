#define _CRT_SECURE_NO_DEPRECATE

#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

#define MAXN 100010

int par[MAXN];
int rel[MAXN];
int T;
int N, M;

int getPar(int a) {
	//cout << "getPar: " << a << endl;
	if (par[a] == a)
		return a;
	int t = par[a];
	par[a] = getPar(par[a]);
	rel[a] = (2 + rel[a] + rel[t]) % 2;
	return par[a];
}

void merge(int a, int b) {
	int pa = getPar(a);
	int pb = getPar(b);
	if (pa == pb)
		return;
	par[pa] = pb;
	rel[pa] = (2 + rel[a] + rel[b] + 1) % 2;
	return;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &N, &M);
		char op;
		int a, b;
		//init.
		for(int i=1;i<=N;i++){
			par[i] = i;
			rel[i] = 0;
		}
		while (M--) {
			scanf(" %c%d%d", &op, &a, &b);
			//cin >> op >> a >> b;
			if (op == 'D')
				merge(a, b);
			else {
				int pa = getPar(a);
				int pb = getPar(b);
				if (pa == pb) {
					if (rel[a] == rel[b])
						cout << "In the same gang." << endl;
					else
						cout << "In different gangs." << endl;
				}
				else {
					cout << "Not sure yet." << endl;
				}
			}
		}
	}
	system("pause");
	return 0;
}