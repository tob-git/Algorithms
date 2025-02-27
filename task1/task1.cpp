#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void tileBoard(vector<vector<char>>& board, int n, int x, int y, string location) {
    if (n == 2) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[x + i][y + j] == 0) {
                    if (location == "UR" || location == "DL") {
                        board[x + i][y + j] = 'R';
                        cout<<"tile placed at row "<<x+i<<", column "<<y+j<<" with color Red"<<endl;
                        
                    }
                    else if (location == "DR" || location == "UL") {
                        board[x + i][y + j] = 'B';
                        cout<<"tile placed at row "<<x+i<<", column "<<y+j<<" with color Blue"<<endl;
                        
                    }
                }
            }
        }
        return;
    }

    int r = 0, c = 0;
    for (int i = x; i < x + n; i++) {
        for (int j = y; j < y + n; j++) {
            if (board[i][j] != 0) {
                r = i;
                c = j;
            }
        }
    }

    if (r < x + n / 2 && c < y + n / 2) {
        board[x + n / 2][y + n / 2 - 1] = 'G';
        board[x + n / 2][y + n / 2] = 'G';
        board[x + n / 2 - 1][y + n / 2] = 'G';
        cout<<"tile placed at row "<<x+n/2<<", column "<<y+n/2-1<<" with color Green"<<endl;
        cout<<"tile placed at row "<<x+n/2<<", column "<<y+n/2<<" with color Green"<<endl;
        cout<<"tile placed at row "<<x+n/2-1<<", column "<<y+n/2<<" with color Green"<<endl;
    }
    else if (r >= x + n / 2 && c < y + n / 2) {
        board[x + n / 2 - 1][y + n / 2] = 'G';
        board[x + n / 2][y + n / 2] = 'G';
        board[x + n / 2 - 1][y + n / 2 - 1] = 'G';
        cout<<"tile placed at row "<<x+n/2-1<<", column "<<y+n/2<<" with color Green"<<endl;
        cout<<"tile placed at row "<<x+n/2<<", column "<<y+n/2<<" with color Green"<<endl;
        cout<<"tile placed at row "<<x+n/2-1<<", column "<<y+n/2-1<<" with color Green"<<endl;
        
    }
    else if (r < x + n / 2 && c >= y + n / 2) {
        board[x + n / 2][y + n / 2 - 1] = 'G';
        board[x + n / 2][y + n / 2] = 'G';
        board[x + n / 2 - 1][y + n / 2 - 1] = 'G';
        cout<<"tile placed at row "<<x+n/2<<", column "<<y+n/2-1<<" with color Green"<<endl;
        cout<<"tile placed at row "<<x+n/2<<", column "<<y+n/2<<" with color Green"<<endl;
        cout<<"tile placed at row "<<x+n/2-1<<", column "<<y+n/2-1<<" with color Green"<<endl;
        
    }
    else if (r >= x + n / 2 && c >= y + n / 2) {
        board[x + n / 2 - 1][y + n / 2] = 'G';
        board[x + n / 2][y + n / 2 - 1] = 'G';
        board[x + n / 2 - 1][y + n / 2 - 1] = 'G';
        cout<<"tile placed at ("<<x+n/2-1<<","<<y+n/2<<")"<<" with color Green"<<endl;
        cout<<"tile placed at ("<<x+n/2<<","<<y+n/2-1<<")"<<" with color Green"<<endl;
        cout<<"tile placed at ("<<x+n/2-1<<","<<y+n/2-1<<")"<<" with color Green"<<endl;
        
    }

    tileBoard(board, n / 2, x, y + n / 2, "DL");
    tileBoard(board, n / 2, x, y, "DR");
    tileBoard(board, n / 2, x + n / 2, y, "UR");
    tileBoard(board, n / 2, x + n / 2, y + n / 2, "UL");
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

    board[missing_row][missing_column] = 'x';

    tileBoard(board, size, 0, 0, "UR");

    cout << "Board after tiling:" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}