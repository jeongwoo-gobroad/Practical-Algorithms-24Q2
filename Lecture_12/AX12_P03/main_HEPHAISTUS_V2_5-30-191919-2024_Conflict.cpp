// KNU CSE 2021114026 Jeongwoo Kim
// AX12, P03: TSP Problem with BestFS search
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

/* Pseudo-code:
        Note: unlike Dynamic Programmed one, we implement n!-like approach here.
        
func TSPwithPQ
    loop til PQ is empty
        for i in range of 2 to n
            if pq.top doesn't have the node i
                pop top as N
                add i to N
                if (n - 2) elements has chosen
                    do remaining operations at once
                    update optimal_minimum at here: DFS-like approach: do not refresh optmin value until reachable one has been found.
                else
                    is N promising? (vertices connected)
                    is N has less lower bound than current optmin?

func getPromising
    check if the vertices in the node are all connected

func getBound
    bound = 0
    bound += current_cumulated_weight
    for all unchosen vertices
        except: not an element that makes the loop
        except: not an element that returns to Vertex 1
        if a vertex has passed the test
            bound += chosenVertex.weight
    
    return bound
*/
#define INF 99999999

typedef vector<vector<int>> mat;
typedef struct node {
    int level;
    vector<int> chosen;
    int cumulatedWeight;
    int bound;
} node;

struct myCompare {
    bool operator()(node* s, node* o) {
        return s->bound > o->bound;
    }
};

/* Best FS */
priority_queue<node*, vector<node*>, myCompare> pq;
mat adj;
int n;

node* insertData(int lvl, int cw, vector<int> cv) {
    node* temp = new node;

    temp->level = lvl;
    temp->cumulatedWeight = cw;
    temp->chosen = cv;

    return temp;
}

bool isPromising(node* v) {
    /* is it looping? */
    for (int i = 0; i <= v->level; i++) {
        for (int j = 0; j <= v->level; j++) {
            if (i == j) {
                continue;
            }
            if (v->chosen[i] == v->chosen[j]) {
                return false;
            }
        }
    }
    /* recently added one is promising? */
    if (adj[v->chosen[v->level - 1]][v->chosen[v->level]] == INF) {
        return false;
    }

    return true;
}

bool alreadyConsidered(node* v, int target) {
    vector<int>::iterator it;
    for (it = v->chosen.begin(); it != v->chosen.end() - 1; it++) {
        if (*it == target) {
            return true;
        }
    }

    return false;
}
bool makesLoop(node* v, int target) {
    vector<int>::iterator it;
    for (it = v->chosen.begin() + 1; it != v->chosen.end(); it++) {
        if (*it == target) {
            return true;
        }
    }

    return false;
}

void printStat(node* v) {
    cout << v->level << " ";
    if (v->bound >= INF) {
        cout << "INF";
    }
    else {
        cout << v->bound;
    }

    for (int i = 0; i <= v->level; i++) {
        cout << " " << v->chosen[i];
    }
    cout << "\n";

    return;
}

int getBound(node* v) {
    /* Exclude
            1. loop to the chosen ones
            2. circuit to the start vertex
    */
    int min = INF;
    v->bound = v->cumulatedWeight;

    for (int i = 1; i <= n; i++) { /* from */
        if (alreadyConsidered(v, i)) continue;

        min = INF;

        for (int j = 1; j <= n; j++) { /* to */
            if (i == j) continue;
            if (j == 1 && v->chosen[v->level] == i) continue;
            if (makesLoop(v, j)) continue;

            if (adj[i][j] < min) {
                //cout << "Checked " << i << " to " << j << "with min of " << min << endl;
                min = adj[i][j];
            }
        }
        v->bound += min;
    }
    
    //printStat(v);

    return v->bound;
}

int getWeight(node* v, int next) {
    return adj[v->chosen.back()][next];
}
int getRecentWeight(node* v) {
    return adj[v->chosen[v->chosen.size() - 2]][v->chosen[v->chosen.size() - 1]];
}

void solve(void) {
    node* root;
    node* curr;
    node* temp;
    int optMin = INF; /* DFS-like approach */
    vector<int> optSol;

    root = insertData(0, 0, {1});
    getBound(root);

    pq.push(root);
    while (!pq.empty()) {
        curr = pq.top(); pq.pop();
        if (curr->level == (n - 2)) /* if a case has been fully defined */ {
            curr->level++;
            for (int i = 2; i <= n; i++) {
                curr->chosen.push_back(i); /* push */
                if (isPromising(curr)) {
                    break;
                }
                curr->chosen.pop_back(); /* pop */
            }
            curr->cumulatedWeight += adj[curr->chosen[curr->level - 1]][curr->chosen[curr->level]];
            curr->chosen.push_back(1);
            if (!isPromising(curr)) continue;
            curr->level++;
            curr->cumulatedWeight += adj[curr->chosen[curr->level - 1]][curr->chosen[curr->level]];
            printStat(curr);
            if (curr->cumulatedWeight < optMin) /* now refresh */{
                optMin = curr->cumulatedWeight;
                optSol = curr->chosen;
            }
        }
        else /* still need to go further */ {
            for (int i = 2; i <= n; i++) /* n!-like approach */ {
                curr->chosen.push_back(i);
                temp = insertData(curr->level + 1, curr->cumulatedWeight + getRecentWeight(curr), curr->chosen);
                if (isPromising(temp)) {
                    getBound(temp);
                    printStat(temp);
                    if (temp->bound < optMin) {
                        pq.push(temp);
                    }
                }
                curr->chosen.pop_back();
            }
        }
    }

    cout << optMin << "\n";
    for (int i = 0; i <= n; i++) {
        cout << optSol[i];
        if (i != n) {
            cout << " ";
        }
    }

    return;
}

int main(void) {
    int cnt;
    int tmpFrom, tmpTo, tmpWei;

    cin >> n;
    cin >> cnt;

    adj.resize(n + 1, vector<int>(n + 1, INF));

    for (int i = 0; i < cnt; i++) {
        cin >> tmpFrom;
        cin >> tmpTo;
        cin >> tmpWei;

        adj[tmpFrom][tmpTo] = tmpWei;
    }

    solve();

    return 0;
}