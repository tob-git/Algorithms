#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void checkMissing(vector<vector<char>>& board,int x, int y, int &r, int &c, int missing_row,int missing_col) {

    if (board[x][y] != 0) {
        r = x;
        c = y;
    }
    else {
        r = missing_row;
        c = missing_col;
    }


}

void tileBoard(vector<vector<char>>& board, int size, int x, int y, string location, int missing_row, int missing_col) {
    if (size == 2) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if (board[x + i][y + j] == 0) {
                    if (location == "UR" || location == "DL") {
                        board[x + i][y + j] = 'R';
                        cout << "tile at row " << x + i << ", column " << y + j << " with color Red" << endl;

                    }
                    else if (location == "DR" || location == "UL") {
                        board[x + i][y + j] = 'B';
                        cout << "tile at row " << x + i << ", column " << y + j << " with color Blue" << endl;

                    }
                }
            }
        }
        return;
    }

    int r = 0, c = 0;
    if (location == "") {
        r = missing_row;
        c = missing_col;
    }
    else if (location == "UR") {

       checkMissing(board, x, y + size - 1, r, c, missing_row, missing_col);
        
    }
    else if (location == "DL") {

        checkMissing(board, x + size - 1, y, r, c, missing_row, missing_col);
    }
    else if (location == "UL") {
        checkMissing(board, x, y, r, c, missing_row, missing_col);
        
    }
    else if (location == "DR") {

        checkMissing(board, x + size - 1, y + size - 1, r, c, missing_row, missing_col);
    }

    if (r < x + size / 2 && c < y + size / 2) {
        board[x + size / 2][y + size / 2 - 1] = 'G';
        board[x + size / 2][y + size / 2] = 'G';
        board[x + size / 2 - 1][y + size / 2] = 'G';
        cout << "tile at row " << x + size / 2 << ", column " << y + size / 2 - 1 << " with color Green" << endl;
        cout << "tile at row " << x + size / 2 << ", column " << y + size / 2 << " with color Green" << endl;
        cout << "tile at row " << x + size / 2 - 1 << ", column " << y + size / 2 << " with color Green" << endl;
    }
    else if (r >= x + size / 2 && c < y + size / 2) {
        board[x + size / 2 - 1][y + size / 2] = 'G';
        board[x + size / 2][y + size / 2] = 'G';
        board[x + size / 2 - 1][y + size / 2 - 1] = 'G';
        cout << "tile at row " << x + size / 2 - 1 << ", column " << y + size / 2 << " with color Green" << endl;
        cout << "tile at row " << x + size / 2 << ", column " << y + size / 2 << " with color Green" << endl;
        cout << "tile at row " << x + size / 2 - 1 << ", column " << y + size / 2 - 1 << " with color Green" << endl;

    }
    else if (r < x + size / 2 && c >= y + size / 2) {
        board[x + size / 2][y + size / 2 - 1] = 'G';
        board[x + size / 2][y + size / 2] = 'G';
        board[x + size / 2 - 1][y + size / 2 - 1] = 'G';
        cout << "tile at row " << x + size / 2 << ", column " << y + size / 2 - 1 << " with color Green" << endl;
        cout << "tile at row " << x + size / 2 << ", column " << y + size / 2 << " with color Green" << endl;
        cout << "tile at row " << x + size / 2 - 1 << ", column " << y + size / 2 - 1 << " with color Green" << endl;

    }
    else if (r >= x + size / 2 && c >= y + size / 2) {
        board[x + size / 2 - 1][y + size / 2] = 'G';
        board[x + size / 2][y + size / 2 - 1] = 'G';
        board[x + size / 2 - 1][y + size / 2 - 1] = 'G';
        cout << "tile at row " << x + size / 2 - 1 << ", column " << y + size / 2 << " with color Green" << endl;
        cout << "tile at row " << x + size / 2 << ", column " << y + size / 2 - 1 << " with color Green" << endl;
        cout << "tile at row " << x + size / 2 - 1 << ", column " << y + size / 2 - 1 << " with color Green" << endl;

    }

    tileBoard(board, size / 2, x, y + size / 2, "DL", missing_row, missing_col);
    tileBoard(board, size / 2, x, y, "DR", missing_row, missing_col);
    tileBoard(board, size / 2, x + size / 2, y, "UR",missing_row,missing_col);
    tileBoard(board, size / 2, x + size / 2, y + size / 2, "UL", missing_row, missing_col);
}

int main() {
    int n;
    do {
        cout << "Enter the value of n such that n > 1 (2^n x 2^n board): ";
        cin >> n;
        if (n <= 1) {
            cout << "n must be greater than 1" << endl;
        }
    } while (n <= 1);

    int size = pow(2, n);

    vector<vector<char>> board(size, vector<char>(size, 0));

    int missing_row, missing_column;
    do {
        cout << "Enter the row number of the missing tile (0-based indexing): ";
        cin >> missing_row;
        cout << "Enter the column number of the missing tile (0-based indexing): ";
        cin >> missing_column;
        if (missing_row < 0 || missing_row >= size || missing_column < 0 || missing_column >= size) {
            cout << "Invalid coordinates. Please enter values between 0 and " << size - 1 << "." << endl;
        }
    } while (missing_row < 0 || missing_row >= size || missing_column < 0 || missing_column >= size);

    board[missing_row][missing_column] = 'X';

    tileBoard(board, size, 0, 0, "", missing_row, missing_column);

    cout << "Board after tiling:" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}