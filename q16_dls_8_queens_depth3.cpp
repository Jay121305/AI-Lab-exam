// Q16. Interactive DLS for N-Queens.
// One queen is placed per depth, so depth 3 gives only a partial 8-Queen board.
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

bool dls(int n, int depth, vector<int>& cols) {
    if ((int)cols.size() == n) return true;
    if (depth == 0) return false;
    for (int c = 0; c < n; c++) if (safe(cols, c)) {
        cols.push_back(c);
        if (dls(n, depth - 1, cols)) return true;
        cols.pop_back();
    }
    return false;
}

bool partial(int n, int limit, vector<int>& cols) {
    if ((int)cols.size() == min(n, limit)) return true;
    for (int c = 0; c < n; c++) if (safe(cols, c)) { cols.push_back(c); if (partial(n, limit, cols)) return true; cols.pop_back(); }
    return false;
}

int main() {
    int n = ask("Board size N", 8), limit = ask("Depth limit", 3);
    vector<int> full, part;
    if (dls(n, limit, full)) {
        cout << "Full solution:\n";
        for (int c : full) cout << string(c, '.') << 'Q' << string(n - c - 1, '.') << "\n";
    } else {
        cout << "Full solution: not found within depth " << limit << "\n";
        partial(n, limit, part);
        cout << "Safe partial placement: "; for (int c : part) cout << c << ' '; cout << "\n";
    }
}
