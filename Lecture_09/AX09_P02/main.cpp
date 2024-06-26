// KNU CSE 2021114026 Jeongwoo Kim
// AX09_P02: Huffman code and its algorithm
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <map>

using namespace std;

typedef struct node {
    char data;
    int freq;
    struct node* left;
    struct node* right;
} node;
typedef struct node* nodePtr;

struct myCompare {
    bool operator() (nodePtr s, nodePtr t) {
        /* non-increasing */
        /* min heap: sending LARGER value to the child node */
        return s->freq > t->freq;
    }
};
typedef priority_queue<nodePtr, vector<nodePtr>, myCompare> nodeQ;

nodePtr huffman(nodeQ target) {
    nodePtr inter;
    nodePtr zero, one;
    int nNum = target.size(); /* we should copy this: */

    /* why node_num - 1?: because it's spanning tree! */
    for (int i = 1; i < nNum; i++) {
        /* Limited Access Vector from each other; attributes of catalan number in diagonal checker board
        */
        zero = target.top(); target.pop();
        one = target.top(); target.pop();

        inter = new node;

        inter->left = zero; 
        inter->right = one;
        inter->data = '+';
        inter->freq = zero->freq + one->freq;

        target.push(inter);

        //cout << target.top()->data << endl;
    }
    
    /* since the very last joint node is the root */
    return inter;
}

void preorder(nodePtr t) {
    if (!t) return;

    cout << t->data << ":" << t->freq << " ";
    preorder(t->left);
    preorder(t->right);

    return;
}

void inorder(nodePtr t) {
    if (!t) return;

    inorder(t->left);
    cout << t->data << ":" << t->freq << " ";
    inorder(t->right);

    return;
}

void createDict(nodePtr t, string s, map<char, string>& d, char c) {
    if (!t) {
        s.pop_back(); /* since branching out from the leaf node has no meanings */
        d.insert(make_pair(c, s));
        return;
    }
    string l = s; string r = s;
    l.push_back('0'); r.push_back('1');

    createDict(t->left, l, d, t->data);
    createDict(t->right, r, d, t->data);

    return;
}

void decode(const nodePtr root, nodePtr t, const string& s, int idx, char x) {
    if (t->left == NULL && t->right == NULL) {
        cout << t->data;
        //cout << " Go back to the root" << endl;
        decode(root, root, s, idx, '\0');
        return; /* important! there are two ways to end this loop */
    }
    
    if (idx >= s.size()) {
            return; /* exit condition */
    }

    //cout << idx << endl;
    //cout << "Depth: " << t->data << endl;
    //cout << s << endl;

    /* printing part */
    if (s[idx++] == '0') {
        //cout << "Left" << endl;
        decode(root, t->left, s, idx, t->data);
    }
    else {
        //cout << "Right" << endl;
        decode(root, t->right, s, idx, t->data);
    }

    return;
}

int main(void) {
    nodeQ pq; nodePtr nd; nodePtr root;
    queue<char> letter; queue<int> freq;
    int input; string input_str;
    char iletter; int ifreq;
    map<char, string> dict;
    /* for additional input */
    int in_in, de_in;
    queue<string> inc, dec;

    /* main input */
    cin >> input;
    for (int i = 0; i < input; i++) {
        cin >> iletter;
        letter.push(iletter);
    }
    for (int i = 0; i < input; i++) {
        cin >> ifreq;
        freq.push(ifreq);
    }

    /* aux input */
    cin >> in_in;
    for (int i = 0; i < in_in; i++) {
        cin >> input_str;
        inc.push(input_str);
    }
    cin >> de_in;
    for (int i = 0; i < de_in; i++) {
        cin >> input_str;
        dec.push(input_str);
    }

    for (int i = 0; i < input; i++) {
        nd = new node;
        nd->data = letter.front();
        nd->freq = freq.front();
        nd->left = nd->right = NULL;
        pq.push(nd);
        letter.pop(); freq.pop();
    }

    root = huffman(pq);

    preorder(root);
    cout << "\n";
    inorder(root);
    cout << "\n";
    string tmp;
    createDict(root, tmp, dict, '\0');

    map<char, string>::iterator it = dict.begin();

    //cout << "\n";
    //for (; it != dict.end(); it++) {
    //    cout << (*it).first << "->" << (*it).second << endl;
    //}

    /* printing encoded */
    for (int i = 0; i < in_in; i++) {
        for (int j = 0; j < inc.front().size(); j++) {
            cout << dict[inc.front()[j]];
        }
        cout << "\n";
        inc.pop();
    }

    /* printing decoded */
    for (int i = 0; i < de_in; i++) {
        input_str = dec.front();
        decode(root, root, input_str, 0, '\0');
        if (i != de_in - 1) {
            cout << "\n";
        }
        dec.pop();
    }


    return 0;
}