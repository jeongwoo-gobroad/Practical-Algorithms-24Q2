// KNU CSE 2021114026 Jeongwoo Kim
#include <iostream>
#include <vector>

using namespace std;

typedef struct node {
    struct node* prev;
    int num;
    struct node* next;
} node;
typedef struct node* nodePtr;

nodePtr head = NULL;

void initNode(int n) {
    nodePtr temp = NULL;
    nodePtr prev = NULL;

    head = new node;
    head->num = 1;
    prev = head;

    for (int i = 2; i <= n; i++) {
        temp = new node;
        temp->num = i;
        temp->prev = prev;
        prev->next = temp;
        //cout << "created: " << temp->num;
        prev = temp;
    }
    prev->next = head;
    head->prev = prev;

    return;
}

void solve(int n, int k) {
    nodePtr temp; nodePtr ft;

    initNode(n); temp = head;
    cout << "<";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < k; j++)  {
            temp = temp->next;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        ft = temp;
        temp = temp->next;
        cout << ft->num;
        if (i != n) {
            cout << ", ";
        }
        free(ft);
    }
    cout << ">\n";
}

int main(void) {
    int n, k;

    cin >> n >> k;

    solve(n, k);

    return 0;
}