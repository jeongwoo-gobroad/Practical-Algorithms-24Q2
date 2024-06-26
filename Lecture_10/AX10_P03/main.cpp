// KNU CSE 2021114026 Jeongwoo Kim
// AX10_P03: m-coloring problem.
#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> color_pair; /* index: vertex value: color */
vector<vector<int>> adj;
int minimalColor = 1;
int cnt = 0;

bool isOptimal(int vtx) {
    for (int i = 1; i < vtx; i++) {
        if (adj[i][vtx] && color_pair[i] == color_pair[vtx]) {
            return false;
            /* Greedy-like approach */
            /* if new one is connected and has same color then fail */
            /* why is this so simple?: */
            /* Partial State Space is defined as [candidate, candidate solution] */
        }
    }

    return true;
}

void solve(int vtx, int n) {
    if (isOptimal(vtx)) {
        if (vtx == n) {
            cnt++;
            return;
        }
        for (int i = 1; i <= minimalColor; i++) {
            color_pair[vtx + 1] = i;
            solve(vtx + 1, n);
        }
    }
}

int main(void) {
    int n;
    int e;

    cin >> n >> e;

    color_pair.resize(n + 1, 0);
    adj.resize(n + 1, vector<int>(n + 1, 0)); 

    for (int i = 0; i < e; i++) {
        int from, to;

        cin >> from >> to;
        adj[from][to] = 1;
        adj[to][from] = 1; /* undirected, unweighted */
    }

    while (cnt == 0) {
        cnt = 0;
        minimalColor++;
        solve(0, n); /* start from the root. you know why? */
    }

    cout << minimalColor << "\n" << cnt;
    
    return 0;
}