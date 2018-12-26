#define _CRT_SECURE_NO_DEPRECATE

#include<iostream>
#include<algorithm>
#include<string>
#include<cstdio>
#include<cstring>

using namespace std;

#define MAXN 10010
#define MAXM 1000100

int N;
char W[MAXN], T[MAXM];
int lenW, lenT;
int nexts[MAXN];

void buildNext() {
	//cout << "buildNext: " << P << endl;
	int i = 0;
	int k = -1;
	nexts[0] = -1;
	while (i < lenW) {
		while (k >= 0 && W[k] != W[i])
			k = nexts[k];
		i++;
		k++;
		if (W[k] == W[i])
			nexts[i] = nexts[k];
		else
			nexts[i] = k;
	}
	/*
	for (int i = 0; i <= lenW; i++)
		cout << nexts[i] << " ";
	cout << endl;
	*/
	return;
}

int kmp() {
	//cout << "kmp: " << P << " " << T << endl;
	int pi = 0, ti = 0;
	int res = 0;
	while (ti < lenT) {
		if (pi < 0 || W[pi] == T[ti]) {
			pi++;
			ti++;
			if (pi == lenW) {
				res++;
				pi = nexts[lenW];
			}
		}
		else
			pi = nexts[pi];
	}
	return res;
}

int main() {
	cin >> N;
	while (N--) {
		/*
		Note: Using 'cin' will lead to TLE.
		*/
		scanf("%s", W);
		scanf("%s", T);
		lenW = strlen(W);
		lenT = strlen(T);
		buildNext();
		cout << kmp() << endl;
	}
	system("pause");
	return 0;
}