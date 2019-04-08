#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>
#include <stack>

using namespace std;

#define MAXN 10010
#define MAXM 50010

int N, M;
vector<int> edges[MAXN];
vector<int> reverses[MAXN];
bool visited[MAXN];
vector<int> orders;
int idx = 0;
int sccs[MAXN];
int degrees[MAXN];

void dfs(int s) {
    if (visited[s])
        return;
    visited[s] = true;
    for (int i = 0; i < edges[s].size(); i++)
        dfs(edges[s][i]);
    orders.push_back(s);
    return;
}

bool reDfs(int s) {
    if (sccs[s] != -1)
        return false;
    sccs[s] = idx;
    for (int i = 0; i < reverses[s].size(); i++)
        reDfs(reverses[s][i]);
    return true;
}

int main() {
    cin >> N >> M;
    int a, b;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        edges[a].push_back(b);
        reverses[b].push_back(a);
    }
    // kosaraju algorithm.
    memset(visited, 0, sizeof(visited));
    for (int i = 1; i <= N; i++)
        dfs(i);
    // revisit graph.
    idx = 0;
    memset(sccs, -1, sizeof(sccs));
    for (int i = N - 1; i >= 0; i--) {
        if (reDfs(orders[i]))
            idx++;
    }
    // build SCC graph.
    memset(degrees, 0, sizeof(degrees));
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            if(sccs[edges[i][j]]!=sccs[i])
                degrees[sccs[i]]++;
        }
    }
    int res = -1;
    for (int i = 0; i < idx; i++) {
        if (degrees[i] == 0) {
            if (res == -1)
                res = i;
            else {
                res = -1;
                break;
            }
        }
    }
    if (res == -1)
        cout << 0 << endl;
    else {
        int cnt = 0;
        for (int i = 1; i <= N; i++)
            if (sccs[i] == res)
                cnt++;
        cout << cnt << endl;
    }
    return 0;
}
