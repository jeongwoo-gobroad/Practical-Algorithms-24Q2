// KNU CSE 2021114026 Jeongwoo Kim
// AX09_P03: Representation of an integer into unique combination of fibonacci numbers
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <stack>

using namespace std;

typedef unsigned long long ull;

ull
returnSameOrLessFibNum(ull t) { /* Greedy */
    ull a, b, c, rtn;
    a = 0, b = 1, c = 1;

    do {
        rtn = c;
        c = b + a;
        a = b;
        b = c;
    } while (c <= t);

    return rtn;
}

void
solve(ull until) {
    ull temp;

    stack<ull> ans;

    while (until) { /* Greedy */
        temp = returnSameOrLessFibNum(until);
        ans.push(temp);
        until -= temp;
    }

    while (!ans.empty()) {
        cout << ans.top();
        ans.pop();
        if (!ans.empty()) {
            cout << "\n";
        }
    }

    return;
}

int
main(void) {
    ull input;

    cin >> input;

    solve(input);

    return 0;
}