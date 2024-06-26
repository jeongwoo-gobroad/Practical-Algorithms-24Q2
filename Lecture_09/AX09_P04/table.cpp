// KNU CSE 2021114026 Jeongwoo Kim
// AX09_P04: Representing Prime factors w/ Roman Digits
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <stack>
#include <string>

using namespace std;

/* index == number
    index == number if prime
    index =/= number, index == smallest prime if not prime

    pseudo_code:
        let table a in range (2, n)
        let primeIdx = 2
        if indexes of table divisible to primeIdx O(n)
            then mark 2;
        scan next primeIdx O(n)
*/

int main(void) {
    int input;
    vector<int> primes;
    int tmp;

    cin >> input;

    primes.resize(input + 1, 1);

    for (int i = 2; i <= input; i++) {
        for (int j = i; j * i <= input; j++) {
            cout << "Filling: " << j * i << endl;
            primes[j * i] = i;
        }
        for (int j = i + 1; j <= input; j++) {
            if (primes[j] == 1) {
                cout << "New Prime: " << j << endl;
                i = j;
                tmp = j;
                break;
            }
        }
        if (tmp == i)
    }

    cin >> input;

    int temp;
    while (temp == 1) {
        temp /= primes[temp];
        cout << temp;
    }

    return 0;
}