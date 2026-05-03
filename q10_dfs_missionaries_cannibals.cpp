// Q10. Interactive DFS for Missionaries and Cannibals.
// Safety rules reject illegal banks; DFS then searches remaining crossings.
#include <bits/stdc++.h>
using namespace std;
using State = tuple<int,int,char>;

int totalPeople, boatCap;

int ask(string msg, int def) {
    cout << msg << " [" << def << "]: ";
    string s; getline(cin, s);
    return s.empty() ? def : stoi(s);
}

bool safe(int m, int c) {
    int rm = totalPeople - m, rc = totalPeople - c;
    return m >= 0 && c >= 0 && m <= totalPeople && c <= totalPeople && (m == 0 || m >= c) && (rm == 0 || rm >= rc);
}

vector<State> children(State s) {
    auto [m, c, side] = s; vector<State> out;
    for (int dm = 0; dm <= boatCap; dm++) for (int dc = 0; dc <= boatCap; dc++) if (dm + dc >= 1 && dm + dc <= boatCap) {
        int nm = side == 'L' ? m - dm : m + dm, nc = side == 'L' ? c - dc : c + dc;
        if (safe(nm, nc)) out.push_back({nm, nc, side == 'L' ? 'R' : 'L'});
    }
    return out;
}

int main() {
    totalPeople = ask("Number of missionaries and cannibals", 3);
    boatCap = ask("Boat capacity", 2);
    State start = {totalPeople, totalPeople, 'L'}, goal = {0, 0, 'R'};
    stack<pair<State, vector<State>>> st; set<State> seen; st.push({start, {start}});
    while (!st.empty()) {
        auto [s, path] = st.top(); st.pop();
        if (seen.count(s)) continue; seen.insert(s);
        if (s == goal) { for (auto [m, c, side] : path) cout << "(" << m << ", " << c << ", " << side << ")\n"; return 0; }
        for (State n : children(s)) { auto p = path; p.push_back(n); st.push({n, p}); }
    }
    cout << "No solution.\n";
}

