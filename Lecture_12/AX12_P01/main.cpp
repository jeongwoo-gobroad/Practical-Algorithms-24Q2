// KNU CSE 2021114026 Jeongwoo Kim
// AX12, P01: BnB w/Best FS Zero-One Knapsack
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

typedef struct ssNode {
    int profit; int weight; int level;
    int bound; /* to fit into the data structure */
} ssNode;

bool initCompare(ssNode* s, ssNode* o) {
    return (s->profit / s->weight) > (o->profit / o->weight);
}

struct boundCompare {
    bool operator()(ssNode* s, ssNode* o) {
        return s->bound < o->bound;
    }
};

priority_queue<ssNode*, vector<ssNode*>, boundCompare> bestFS;
vector<ssNode*> items;
int n, w;
int opVal = 0;

int getChildBound(ssNode* o) {
    int retVal = 0;
    int zeroOneW = 0;
    int i;

    if (o->weight >= w) { /* is the node promising? */
        retVal = 0;
    }
    else {
        retVal += o->profit;
        zeroOneW += o->weight;
        for (i = o->level + 1; i <= n && zeroOneW + items[i]->weight <= w; i++) {
            retVal += items[i]->profit;
            zeroOneW += items[i]->weight;
        }
        /* being fractional */
        if (i <= n) {
            retVal += ((w - zeroOneW) * (items[i]->profit / items[i]->weight));
        }
    }

    o->bound = retVal;

    cout << o->level << " " << o->weight << " " << o->profit << " " << o->bound << "\n";

    return retVal;
}

ssNode* setNodeVal(int profit, int weight, int level) {
    ssNode* temp = new ssNode;

    temp->profit = profit;
    temp->weight = weight;
    temp->level = level;

    return temp;
}

void solve(void) {
    /* simulates BFS with SINGLE Queue */
    /* And, we apply PQ to achieve Best FS */
    /* So, identifing those nodes with a member called 'level' is needed. */
    ssNode* root = new ssNode;
    ssNode* temp; ssNode* curr;
    int curBound;

    root = setNodeVal(0, 0, 0);
    getChildBound(root);

    bestFS.push(root);
    while (!bestFS.empty()) {
        curr = bestFS.top(); bestFS.pop();
        cout << "popped: " << curr->weight << " " << curr->profit << " " << curr->bound << endl;
        int nextLevel = curr->level + 1;
        //cout << "Visited: " << curr->level << endl;
        //cout << "Next-Level: " << nextLevel << endl;
        //cout << curr->level << " " << curr->weight << " " << curr->profit << " " << curr->bound << "\n";
        
        if (curr->profit > opVal && curr->weight <= w) {
            /* refresh */
            opVal = curr->profit;
        }
        else if (curr->bound < opVal || nextLevel > n) {
            /* somewhat previous queue operation has found better opt.val */
            /* or trying to exceed given index */
            continue;
        }
        
        /* include element of the next level here and evaluate! */
        /* Why need to do insertion and evaluation both at the same time? */
        /* The Reason is simple: PQ needs a bound value in which an element is inserted. */
        /* Do include nth level element */
        temp = setNodeVal(curr->profit + items[nextLevel]->profit, curr->weight + items[nextLevel]->weight, nextLevel);
        //cout << temp->level << " " << temp->weight << " " << temp->profit << " " << temp->bound << "\n";
        /* only to proceed if higher possibility value has been found */
        if (temp->profit > opVal && temp->weight <= w) { /* bound can be zero if fully packed */
            /* refresh */
            opVal = temp->profit;
        }
        if (opVal < getChildBound(temp)) {
            //cout << temp->level << " " << temp->weight << " " << temp->profit << " " << temp->bound << "\n";
            bestFS.push(temp);
        }
        /* Do not include */
        temp = setNodeVal(curr->profit, curr->weight, nextLevel);
        //cout << temp->level << " " << temp->weight << " " << temp->profit << " " << temp->bound << "\n";
        /* only to proceed if higher possibility value has been found */
        if (temp->profit > opVal && temp->weight <= w) { /* bound can be zero if fully packed */
            /* refresh */
            opVal = temp->profit;
        }
        if (opVal < getChildBound(temp)) {
            //cout << temp->level << " " << temp->weight << " " << temp->profit << " " << temp->bound << "\n";
            bestFS.push(temp);
        }
    }

    return;
}

int main(void) {
    int temp; ssNode* tmNode;
    vector<int> profs;
    vector<int> weights;

    cin >> n;
    cin >> w;

    for (int i = 0; i < n; i++) {
        cin >> temp;
        weights.push_back(temp);
    }
    for (int i = 0; i < n; i++) {
        cin >> temp;
        profs.push_back(temp);
    }
    
    items.push_back(new ssNode);
    for (int i = 0; i < n; i++) {
        tmNode = new ssNode;
        tmNode->profit = profs[i];
        tmNode->weight = weights[i];
        items.push_back(tmNode);
    }
    sort(items.begin() + 1, items.end(), initCompare);

    solve();
    cout << opVal;

    return 0;
}