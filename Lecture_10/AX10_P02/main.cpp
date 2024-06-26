// KNU CSE 2021114026 Jeongwoo Kim
// AX10_P02: Sum-of-subsets
#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

int cnt = 0;
vector<vector<int>> ans;

bool isOptimal(int nthres, const int& target, int sum) {
    if (nthres > target) return false;
    if (nthres < target && sum < target - nthres) return false;

    return true;
}

void solve(const vector<int>& num, vector<int>& choose, int nthres, const int& target, int sum, int idx) {
    if (isOptimal(nthres, target, sum)) {
        if (nthres == target) {
            vector<int> temp;
            cnt++;
            for (int i = 1; i < choose.size(); i++) {
                if (choose[i]) {
                    temp.push_back(num[i]);
                }
            }
            ans.push_back(temp);
            
            return;
        }
        //printf("idx: %d, num: %d\n", idx, num[idx]);
        choose[idx + 1] = 1; /* we have to make it static, not dynamic! why? */
        solve(num, choose, nthres + num[idx + 1], target, sum - num[idx + 1], idx + 1);
        choose[idx + 1] = 0; /* we have to make it static, not dynamic! why? */
        /* when we access via index number, we often use obj.size(), but this is DANGEROUS */
        /* once doubled size doesn't get shrinked, so this will lead us to invaild memory access */
        solve(num, choose, nthres, target, sum - num[idx + 1], idx + 1);
    }

    return;
}

int main(void) {
    int n; int target; int sum = 0;
    vector<int> numarr;
    vector<int> isChosen; /* Partial State Space: (number index, is_chosen) */

    numarr.push_back(0);
    isChosen.push_back(0);

    cin >> n;
    cin >> target;

    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        numarr.push_back(temp);
        sum += temp;
    } /* let the numbers be sorted already. */
    isChosen.resize(n + 1, 0); /* we have to make it static, not dynamic! why? */
    /* when we access via index number, we often use obj.size(), but this is DANGEROUS */
    /* once doubled size doesn't get shrinked, so this will lead us to invaild memory access */

    solve(numarr, isChosen, 0, target, sum, 0);

    cout << cnt;

    for (int i = 0; i < ans.size(); i++) {
        cout << "\n";
        for (int j = 0; j < ans[i].size() - 1; j++) {
            cout << ans[i][j] << " ";
        }
        cout << ans[i][ans[i].size() - 1];
    }
    
    return 0;
}