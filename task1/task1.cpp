#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

enum Color { BLUE, BLACK, RED };

struct Tromino {
    int x, y;
    Color color;
    Tromino(int x, int y, Color c) : x(x), y(y), color(c) {}
};

void tileBoard(vector<vector<int>>& board, int x, int y, int size, int missing_x, int missing_y, int& tile_id) {
    if (size == 1) {
        return;
    }
    
    int half = size / 2;
    int mx = x + half;
    int my = y + half;
    int quad_x; int quad_y;
    if(missing_x < mx){
        quad_x = x;
    } else {
        quad_x = mx;
    }
    if(missing_y < my){
        quad_y = y;
    } else {
        quad_y = my;
    }
    
    tile_id++;
    
    if (missing_x >= mx && missing_y >= my) {
        board[mx - 1][my - 1] = tile_id;
        board[mx - 1][my] = tile_id;
        board[mx][my - 1] = tile_id;
    } else if (missing_x < mx && missing_y >= my) {
        board[mx - 1][my - 1] = tile_id;
        board[mx][my - 1] = tile_id;
        board[mx][my] = tile_id;
    } else if (missing_x >= mx && missing_y < my) {
        board[mx - 1][my - 1] = tile_id;
        board[mx - 1][my] = tile_id;
        board[mx][my] = tile_id;
    } else {
        board[mx - 1][my] = tile_id;
        board[mx][my - 1] = tile_id;
        board[mx][my] = tile_id;
    }
    
    if (missing_x < mx && missing_y < my) {
        tileBoard(board, x, y, half, missing_x, missing_y, tile_id);
    } else {
        tileBoard(board, x, y, half, mx - 1, my - 1, tile_id);
    }
    
    if (missing_x < mx && missing_y >= my) {
        tileBoard(board, x, my, half, missing_x, missing_y, tile_id);
    } else {
        tileBoard(board, x, my, half, mx - 1, my, tile_id);
    }
    
    if (missing_x >= mx && missing_y < my) {
        tileBoard(board, mx, y, half, missing_x, missing_y, tile_id);
    } else {
        tileBoard(board, mx, y, half, mx, my - 1, tile_id);
    }
    
    if (missing_x >= mx && missing_y >= my) {
        tileBoard(board, mx, my, half, missing_x, missing_y, tile_id);
    } else {
        tileBoard(board, mx, my, half, mx, my, tile_id);
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
    vector<vector<int>> board(size, vector<int>(size, 1));
    int missing_x, missing_y;
    
    do {
        cout << "Enter the X-Coordinate of the missing square (0-based): ";
        cin >> missing_x;
        cout << "Enter the Y-Coordinate of the missing square (0-based): ";
        cin >> missing_y;
        if (missing_x < 0 || missing_x >= size || missing_y < 0 || missing_y >= size) {
            cout << "Invalid coordinates, out of range." << endl;
        }
    } while (missing_x < 0 || missing_x >= size || missing_y < 0 || missing_y >= size);
    
    board[missing_x][missing_y] = 0;
    int tile_id = 1;
    tileBoard(board, 0, 0, size, missing_x, missing_y, tile_id);
    
    for (const auto& row : board) {
        for (int cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
    
} 