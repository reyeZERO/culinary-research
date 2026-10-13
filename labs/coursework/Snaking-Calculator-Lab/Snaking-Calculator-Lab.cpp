#include <iostream>
#include <vector>
#include <cctype>
using namespace std;

long long applyOp(long long total, char op, int d) {
    if (op == '+') return total + d;
    if (op == '-') return total - d;
    return total * d;
}

long long evalRow(const vector<string>& grid, int row, size_t col, char op, long long total) {
    if (col >= grid[row].size()) return total;
    char ch = grid[row][col];

    if (isdigit(static_cast<unsigned char>(ch)))
        return evalRow(grid, row, col + 1, op, applyOp(total, op, ch - '0'));
    if (ch == '+' || ch == '-' || ch == '*')
        return evalRow(grid, row, col + 1, ch, total);
    if (ch == '^' || ch == 'v') {
        int nextRow = (ch == '^') ? row - 1 : row + 1;
        long long afterBranch = evalRow(grid, nextRow, col, op, total);
        return evalRow(grid, row, col + 1, op, afterBranch);
    }
    return evalRow(grid, row, col + 1, op, total);
}

long long evaluate(const vector<string>& grid) {
    return evalRow(grid, 0, 0, '+', 0);
}

int main() {
    vector<string> grid = {
        "257*233+6v790-12",
        "61247833212+*9^3"
    };
    cout << evaluate(grid) << '\n';
    return 0;
}
