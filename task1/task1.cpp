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
                        cout<<"tile placed at ("<<x+i<<","<<y+j<<")"<<" with color Red"<<endl;
                        
                    }
                    else if (location == "DR" || location == "UL") {
                        board[x + i][y + j] = 'B';
                        cout<<"tile placed at ("<<x+i<<","<<y+j<<")"<<" with color Blue"<<endl;
                        
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
        cout<<"tile placed at ("<<x+n/2<<","<<y+n/2-1<<")"<<" with color Green"<<endl;
        cout<<"tile placed at ("<<x+n/2<<","<<y+n/2<<")"<<" with color Green"<<endl;
        cout<<"tile placed at ("<<x+n/2-1<<","<<y+n/2<<")"<<" with color Green"<<endl;
    }
    else if (r >= x + n / 2 && c < y + n / 2) {
        board[x + n / 2 - 1][y + n / 2] = 'G';
        board[x + n / 2][y + n / 2] = 'G';
        board[x + n / 2 - 1][y + n / 2 - 1] = 'G';
        cout<<"tile placed at ("<<x+n/2-1<<","<<y+n/2<<")"<<" with color Green"<<endl;
        cout<<"tile placed at ("<<x+n/2<<","<<y+n/2<<")"<<" with color Green"<<endl;
        cout<<"tile placed at ("<<x+n/2-1<<","<<y+n/2-1<<")"<<" with color Green"<<endl;
        
    }
    else if (r < x + n / 2 && c >= y + n / 2) {
        board[x + n / 2][y + n / 2 - 1] = 'G';
        board[x + n / 2][y + n / 2] = 'G';
        board[x + n / 2 - 1][y + n / 2 - 1] = 'G';
        cout<<"tile placed at ("<<x+n/2<<","<<y+n/2-1<<")"<<" with color Green"<<endl;
        cout<<"tile placed at ("<<x+n/2<<","<<y+n/2<<")"<<" with color Green"<<endl;
        cout<<"tile placed at ("<<x+n/2-1<<","<<y+n/2-1<<")"<<" with color Green"<<endl;
        
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

    int missing_x, missing_y;
    do {
        cout << "Enter the row number of the missing tile (0-based indexing): ";
        cin >> missing_x;
        cout << "Enter the column number of the missing tile (0-based indexing): ";
        cin >> missing_y;
        if (missing_x < 0 || missing_x >= size || missing_y < 0 || missing_y >= size) {
            cout << "Invalid coordinates. Please enter values between 0 and " << size - 1 << "." << endl;
        }
    } while (missing_x < 0 || missing_x >= size || missing_y < 0 || missing_y >= size);

    board[missing_x][missing_y] = 'x';

    tileBoard(board, size, 0, 0, "UR");

    cout << "Board after tiling:" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}