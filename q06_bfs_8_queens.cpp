// Q06. Interactive BFS for N-Queens, default 8.
// A state stores queen columns for completed rows; BFS expands safe boards row by row.
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

int main() {
    int n = ask("Board size N", 8);
    queue<vector<int>> q; q.push({});
    while (!q.empty()) {
        vector<int> cols = q.front(); q.pop();
        if ((int)cols.size() == n) {
            for (int c : cols) cout << string(c, '.') << 'Q' << string(n - c - 1, '.') << "\n";
            return 0;
        }
        for (int c = 0; c < n; c++) if (safe(cols, c)) { auto nxt = cols; nxt.push_back(c); q.push(nxt); }
    }
    cout << "No solution.\n";
}

