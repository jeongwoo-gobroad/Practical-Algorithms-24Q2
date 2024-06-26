// KNU CSE 2021114026 Jeongwoo Kim
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/* since it is just performing complete DFS, we don't have to implement the tree. just stack here */
static int counter = 0;

bool okay(const vector<int>& v, int curRow, int addCol) {
    for (int i = 1; i < curRow; i++) {
        /* there are 4 possible ways to determine whether a set of points is in a diagonal position */
        if (v[i] == addCol || abs(v[i] - addCol) == abs(i - curRow)) {
            return false;
        }
    }

    return true;
}

void createTree(vector<int>& v, int row, int n) {
    if (row > n) {
        counter++;
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (okay(v, row, i)) {
            v.push_back(i);
            createTree(v, row + 1, n);
            v.pop_back();
        }
    }
}

int main(void) {
    int nq;
    vector<int> vec;

    vec.push_back(0);
    
    cin >> nq;
    
    createTree(vec, 1, nq);

    cout << counter;

    return 0;
}