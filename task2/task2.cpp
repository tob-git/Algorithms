#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
using namespace std;

// All possible knight moves (row, col)
static const int moves[8][2] = {
    {-2, -1}, {-2, +1},
    {-1, -2}, {-1, +2},
    {+1, -2}, {+1, +2},
    {+2, -1}, {+2, +1}
};

bool isValid(int r, int c, int n, const vector<vector<bool>>& visited) {
    return (r >= 0 && r < n && c >= 0 && c < n && !visited[r][c]);
}

// Count how many onward moves are possible from (r,c)
int countOnwardMoves(int r, int c, int n, const vector<vector<bool>>& visited) {
    int count = 0;
    for (int i = 0; i < 8; ++i) {
        int rr = r + moves[i][0];
        int cc = c + moves[i][1];
        if (isValid(rr, cc, n, visited)) {
            count++;
        }
    }
    return count;
}

bool warnsdorffTour(int r, int c, int moveCount,
                    int n, vector<vector<bool>>& visited,
                    vector<pair<int,int>>& path)
{
    // If we have visited all squares, we're done (open tour found)
    if (moveCount == n*n) {
        // path[0] is the starting position; check if current (r, c)
        // can jump back to path[0].
        int startR = path[0].first;
        int startC = path[0].second;
        for (int i = 0; i < 8; ++i) {
            int rr = r + moves[i][0];
            int cc = c + moves[i][1];
            // If we can reach the start square, it's a closed tour
            if (rr == startR && cc == startC) {
                return true; // closed tour found
            }
        }
        return false; // can't jump back -> open tour
    }


    // Generate all possible next moves
    vector<pair<int,int>> candidates;
    for (int i = 0; i < 8; ++i) {
        int rr = r + moves[i][0];
        int cc = c + moves[i][1];
        if (isValid(rr, cc, n, visited)) {
            candidates.push_back({rr, cc});
        }
    }

    // Sort the candidates by the number of onward moves (ascending)
    std::sort(candidates.begin(), candidates.end(),
[&](auto &a, auto &b)
{
    int onwardA = countOnwardMoves(a.first, a.second, n, visited);
    int onwardB = countOnwardMoves(b.first, b.second, n, visited);

    // 1) Primary criterion: fewer onward moves comes first
    if (onwardA != onwardB) {
        return onwardA < onwardB;
    }

    // 2) Tie-breaker: the one that's farther from (0,0) comes first.
    //    We'll compare squared distances to avoid unnecessary sqrt calls.
    long long distA = static_cast<long long>(a.first) * a.first
                    + static_cast<long long>(a.second) * a.second;
    long long distB = static_cast<long long>(b.first) * b.first
                    + static_cast<long long>(b.second) * b.second;

    // If A is farther than B, then A should come first => return true
    // (since "true" means "a < b" in the sense that 'a' precedes 'b' in the sorted output).
    return distA > distB;
});
    // Try each candidate move in ascending order of onward-degree
    for (auto &cand : candidates) {
        int rr = cand.first;
        int cc = cand.second;
        visited[rr][cc] = true;
        path.push_back({rr, cc});

        if (warnsdorffTour(rr, cc, moveCount + 1, n, visited, path)) {
            return true;
        }

        // backtrack
        visited[rr][cc] = false;
        path.pop_back();
    }

    // If all candidates fail, return false
    return false;
}




int main() {
    int n;
    cout << "Enter the board size (n x n): ";
    cin >> n;

    vector<vector<bool>> visited(n, vector<bool>(n, false));
    vector<pair<int,int>> path;

    // Choose a starting position, e.g., top-left corner (0,0)
    // Determine a "center" starting position.
    int row = n / 2;
    if (n % 2 == 0) {
        // Shift one cell for even-size boards
        row -= 1;
    }
    int col = row;
    // Mark the chosen start cell as visited and push it onto the path
    visited[row][col] = true;
    path.push_back({row, col});

    auto startTime1 = std::chrono::high_resolution_clock::now();

    bool success = warnsdorffTour(row, col, 1, n, visited, path);
    auto endTime1 = std::chrono::high_resolution_clock::now();

    // Calculate elapsed time in microseconds (or milliseconds, if you prefer)
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime1 - startTime1);

    // Print the result
    std::cout << "Sorting took " << duration.count() << " microseconds.\n";

    if (success) {
        cout << "Knight's tour found:\n";
        for (int i = 0; i < (int)path.size(); ++i) {
            cout << "(" << path[i].first << ", " << path[i].second << ") ";
        }
        cout << endl;
        // You can also check if path.back() can jump back to path.front() for a closed cycle
    } else {
        cout << "No tour found by this heuristic (try different start or backtracking).\n";
    }


    return 0;
}
