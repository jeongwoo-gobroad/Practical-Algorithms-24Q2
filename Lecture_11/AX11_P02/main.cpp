// KNU CSE 2021114026 Jeongwoo Kim
// AX11, P02: 0/1 Knapsack with Dynamic Programming
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <tuple>
#include <map>

using namespace std;

/*         profit weight */
typedef pair<int, int> items;
/*          index weight */
typedef pair<int, int> pseudoMatrix;
typedef tuple<int, int, int> result;

int n;

vector<items> mybag;
vector<vector<int>> table;
vector<result> res;
map<pseudoMatrix, int> dp;

bool ordering(items s, items o) {
    return (s.first / s.second) > (o.first / o.second);
} /* ordering items in non-increasing order based on Profit Per Weight */

int solve(int index, int partialWeight) {
    int notIncludingCurrentIndex = 0; /* lvalue */
    int    doIncludeCurrentIndex = 0; /* rvalue */

    if (partialWeight <= 0 || index < 1) {
        return 0;
    }

    if (dp.end() == dp.find(make_pair(index - 1, partialWeight))) {
        dp[make_pair(index - 1, partialWeight)] = solve(index - 1, partialWeight);
    }
    notIncludingCurrentIndex = dp[make_pair(index - 1, partialWeight)];

    if (partialWeight - mybag[index].second >= 0) {
        if (dp.end() == dp.find(make_pair(index - 1, partialWeight - mybag[index].second))) {
            dp[make_pair(index - 1, partialWeight - mybag[index].second)] = solve(index - 1, partialWeight - mybag[index].second);
        }
        doIncludeCurrentIndex = dp[make_pair(index - 1, partialWeight - mybag[index].second)] + mybag[index].first;

        if (notIncludingCurrentIndex < doIncludeCurrentIndex) {
            return doIncludeCurrentIndex;
        }
    }

    return notIncludingCurrentIndex;
}

int main(void) {
    int input;
    int w;

    vector<int> profits;
    vector<int> weights;
    vector<int> cases;

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> input;
        weights.push_back(input);
    }
    for (int i = 0; i < n; i++) {
        cin >> input;
        profits.push_back(input);
    }

    mybag.push_back(make_pair(0, 0));
    for (int i = 0; i < n; i++) {
        mybag.push_back(make_pair(profits[i], weights[i]));
    }
    /* to avoid divided by zero err */
    sort(mybag.begin() + 1, mybag.end(), ordering);

    /*
    for (const auto& i: mybag) {
        cout << i.first << " " << i.second << endl;
    }
    */

    cin >> w;

    for (int i = 0; i < w; i++) {
        cin >> input;
        cases.push_back(input);
    }

    /* computing */
    for (int i = 0; i < w; i++) {
        int temp = dp[make_pair(n, cases[i])] = solve(n, cases[i]);
        cout << temp;
        for (const auto& p: dp) {
            if (p.first.first == 0 || p.first.second == 0) continue;
            cout << "\n";
            cout << p.first.first << " " << p.first.second << " " << p.second;
        }
        if (i != w - 1) {
            cout << "\n";
        }
        dp.clear();
    }

    return 0;
}