#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

enum Color { BLUE, GREEN, RED, WHITE };

struct Square {
    int x, y;
    Color color;
    bool tiled = false;
    Square() : x(0), y(0), color(WHITE), tiled(false) {}
    Square(int x, int y) : x(x), y(y) {}
};

Color getNextColor(Color color) {
    switch (color) {
        case BLUE:
            return GREEN;
        case GREEN:
            return RED;
        case RED:
            return BLUE;
        default:
            return WHITE;
    }
}

void tileBoard(vector<vector<Square>>& board, int x, int y, int size, int missing_x, int missing_y) {
    if (size == 1) {
        return;
    }
    
    int half = size / 2;
    int mx = x + half;
    int my = y + half;

    if (missing_x >= mx && missing_y >= my) {
        board[mx - 1][my - 1].tiled = true;
        board[mx - 1][my].tiled = true;
        board[mx][my - 1].tiled = true;
        cout<<"place tromino on points ("<<mx-1<<","<<my-1<<")"<<",("<<mx-1<<","<<my<<")"<<",("<<mx<<","<<my-1<<")"<<endl;

    } else if (missing_x < mx && missing_y >= my) {
        board[mx - 1][my - 1].tiled = true;
        board[mx][my - 1].tiled = true;
        board[mx][my].tiled = true;
        cout<<"place tromino on points ("<<mx-1<<","<<my-1<<")"<<",("<<mx<<","<<my-1<<")"<<",("<<mx<<","<<my<<")"<<endl;
    } else if (missing_x >= mx && missing_y < my) {
        board[mx - 1][my - 1].tiled = true;
        board[mx - 1][my].tiled = true;
        board[mx][my].tiled = true;
        cout<<"place tromino on points ("<<mx-1<<","<<my-1<<")"<<",("<<mx-1<<","<<my<<")"<<",("<<mx<<","<<my<<")"<<endl;
    } else {
        board[mx - 1][my].tiled = true;
        board[mx][my - 1].tiled = true;
        board[mx][my].tiled = true;
        cout<<"place tromino on points ("<<mx-1<<","<<my<<")"<<",("<<mx<<","<<my-1<<")"<<",("<<mx<<","<<my<<")"<<endl;
    }

    if (missing_x < mx && missing_y < my) {
        tileBoard(board, x, y, half, missing_x, missing_y);
    } else {
        tileBoard(board, x, y, half, mx - 1, my - 1);
    }
    
    if (missing_x < mx && missing_y >= my) {
        tileBoard(board, x, my, half, missing_x, missing_y);
    } else {
        tileBoard(board, x, my, half, mx - 1, my);
    }
    
    if (missing_x >= mx && missing_y < my) {
        tileBoard(board, mx, y, half, missing_x, missing_y);
    } else {
        tileBoard(board, mx, y, half, mx, my - 1);
    }
    
    if (missing_x >= mx && missing_y >= my) {
        tileBoard(board, mx, my, half, missing_x, missing_y);
    } else {
        tileBoard(board, mx, my, half, mx, my);
    }
    
    

}

int main() {
    int n;
    do {
        cout << "Enter the value of n such that n > 1: ";
        cin >> n;
        if (n <= 1) {
            cout << "Invalid n, must be greater than 1" << endl;
        }
    } while (n <= 1);
    
    int size = pow(2, n);
    vector<vector<Square>> board(size, vector<Square>(size));

    int missing_x, missing_y;
    
    do {
        cout << "Enter the X-Coordinate of the missing square (0-based): ";
        cin >> missing_x;
        cout << "Enter the Y-Coordinate of the missing square (0-based): ";
        cin >> missing_y;
        if (missing_x < 0 || missing_x >= size || missing_y < 0 || missing_y >= size) {
            cout << "Invalid coordinates, out of range" << endl;
        }
    } while (missing_x < 0 || missing_x >= size || missing_y < 0 || missing_y >= size);
    Square missing_square(missing_x, missing_y);
    missing_square.color = WHITE;
    board[missing_x][missing_y] = missing_square;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i != missing_x || j != missing_y) {
                Square s(i, j);
                s.color = WHITE;
                board[i][j] = s;
            }
        }
    }
    cout<< "board before tiling: "<<endl;
    for (const auto& row : board) {
        for (const Square& cell : row) {
            cout << cell.tiled <<" ";
        }
        cout << endl;
    }

    tileBoard(board, 0, 0, size, missing_x, missing_y);

    cout<< "board after tiling: "<<endl;

    for (const auto& row : board) {
        for (const Square& cell : row) {
            cout << cell.tiled <<" ";
        }
        cout << endl;
    }
    
} 