// Q07. Interactive DFS for Water-Jug.
// DFS follows one branch deeply; visited states prevent repeated loops.
#include <bits/stdc++.h>
using namespace std;

int ask(string msg, int def) {
    cout << msg << " [" << def << "]: ";
    string s; getline(cin, s);
    return s.empty() ? def : stoi(s);
}

vector<pair<int,int>> nextStates(pair<int,int> s, int ca, int cb) {
    auto [a, b] = s; int ab = min(a, cb - b), ba = min(b, ca - a);
    return {{ca,b},{a,cb},{0,b},{a,0},{a-ab,b+ab},{a+ba,b-ba}};
}

int main() {
    int ca = ask("Capacity of jug A", 4), cb = ask("Capacity of jug B", 3), goal = ask("Required amount", 2);
    stack<pair<pair<int,int>, vector<pair<int,int>>>> st; set<pair<int,int>> seen;
    st.push({{0,0}, {{0,0}}});
    while (!st.empty()) {
        auto [s, path] = st.top(); st.pop();
        if (seen.count(s)) continue;
        seen.insert(s);
        if (s.first == goal || s.second == goal) {
            for (auto [a, b] : path) cout << "(" << a << ", " << b << ")\n";
            return 0;
        }
        for (auto n : nextStates(s, ca, cb)) { auto p = path; p.push_back(n); st.push({n, p}); }
    }
    cout << "No solution.\n";
}

