// KNU CSE 2021114026 Jeongwoo Kim
// AX09_P01:
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>

using namespace std;

class Schedule {
    private:
        /* job_number, deadline, profit */
        queue<tuple<int, int, int>> job;
        /* job_number, deadline */
        vector<pair<int, int>> stk;
        /* priority queue */
        struct myCompare {
            bool operator() (tuple<int, int, int> a, tuple<int, int, int> b) {
                return get<1>(a) > get<1>(b);
            }
        };              /* job_number, deadline, profit */
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, myCompare> selected;

        int top;
        int maxdl;
        int maxProf;

    public:
        Schedule() {
            top = 1;
            stk.push_back(make_pair(0, 0));
            maxdl = 0;
            maxProf = 0;
        }
        
        int push_data(int num, int dl, int pro) {
            job.push(make_tuple(num, dl, pro));
            //cout << "pushed" << endl;
            if (maxdl < dl) maxdl = dl; /*  */
        }

        void getOptimal(void) {
            tuple<int, int, int> temp;
            /*
                * why this does not work
                    - less deadline can be found later! => re-sorted
            */
            while (top <= maxdl) {
                //cout << "iter" << endl;
                temp = job.front(); job.pop();
                if (get<1>(temp) >= top && get<1>(temp) <= maxdl) {
                    //stk.push_back(make_pair(get<0>(temp), get<1>(temp)));
                    selected.push(make_tuple(get<0>(temp), get<1>(temp), get<2>(temp)));
                    top++;
                    maxProf += get<2>(temp);
                    cout << "top added" << endl;
                }
            }
        }
        void printOptimalSet(void) {
            cout << "opt. set: \n";
            for (int i = 1; i < stk.size(); i++) {
                cout << stk[i].first << " ";
            }
            cout << "\n";
        }
        void printOptimalSeq(void) {
            int sum = 0;
            cout << "opt. seq: \n";
            /*  let var a = 1;
                for i (1 -> stk.size())
                    for j (1 -> stk.size())
                        if deadline of stk is same or higher than stk[i]
                            then add, pop
            */
            while (!selected.empty()) {
                cout << get<2>(selected.top()) << " ";
                sum += get<2>(selected.top());
                selected.pop();
            }
            cout << sum << endl;
        }
};

int main(void) {
    int cnt; int in;
    queue<int> dl;
    queue<int> pro;
    Schedule a;

    cin >> cnt;
    for (int i = 1; i <= cnt; i++) {
        cin >> in;
        dl.push(in);
    }
    for (int i = 1; i <= cnt; i++) {
        cin >> in;
        pro.push(in);
    }
    for (int i = 1; i <= cnt; i++) {
        a.push_data(i, dl.front(), pro.front());
        dl.pop(); pro.pop();
    }

    a.getOptimal();

    //a.printOptimalSet();

    a.printOptimalSeq();

    return 0;
}