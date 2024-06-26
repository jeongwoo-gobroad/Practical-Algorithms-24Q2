// KNU CSE 2021114026 Jeongwoo Kim
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void solve(int n, int k) {
    /* simulates Circular Linked List, but how? */
    int cur = k;
    vector<int> arr(n + 1, 1);

    for (int i = 1; i <= n; i++) {
        arr[i] = i; /* yeah... this seems ok. but why? Doesn't index itself mean data? */
        /* here's why:  if you delete an element in your vector, index will be shrinked.*/
        /* so, index has no meanings, only data does. */
    }

    cout << "<";
    while (arr.size() != 1) {
        cout << arr[cur]; /* data has the meaning */
        arr.erase(arr.begin() + cur); /* added number in the iterator means "th" element. */
        /* so arr.begin() + 1 == arr[0] */
        if (arr.size() != 1) { /* exit condition */
            cout << ", ";
        }
        else {
            break;
        }
        cur += k - 1; /* wtf: k means k'th' student, so movement(action) is k - 1. */
        cur %= (arr.size() - 1); /* to get exact information of original circular size */
        if (cur == 0) {
            /* to be more specific: arr[0] is not for use. */
            cur = arr.size() - 1; /* points out the end of the vector */
        }
    }
    cout << ">";
}

int main(void) {
    int input, k;

    cin >> input >> k;

    solve(input, k);

    return 0;
}