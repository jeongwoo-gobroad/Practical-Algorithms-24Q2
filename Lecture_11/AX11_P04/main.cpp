// KNU CSE 2021114026 Jeongwoo Kim
// AX11, P04: Hamiltonian Circuit / Path
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

typedef vector<vector<int>> mat;

int n, m;
int cell;
const int mvmt[8][2] = {{2,  1},  {1,  2},{-2,  1}, {-1,  2}, 
                       {-2, -1}, {-1, -2}, {2, -1},  {1, -2}};

int cirCnt = 0;
int pathCnt = 0;

bool isPromising_circuit(const int& tR, const int& tC, const int& cnt, const int& curRow, const int& curCol, const mat& t) {
    int v = 0;
    int avail = 0;

    if (curRow == tR && curCol == tC && cnt + 1 != cell) {
        return false;
    }
    if (curRow < 0 || curRow >= n) {
        return false;
    }
    if (curCol < 0 || curCol >= m) {
        return false;
    }
    if (t[curRow][curCol]) { /* if visited */
        return false;
    }
    
    for (int i = 0; i < 8; i++) {
        int tempRow = curRow + mvmt[i][0];
        int tempCol = curCol + mvmt[i][1];
        if (tempRow < 0 || tempRow >= n || tempCol < 0 || tempCol >= m) {
            avail++;
        }
        else {
            if (t[tempRow][tempCol] == 1) {
                avail++;
            }
        } 
    }
    if (avail == 8) {
        //cout << "cannot go further" << endl;
        return false;
    }
    
    return true;
}

bool isPromising_path(const int& tR, const int& tC, const int& cnt, const int& curRow, const int& curCol, const mat& t) {
    int v = 0;

    /*
    if (curRow == tR && curCol == tC && cnt + 1 == cell) {
        return false;
    }
    */
    if (curRow < 0 || curRow >= n) {
        return false;
    }
    if (curCol < 0 || curCol >= m) {
        return false;
    }
    if (t[curRow][curCol]) { /* if visited */
        return false;
    }

    return true;
}

void hmtCircuit(const int& tR, const int& tC, int cnt, mat b, int row, int col) {
    if (cnt == cell && row == tR && col == tC) {
        cirCnt++;
        return;
    }

    for (int i = 0; i < 8; i++) {
        if (isPromising_circuit(tR, tC, cnt, row + mvmt[i][0], col + mvmt[i][1], b)) {
            //cout << "Going to " << row + mvmt[i][0] << ", " << col + mvmt[i][1] << endl;
            b[row + mvmt[i][0]][col + mvmt[i][1]] = 1;
            hmtCircuit(tR, tC, cnt + 1, b, row + mvmt[i][0], col + mvmt[i][1]);
            b[row + mvmt[i][0]][col + mvmt[i][1]] = 0;
        }
    }
    
    return;
}
void hmtPath(const int& tR, const int& tC, int cnt, mat b, int row, int col) {
    if (cnt == cell - 1) {
        pathCnt++;
        return;
    }

    for (int i = 0; i < 8; i++) {
        if (isPromising_path(tR, tC, cnt, row + mvmt[i][0], col + mvmt[i][1], b)) {
            b[row + mvmt[i][0]][col + mvmt[i][1]] = 1;
            hmtPath(tR, tC, cnt + 1, b, row + mvmt[i][0], col + mvmt[i][1]);
            b[row + mvmt[i][0]][col + mvmt[i][1]] = 0;
        }
    }
    
    return;
}

int main(void) {
    mat board;
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
    board.resize(n, vector<int>(m, 0));

    hmtCircuit(0, 0, 0, board, 0, 0);
    cout << cirCnt;

    for (int i = 0; i < cnt; i++) {
        board.resize(n, vector<int>(m, 0));
        board[coor[i].first][coor[i].second] = 1;
        hmtPath(coor[i].first, coor[i].second, 0, board, coor[i].first, coor[i].second);
        cout << "\n" << pathCnt;
        board.clear();
        pathCnt = 0;
    }

    return 0;
}