// KNU CSE 2021114026 Jeongwoo Kim
// AX11, P01: Fractional Knapsack with Greedy approach
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <tuple>

#define weight get<0>
#define value  get<1>
#define vpw    get<2>

using namespace std;

/*         weight value value_per_weight*/
typedef tuple<int, int, int> knapsack;

struct myCompare {
    bool operator()(knapsack s, knapsack o) {
        return vpw(s) < vpw(o); /* max heap */
    }
};

priority_queue<knapsack, vector<knapsack>, myCompare> pq;
priority_queue<knapsack, vector<knapsack>, myCompare> temp;

void solve(const int& maxWeight) {
    queue<knapsack> myKnapsack;
    int           myWeight = 0;
    int           myProfit = 0;
    int           fractionedWeight = 0;
    knapsack        grab;

    /* Fractional Knapsack Problem: Greedy approach */
    temp = pq;
    while (myWeight < maxWeight && !temp.empty()) {
        /* important: condition should not be <= */
        /* else then if-statement below will add <0, 0, 0> to the queue! */
        grab = temp.top();
        
        /* If Last Record is being fractional data */
        if (myWeight + weight(grab) > maxWeight) {
            fractionedWeight = maxWeight - myWeight;
            
            myProfit += vpw(grab) * fractionedWeight;

            myKnapsack.push(make_tuple(fractionedWeight, vpw(grab) * fractionedWeight, 0));
            break;
        }

        myWeight += weight(grab);
        myProfit += value(grab);
        myKnapsack.push(grab);

        temp.pop();
    }

    cout << myProfit << "\n";
    while (!myKnapsack.empty()) {
        cout << weight(myKnapsack.front()) << " " << value(myKnapsack.front());
        myKnapsack.pop();

        if (!myKnapsack.empty()) {
            cout << "\n";
        }
    }

    return;
}

int main(void) {
    int n; int input;
    vector<int> w;
    vector<int> p;
    vector<int> knapsackW;
    int k;

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> input;
        w.push_back(input);
    }
    for (int i = 0; i < n; i++) {
        cin >> input;
        p.push_back(input);
    }
    for (int i = 0; i < n; i++) {
        pq.push(make_tuple(w.back(), p.back(), p.back() / w.back()));
        w.pop_back(); p.pop_back();
    }

    cin >> k;
    for (int i = 0; i < k; i++) {
        cin >> input;
        knapsackW.push_back(input);
    }

    for (int i = 0; i < k; i++) {
        solve(knapsackW[i]);
        if (i != k - 1) {
            cout << "\n";
        }
    }

    return 0;
}