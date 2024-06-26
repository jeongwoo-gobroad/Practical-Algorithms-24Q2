// KNU CSE 2021114026 Jeongwoo Kim
// AX10_P01: An N-Queens Problem
#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

typedef unsigned long long ull;

ull msv = 0; /* most_significant_value */
int cnt = 0;  /* counter */

string vectorToString(vector<int> target) {
    string rtn;

    for (int i = target.size() - 1; i >= 1; i--) {
        rtn.push_back(target.back());
        target.pop_back();
    }

    cout << rtn;

    return rtn;
}

ull vectorToInt(vector<int> target) {
    ull rtn = 0;
    ull pownum = 1;

    for (int i = target.size() - 1; i >= 1; i--) {
        rtn += (ull)target[i] * (ull)pownum;
        pownum *= 10;
        if (target[i] / 10 == 1) { /* if two digits */
            pownum *= 10;
        }
    }

    return rtn;
}



bool isOptimal(const vector<int>& bd, int row) {
    for (int i = 1; i < row; i++) {
        /* if col is same OR are in diagonal position (identical rows have been eliminated since its ADT) */
        if (bd[i] == bd[row] || abs(i - row) == abs(bd[i] - bd[row])) {
            return false;
        }
    }

    return true;
}

void solve(vector<int>& bd, int row, const int& n) {
    /* pruning */
    if (isOptimal(bd, row)) {
        if (row == n) {
            if (vectorToInt(bd) > msv) {
                msv = vectorToInt(bd);
            }
            cnt++;
            return;
        }
        for (int i = 1; i <= n; i++) {
            /* important: vector simulates graph traverse. but how? */
            /* each node of state space stands for a pair of (argument, POSSIBLE value->partial candidate solution) */
            /* argument is fixed, while the latter one is not determined nor single solution. */
            /* so we let the index mean argument, value mean p.c.s. */
            bd.push_back(i);
            solve(bd, row + 1, n);
            bd.pop_back();
        }
    }

    return;
}

int main(void) {
    int n;
    vector<int> chessBoard;

    cin >> n;

    chessBoard.push_back(0);
    solve(chessBoard, 0, n); /* always start from the root */

    cout << cnt << "\n" << msv;

    return 0;
}