#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

#define MAXN 1000010
char s[MAXN];
int slen;
int nexts[MAXN];

void getNexts() {
	nexts[0] = -1;
	int i = 0;
	int k = -1;
	while (i < slen) {
		while (k >= 0 && s[i] != s[k])
			k = nexts[k];
		i++;
		k++;
		nexts[i] = k;
	}
	return;
}

int main() {
	while (~scanf("%s", s)) {
		slen = strlen(s);
		if (slen == 1 && s[0] == '.')
			break;
		getNexts();
		/*
		for (int i = 0; i <= slen; i++)
			cout << nexts[i] << " ";
		cout << endl;
		*/
		int res = 1;
		if (slen % (slen - nexts[slen]) == 0)
			res = slen / (slen - nexts[slen]);
		printf("%d\n", res);
	}
	system("pause");
	return 0;
}