// KNU CSE 2021114026 Jeongwoo Kim
// 1715
#include <iostream>
#include <queue>

using namespace std;

struct myCompare {
    bool operator()(int x, int y) {
        return x > y;
    }
};

priority_queue<int, vector<int>, myCompare> pq;

void solve() {
    int x = 0;
    int ret = 0;

    while (pq.size() != 1) {
        x = pq.top(); pq.pop();
        x += pq.top(); pq.pop();
        ret += x;
        pq.push(x);
    }

    cout << ret;

    return;
}

int main(void) {
    int n;
    int temp;

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> temp;
        pq.push(temp);
    }

    if (n == 1) {
        cout << "0";
        return 0;
    }
    solve();

    return 0;
}