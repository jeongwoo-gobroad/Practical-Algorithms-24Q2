// KNU CSE 2021114026 Jeongwoo Kim
// AX09_P05: A present sent by Josephus
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

typedef unsigned long long ull;
typedef long double ld;

void solve(int n) {
    /* simulates Circular Linked List, but how? */
    ull cur = 1;
    int term = 2;
    vector<int> arr(n + 1, 1);

    for (int i = 1; i <= n; i++) {
        arr[i] = i; /* yeah... this seems ok. but why? Doesn't index itself mean data? */
        /* here's why:  if you delete an element in your vector, index will be shrinked.*/
        /* so, index has no meanings, only data does. */
    }

    while (arr.size() != 2) {
        //cur %= (ull)(arr.size() - 1);

        //cout << arr[cur] << " "; /* data has the meaning */
        arr.erase(arr.begin() + cur); /* added number in the iterator means index of an element. */
        /* so arr.begin() + 1 == arr[1] */
        if (arr.size() != 2) { /* exit condition */
        }
        else {
            break;
        }

        cur += (ull)(term) * (ull)(term) * (ull)(term) - (ull)1; /* wtf: (k) means (k)'th' student, so movement(action) is (k - 1). */
        cur %= (ull)(arr.size() - 1); /* to get exact information of original circular size */
        //cur -= (ull)1;
        term++;
        if (cur == 0) {
            /* to be more specific: arr[0] is not for use. */
            cur = (ull)arr.size() - (ull)1; /* points out the end of the vector */
        }
    }

    cout << arr[1];

    return;
}

int main(void) {
    int input, k;

    cin >> input;

    solve(input);

    return 0;
}