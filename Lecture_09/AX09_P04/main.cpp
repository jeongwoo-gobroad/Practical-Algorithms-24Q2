// KNU CSE 2021114026 Jeongwoo Kim
// AX09_P04: Representing Prime factors w/ Roman Digits
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <chrono>
#include <string>

using namespace std;

    /**important:
     *      When smaller units appear before larger units in Roman numerals,
     *      subtract the smaller unit from the larger unit.
     */
                             /* 0    1     2    3     4    5     6    7     8    9     10   11    12   */
const vector<string> romans = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};
                      /* 0  1  2  3  4   5   6   7   8    9    10   11   12   */
const vector<int> num = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};

vector<int> primes; /* 1 is stored if prime, minimum prime number is stored if it can be divided to. */
vector<int> found_primes; /* only for primes to reduce time complexity */

string
returnRomans(int target) {
    int numCnter = 12;
    string rtn = "";

    while (target) {
        if (target - num[numCnter] < 0) { /* Greedy approach */
            numCnter--;
        }
        else {
            target -= num[numCnter];
            rtn = rtn + romans[numCnter]; /* concatenate */
        }
    }

    return rtn;
}

int
returnInt(string r) {
    int romansIdx = 12;
    int sizeOfRomansIdx = 0;
    int rtn = 0;
    int found = 1;

    for (int i = 0; i < r.size();) {
        /* comparing current MSSS(Most Significant SubString) to the Greedy Table */
        sizeOfRomansIdx = romans[romansIdx].size();
        for (int j = 0; j < sizeOfRomansIdx; j++) { /* max loop: 2(IX-like words) */
            /* magic works here */
            if (r[i + j] != romans[romansIdx][j]) {
                found = 0;
                romansIdx--;
                break;
            }
        }
        if (found) {
            i += sizeOfRomansIdx;
            //cout << "found: " << num[romansIdx] << endl;
            rtn += num[romansIdx];
        }
        else {
            sizeOfRomansIdx = 0;
        }
        found = 1;
    }

    return rtn;
}

void
storePrime_new(int limit) {
    for (int indexCounter = 2; indexCounter <= sqrt(limit); indexCounter++) {
            /** Why we can just define that a number is a prime until it can't be divided by some
             *  prime numbers same or less than sqrt(input)?
             *      let input = X
             *      if input can ba divisible into M, N
             *      X = M * N (N <= M)
             *      then M * N <= M * M
             *          sqrt(X) <= M, minimum of M is sqrt(x)
             *          N <= M <= sqrt(x), maximum of N is sqrt(x)
            */
        if (primes[indexCounter] == 1) {
            for (int i = indexCounter; i * indexCounter <= limit; i++) {
                //cout << "Checking... " << indexCounter * i << endl;
                if (primes[indexCounter * i] == 1) {
                    primes[indexCounter * i] = indexCounter;
                }
            }
        }  
    }

    return;
}

void
storePrime(int limit) {
    int found = 1;

    found_primes.push_back(2);
    found_primes.push_back(3);
    for (int indexCounter = 4; indexCounter <= limit; indexCounter++) {
        for (int target = 0; target < found_primes.size(); target++) {
            if (sqrt(indexCounter) < found_primes[target]) {
                /** Why we can just define that a number is a prime until it can't be divided by some
                 *  prime numbers same or less than sqrt(input)?
                 *      let input = X
                 *      if input can ba divisible into M, N
                 *      X = M * N (N <= M)
                 *      then M * N <= M * M
                 *          sqrt(X) <= M, minimum of M is sqrt(x)
                 *          N <= M <= sqrt(x), maximum of N is sqrt(x)
                */
                found_primes.push_back(indexCounter);
                break;
            }

            if (indexCounter % found_primes[target] == 0) { /* to find primes */
                primes[indexCounter] = found_primes[target];
                break;
            }


        }
    }

    //for (auto i: found_primes)
    //    cout << i << " ";
    //cout << endl;

    return;
}

vector<int>
getPrimeFactors(int target) {
    vector<int> rtn;
    /* kinda greedy */
    while (1) {
        if (primes[target] == 1) {
            rtn.push_back(target);
            break;
        }
        else {
            rtn.push_back(primes[target]);
        }
        target /= primes[target];
    }

    return rtn;
}

int main(void) {
    string input; int num; queue<string> result;
    vector<int> factorized;

    cin >> input;

    /* Romans to Int */
    num = returnInt(input);

    /* Get Prime Factors */
    primes.resize(num + 1, 1);

    //storePrime(num);
    
    storePrime_new(num);
    //for (auto i: primes) cout << i << " ";
    factorized = getPrimeFactors(num);

    /* Int to Romans, then print */
    for (int i = 0; i < factorized.size(); i++) {
        cout << returnRomans(factorized[i]);
        if (i != factorized.size() - 1) {
            cout << "\n";
        }
    }

    /* is this slow?
    for (int i = 0; i < factorized.size(); i++) {
        cout << returnRomans(factorized[i]);
        if (i != factorized.size() - 1) {
            cout << "\n";
        }
    }
    */
    /*  For testing 
    cout << returnRomans(input) << ": " << returnInt(returnRomans(input));
    storePrime(input, primes);

    for (const auto& i: primes) {
        cout << i << " ";
    }

    factorized = getPrimeFactors(input, primes);

    for (const auto& i: factorized) {
        cout << i << " ";
    }
    */

    return 0;
}