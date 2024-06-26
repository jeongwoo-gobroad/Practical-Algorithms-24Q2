// KNU CSE 2021114026 Jeongwoo Kim
// AX11, P03: 0/1 Knapsack with Backtracking, advanced pruning
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <tuple>

#define weight   get<0>
#define profit   get<1>
#define unitprof get<2>

using namespace std;

/* weight - profit - unitprof */
typedef tuple<int, int, int> items;

int n, w;
int optimalValue;
vector<int> optimalSol;
vector<items> knapsack;

bool myCompare(items s, items o) {
    return unitprof(s) > unitprof(o);
}

bool isPromising(const int& index, const int& localProfit, const int& localWeight, const vector<int>& set) {
    /* isPromising: Is there any necessities to search further? */
    int cursor = 1;
    int        upperBoundByGreedyApproach = localProfit - profit(knapsack[index]);
    int lowerWeightBoundByZeroOneApproach = localWeight - weight(knapsack[index]);
    /* Key idea(important): DO WE NEED TO PROGRESS FURTHER FROM "ME"? */
    /* I'm added BEFORE, I'm evaluated NOW! */

    /* setting upper bound greedly */
    /* note: chosen 'index' is added at the next node. */
    /* so we start to grab greedly from this very node: including this node is not determined */
    /* +) improving efficieny of pruning with reducing tree depth if not possible */
    /* +) and getting rid of possibilities that would cause overflow */

    /* #1: non-fractional */
    for (cursor = index; cursor <= n; cursor++) {
        if (lowerWeightBoundByZeroOneApproach + weight(knapsack[cursor]) >= w) {
            break;
        }
        lowerWeightBoundByZeroOneApproach += weight(knapsack[cursor]);
        upperBoundByGreedyApproach += profit(knapsack[cursor]);
    }
    /* #2: fractional */
    if (cursor != n + 1) {
        //cout << "Index: " << cursor << " is target: " << (w - lowerWeightBoundByZeroOneApproach) * unitprof(knapsack[cursor]) << endl;
        upperBoundByGreedyApproach += (w - lowerWeightBoundByZeroOneApproach) * unitprof(knapsack[cursor]);
    }

    /* i weight profit bound maxprofit */
    cout << index << " " << localWeight << " " << localProfit << " " <<
        upperBoundByGreedyApproach << " " << optimalValue << "\n";
    
    /* no need to go further if: 1. bound is under current opt.val 2. no more index 3. localweight is same to or exceeds w */
    if (upperBoundByGreedyApproach < optimalValue || index == n || localWeight >= w) {
        return false;
    }

    return true;
}

void solve(int index, int localProfit, int localWeight, vector<int> include) {
    /* :::::::Evaluation of previous case is done right here */
    //cout << "Evaluating: " << index << " of " << localProfit << ", " << localWeight << endl;
    if (localProfit > optimalValue && localWeight <= w) {
        optimalSol = include;
        optimalValue = localProfit; /* update condition */
    }

    /* Important: evaluation of a case is done in the next(child) node */
    /* Why? Since it is a state space tree, a node only does determine that the next node includes the very node or not. */
    /* This is just a simple concept when it comes to a state space problem, but in here, like optimization problems, */
    /* It is notable that evaluation is done in the next node. */
    /* And to increase the efficiency of this algorithm, we let an "upper bound", which determines */
    /* There is necessities to search further for more possibilities. */

    /* Is there any necessities to search further? */
    if (isPromising(index, localProfit, localWeight, include)) { /* if so, then */
        /* do include */
        include[index + 1] = 1;
        solve(index + 1, localProfit + profit(knapsack[index + 1]), localWeight + weight(knapsack[index + 1]), include);
        /* do not include */
        include[index + 1] = 0;
        solve(index + 1, localProfit, localWeight, include);
    }

    return;
}

int main(void) {
    int input; int notFirst = 0;
    vector<int> wei;
    vector<int> prof;
    vector<int> chooseTable;

    cin >> n;
    cin >> w;

    chooseTable.resize(n + 1, 0);

    for (int i = 0; i < n; i++) {
        cin >> input;
        wei.push_back(input);
    }

    for (int i = 0; i < n; i++) {
        cin >> input;
        prof.push_back(input);
    }

    knapsack.push_back(make_tuple(0, 0, 0));
    for (int i = 0; i < n; i++) {
        knapsack.push_back(make_tuple(wei[i], prof[i], prof[i] / wei[i]));
    }
    /* to avoid divided by zero */
    sort(knapsack.begin() + 1, knapsack.end(), myCompare);
    
    solve(0, 0, 0, chooseTable);

    cout << optimalValue;
    for (int i = 1; i <= n; i++) {
        if (optimalSol[i]) {
            cout << "\n";
            cout << weight(knapsack[i]) << " " << profit(knapsack[i]);
        }
    }

    return 0;
}