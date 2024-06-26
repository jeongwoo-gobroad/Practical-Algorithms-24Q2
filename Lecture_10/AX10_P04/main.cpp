// KNU CSE 2021114026 Jeongwoo Kim
// AX10_P04: Hamiltonian Circuits
#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

int cnt = 0;
vector<vector<int>> adj;
vector<int> circuit; /* State Space: <nth visit, node type> */

bool isOptimal(int cur, const int& len, const int& n) {
    /* not root AND adj[previous_chosen_vertex][greedy_like] != 1 */
    if (len > 0 && adj[circuit[len - 1]][cur] != 1) {
        return false; /* not connected to the previous one */
    }
    if (len == n - 1 && adj[cur][1] != 1) {
        return false; /* cannot go back to the first one */
    }
    for (int i = 0; i < len; i++) {
        if (circuit[i] == cur) return false;
        /* makes cycle */
    }

    return true;
}

void solve(int targetVertex, int len, const int& n) {
    if (isOptimal(targetVertex, len, n)) {
        if (len == n - 1) {
            /* but why exactly "n - 1"? */
            /* we let var len as count of chosen vertices, */
            /* while vertex 1 is preserved as start root. */
            /* so, count should be n - 1 */
            cnt++;
            return;
        }
        for (int i = 2; i <= n; i++) {
            /* make nth visit as i */
            circuit[len + 1] = i;
            solve(i, len + 1, n);
        }
    }
}

int main(void) {
    int v, e;

    cin >> v >> e;

    adj.resize(v + 1, vector<int>(v + 1, 0));
    circuit.resize(v + 1, 0);

    for (int i = 0; i < e; i++) {
        int from, to;

        cin >> from >> to;
        adj[from][to] = 1;
        adj[to][from] = 1;
        /* undirected, unweighted */
    }

    circuit[0] = 1;
    solve(0, 0, v); /* always start from the root */

    cout << cnt;
    
    return 0;
}