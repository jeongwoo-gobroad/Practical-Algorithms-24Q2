// KNU CSE 2021114026 Jeongwoo Kim
// AX12, P02: TSP Problem with Dynamic Program Table Method
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <cmath>

#define INF 99999999

using namespace std;

typedef vector<vector<int>> mat;
typedef int set;

mat adj;
mat dpTable_val;
/* IMPORTANT: dptable_val[i][A] means the shortest path that sum of i to j to 1 is minimized. */
/* Why we do so? DP is based on the 'Optimal Substructure Theorem', so each A stands for possible subsets of V, so that Vi to A means local optimal */
/* Row index := initial vertex, Col index := possible partial state space WITH OPTIMIZED ORDER, element := local optimal value */
/* Plus: expression of set A is achieved via SUBFIELD ENCODING, in which every bit stands for the existence of an element corresponding to its bit significance */
/* Plus: we have to search for a circuit, so [i][0](A = {0}) means 1 to j to 1 */
mat dpTable_sol;
int n;

bool alreadyExists(set a, int what) {
    return a & (1 << (what - 2)); /* since we have excluded V1. */
}

set addGivenIndex(set target, int what) {
    target |= (1 << (what - 2));

    return target;
}

set delGivenIndex(set target, int what) {
    target = target & ~(1 << (what - 2));

    return target;
}

int get_optimal_j(set whatA, int arrival) {
    int localOptVal = INF;
    int localOptSol = 0;
    int temp;

    for (int temp_j = 2; temp_j <= n; temp_j++) {
        if (temp_j != arrival && alreadyExists(whatA, temp_j)) { /* only proceed if not the same */
            temp = delGivenIndex(whatA, temp_j);
            if (adj[arrival][temp_j] + dpTable_val[temp_j][temp] < localOptVal) {
                localOptVal = adj[arrival][temp_j] + dpTable_val[temp_j][temp];
                localOptSol = temp_j;
            }
        }
    }

    /* finalize */
    dpTable_val[arrival][whatA] = localOptVal;

    return localOptSol;
}

int get_count(set target) {
    int eleCnt = 0;

    while (target) {
        if (target & 1 == 1) {
            eleCnt++; /* only if an element has found */
        }
        target = target >> 1;
    }

    return eleCnt;
}

void printPath(int row, int col) {
    if (col == 0) {
        cout << "1";
        return;
    }
    else {
        cout << dpTable_sol[row][col] << " ";
        printPath(dpTable_sol[row][col], delGivenIndex(col, dpTable_sol[row][col]));
    }

    return;
}

void solve(void) {
    /* Pseudo-code:
        Important: operation is being done in reverse order
            Procedure preProcessing:
                set dpTable_val[i][0] as adj[i][1];
            Procedure Filling_DP_Tables:
                for As in element count range of 1 to (n - 2) #No 1, No End
                    for i in range 2 to n
                        for j in range 2 to n
                            choose optimal j in given A to minimize overall weight to the i
                            that makes i -> j -> 1 loop
                        write to solution table that j has chosen when considering A and i
            Procedure make_Circuit:
                choose optimal j in last A to minimize overall weight to the 1
                that makes 1 -> j -> 1 loop #Circuit has made
                write to solution table that j has chosen when considering A and 1
    */
    int maxSetCount = pow(2, n - 1); /* why n - 1?: we do not consider vertex 1 */
    int tempVia;

    for (int i = 2; i <= n; i++) {
        dpTable_val[i][0] = adj[i][1];
    }
    for (int eleCnt = 1; eleCnt <= n - 2; eleCnt++) { /* since we excluded 1, and table[i][A] is a path of i to j to 1 */
        for (set a = 1; a < maxSetCount - 1; a++) {
            if (get_count(a) != eleCnt) {
                continue; /* to calculate in the sequence */
            }
            else {
                for (int arriveTo = 2; arriveTo <= n; arriveTo++) {
                    if (!alreadyExists(a, arriveTo)) { /* only if chosen arriveTo index is not in A */
                        tempVia = get_optimal_j(a, arriveTo);
                        dpTable_sol[arriveTo][a] = tempVia;
                    }
                }
            }
        }
    }

    /* make circuit */
    tempVia = get_optimal_j(maxSetCount - 1, 1);
    dpTable_sol[1][maxSetCount - 1] = tempVia;

    /* printing optimal value */
    cout << dpTable_val[1][maxSetCount - 1]; /* why maxSetCount - 1? */
                                             /* number of element: maxSetCount */
                                             /* maxSetCount - 1: represents "all vertices considered" */

    cout << "\n1 ";
    /* printing optimal solution */
    printPath(1, maxSetCount - 1);

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= maxSetCount; j++) {
            if (dpTable_val[i][j] != INF) {
                cout << "\n";
                cout << i << " " << j << " " << dpTable_val[i][j];
            }            
        }
    }

    return;
}

void setMats(void) {
    int powNum = pow(2, n - 1);

    adj.resize(n + 1, vector<int>(n + 1, INF));
    dpTable_val.resize(n + 1, vector<int>(powNum + 1, INF));
    dpTable_sol.resize(n + 1, vector<int>(powNum + 1, INF));

    return;
}

int main(void) {
    int cnt;
    int tmp_from, tmp_to, tmp_weight;

    cin >> n;
    cin >> cnt;

    setMats();

    for (int i = 0; i < cnt; i++) {
        cin >> tmp_from;
        cin >> tmp_to;
        cin >> tmp_weight;
        adj[tmp_from][tmp_to] = tmp_weight;
    }

    solve();

    return 0;
}