#define _CRT_SECURE_NO_DEPRECATE

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <string.h>

using namespace std;

#define MAXN 110

int N;
vector<int> edges[MAXN];
int nidx;
int dfn[MAXN];
int low[MAXN];
int par[MAXN];
int rcnts[MAXN];

void init() {
    nidx = 0;
    for (int i = 1; i <= N; i++)
        edges[i].clear();
    memset(dfn, -1, sizeof(dfn));
    memset(low, -1, sizeof(low));
    memset(par, -1, sizeof(par));
    memset(rcnts, 0, sizeof(rcnts));
    return;
}

void tarjan(int s, int p) {
    if (dfn[s] != -1)
        return;
    par[s] = p;
    rcnts[p]++;
    dfn[s] = low[s] = ++nidx;
    for (int i = 0; i < edges[s].size(); i++) {
        int v = edges[s][i];
        if (dfn[v] == -1) {
            tarjan(v, s);
            low[s] = min(low[s], low[v]);
        } else
            low[s] = min(low[s], dfn[v]);
    }
    return;
}

int count() {
    int res = 0;
    for (int i = 1; i <= N; i++) {
        if (par[i] == i) {
            // if root.
            if (rcnts[i] >= 3)
                res++;
        } else {
            // otherwise.
            for (int j = 0; j < edges[i].size(); j++) {
                int v = edges[i][j];
                if (par[v] == i && dfn[i] <= low[v]) {  // note here!  par[v]==i !!!
                    res++;
                    break;
                }
            }
        }
    }
    return res;
}

int main() {
    while (scanf("%d", &N) && N) {
        init();
        int a, b;
        while (scanf("%d", &a) && a) {
            while (getchar() != '\n') {
                scanf("%d", &b);
                edges[a].push_back(b);
                edges[b].push_back(a);
            }
        }
        for (int i = 1; i <= N; i++)
            tarjan(i, i);
        printf("%d\n", count());
    }
    system("pause");
    return 0;
}
