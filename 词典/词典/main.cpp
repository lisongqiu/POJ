#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<vector>
#include<stdio.h>
#include<string.h>

using namespace std;

#define MAX_WORD 11
#define MAXN 100010

struct Item {
	char src[MAX_WORD];
	char tgt[MAX_WORD];
};

bool cmp(const Item& a, const Item& b){
	return strcmp(a.src, b.src) < 0;
}

Item items[MAXN];

int midSearch(char* ref, int maxLen) {
	int begin = 0, end = maxLen - 1;
	while (begin <= end) {
		int mid = (begin + end) / 2;
		int res = strcmp(ref, items[mid].src);
		if (res == 0)
			return mid;
		else if (res < 0)
			end = mid - 1;
		else
			begin = mid + 1;
	}
	return -1;
}

int main() {
	char input[30];
	int n = 0;
	while (fgets(input, 30, stdin), input[0] != '\n') {
		sscanf(input, "%s%s", items[n].tgt, items[n].src);
		n++;
	}
	sort(items, items+n, cmp);
	while (scanf("%s", input) == 1) {
		int res = midSearch(input, n);
		if (res != -1)
			printf("%s\n", items[res].tgt);
		else
			printf("eh\n");
	}
	system("pause");
}