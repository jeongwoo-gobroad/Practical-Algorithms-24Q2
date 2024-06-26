// KNU CSE 2021114026 Jeongwoo Kim
// AX09_P01: An deadline scheduling problem
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>

#define JOB       get<0> 
#define DEADLINE  get<1>
#define PROFIT    get<2> 

using namespace std;

/*< job no, deadline, profit > */
typedef tuple<int, int, int> task;

class Schedule {
    private:
        /* optimization */
        int maxDeadLine;
        /* just for heap */
        queue<task> jobs;
        /* for local set of greedy approach */
        vector<task> optSol; /* index for time allocation */
        int optVal;
    public:
        Schedule() {
            maxDeadLine = 0;
            optVal = 0;
        }

        void pushData(int idx, int dl, int pro) {
            jobs.push(make_tuple(idx, dl, pro));
            if (dl > maxDeadLine) {
                maxDeadLine = dl;
            }
        }

        bool isFeasible(const vector<task>& j) {
            for (int i = 1; i < j.size(); i++) {
                if (DEADLINE(j[i]) < i) {
                    return false;
                }
            }

            return true;
        }

        void myInsert(vector<task>& v, int idx, task target) {
            v.resize(v.size() + 1);
            for (int i = idx; i < v.size() - 1; i++) {
                v[i + 1] = v[i];
            }
            v[idx] = target;
        }

        void algorithm() {                         /*< job no, deadline, profit > */
            vector<task> temp;                     /*typedef tuple<int, int, int> task;*/
            task insertTarget;
            int idx = 1;

            optSol.push_back(make_tuple(0, 0, 0)); /* to match index and time allocation */
            optSol.push_back(jobs.front()); jobs.pop();
            optVal += PROFIT(optSol.back());
            while (optSol.size() - 1 != maxDeadLine) {
                temp = optSol; /* copy */
                insertTarget = jobs.front(); jobs.pop();
                for (idx = 1; idx < temp.size(); idx++) {
                    if (DEADLINE(insertTarget) < DEADLINE(temp[idx])) {
                        break;
                    }
                }
                myInsert(temp, idx, insertTarget);
                if (isFeasible(temp)) {
                    optVal += PROFIT(insertTarget);
                    optSol = temp;
                }
                temp.clear();
            }
        }

        void printResult() {
            cout << optVal << "\n";
            for (int i = 1; i < optSol.size(); i++) {
                cout << PROFIT(optSol[i]);
                if (i != optSol.size() - 1) {
                    cout << " ";
                }
            }
        }
};

int main(void) {
    int cnt, temp;
    queue<int> a, b;
    Schedule t;

    cin >> cnt;

    for (int i = 1; i <= cnt; i++) {
        cin >> temp;
        a.push(temp);
    }
    for (int i = 1; i <= cnt; i++) {
        cin >> temp;
        b.push(temp);
    }
    for (int i = 1; i <= cnt; i++) {
        t.pushData(i, a.front(), b.front());
        a.pop(); b.pop();
    }

    t.algorithm();
    t.printResult();

    return 0;
}