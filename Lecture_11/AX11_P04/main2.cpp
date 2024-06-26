// KNU CSE 2021114026 Jeongwoo Kim
// AX11, P04: Hamiltonian Circuit / Path with Sparce Matrix Algorithm
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

/* Data structure Itself is a best promising function if the given graph is sparce. */
typedef struct vertexTo {
    int index;
    struct vertexTo* next;
} vertexTo;

typedef struct vertexFrom {
    bool isVisited;
    struct vertexTo* list;
    struct vertexTo* recent;
} vertexFrom;

int n, m;
int cell;
int circuitCnt = 0, pathCnt = 0;
const int mvmt[8][2] = {{2,  1},  {1,  2},{-2,  1}, {-1,  2}, 
                       {-2, -1}, {-1, -2}, {2, -1},  {1, -2}};
vector<vector<int>> indexSample;
vector<vertexFrom> node;

void resizeNode(void);
void appendNode(int from, int rowFrom, int colFrom, int rowDelta, int colDelta);
void createNode(void);
void appendNode(int from, int rowFrom, int colFrom, int rowDelta, int colDelta);
int coorToIndex(int r, int c);

void hmtCircuit(vector<vertexFrom> spcmtx, int cnt, int to) {
    /* let starting point as (0, 0) */
    vertexTo* temp;

    if (to == 0 && cnt == cell) {
        circuitCnt++;
        return;
    }

    temp = spcmtx[to].list;
    while (temp) {
        /* if not visited */
        if (!spcmtx[temp->index].isVisited) {
            /* do you attempt to move to the starting point? */
            if (temp->index == 0) {
                /* It should be done at the last procedure! */
                if (cnt + 1 == cell) {
                    spcmtx[temp->index].isVisited = 1;
                    hmtCircuit(spcmtx, cnt + 1, temp->index);
                    spcmtx[temp->index].isVisited = 0;
                }
            }
            else {
                spcmtx[temp->index].isVisited = 1;
                hmtCircuit(spcmtx, cnt + 1, temp->index);
                spcmtx[temp->index].isVisited = 0;
            }
        }
        temp = temp->next;
    }

    return;
}

void hmtPath(vector<vertexFrom> spcmtx, int cnt, int to, const int& src) {
    vertexTo* temp;

    if (cnt == cell - 1) {
        pathCnt++;
        return;
    }

    temp = spcmtx[to].list;
    while (temp) {
        /* If you attempt to move, it shouldn't be the starting point! */
        if (temp->index != src && !spcmtx[temp->index].isVisited) {
            spcmtx[temp->index].isVisited = 1;
            hmtPath(spcmtx, cnt + 1, temp->index, src);
            spcmtx[temp->index].isVisited = 0;
        }
        temp = temp->next;
    }

    return;
}

int main(void) {
    vector<pair<int, int>> coor;
    int cnt; int r, c;

    cin >> n;
    cin >> m;

    cin >> cnt;

    for (int i = 0; i < cnt; i++) {
        cin >> r;
        cin >> c;
        coor.push_back(make_pair(r, c));
    }

    cell = n * m;
    resizeNode();
    createNode();

    /*
    for (int i = 0; i < n * m; i++) {
        vertexTo* temp = node[i].list;

        cout << "from " << i << " ";
        while (temp) {
            cout << temp->index << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    */
    hmtCircuit(node, 0, 0);

    cout << circuitCnt;

    for (int i = 0; i < cnt; i++) {
        cout << "\n";
        int temp = coorToIndex(coor[i].first, coor[i].second);
        hmtPath(node, 0, temp, temp);
        cout << pathCnt;
        pathCnt = 0;
    }

    return 0;
}

void resizeNode(void) {
    node.resize(n * m);
    indexSample.resize(n, vector<int>(m, 0));

    for (int i = 0; i < n * m; i++) {
        node[i].isVisited = false;
        node[i].list = NULL;
        node[i].recent = NULL;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            indexSample[i][j] = i * m + j;
        }
    }
}
void appendNode(int from, int rowFrom, int colFrom, int rowDelta, int colDelta);
void createNode(void) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 8; k++) {
                appendNode(indexSample[i][j], i, j, mvmt[k][0], mvmt[k][1]);
            }
        }
    }
}

void appendNode(int from, int rowFrom, int colFrom, int rowDelta, int colDelta) {
    if (rowFrom + rowDelta < 0 || rowFrom + rowDelta >= n || colFrom + colDelta < 0 || colFrom + colDelta >= m) {
        return;
    }

    if (node[from].recent == NULL) {
        vertexTo* temp = new vertexTo;
        temp->index = indexSample[rowFrom + rowDelta][colFrom + colDelta];
        temp->next = NULL;
        node[from].recent = temp;
        node[from].list = temp;
    }
    else {
        vertexTo* temp = new vertexTo;
        temp->index = indexSample[rowFrom + rowDelta][colFrom + colDelta];
        temp->next = NULL;
        node[from].recent->next = temp;
        node[from].recent = temp;
    }

    return;
}

int coorToIndex(int r, int c) {
    return indexSample[r][c];
}