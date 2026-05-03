// Q21. Interactive CSP for N-Queens, default 8.
// Rows are variables, columns are values, and constraints avoid attacks.
#include <bits/stdc++.h>
using namespace std;

int ask(string msg, int def) {
    cout << msg << " [" << def << "]: ";
    string s; getline(cin, s);
    return s.empty() ? def : stoi(s);
}

bool safe(vector<int>& cols, int col) {
    int row = cols.size();
    for (int r = 0; r < row; r++) if (cols[r] == col || abs(cols[r] - col) == row - r) return false;
    return true;
}

bool solve(int n, vector<int>& cols) {
    if ((int)cols.size() == n) return true;
    for (int c = 0; c < n; c++) if (safe(cols, c)) {
        cols.push_back(c);
        if (solve(n, cols)) return true;
        cols.pop_back();
    }
    return false;
}

int main() {
    int n = ask("Board size N", 8);
    vector<int> cols;
    if (!solve(n, cols)) { cout << "No solution.\n"; return 0; }
    for (int c : cols) cout << string(c, '.') << 'Q' << string(n - c - 1, '.') << "\n";
}

