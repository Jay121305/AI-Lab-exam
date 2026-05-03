// Q02. Interactive BFS for Water-Jug.
// BFS explores states level by level, so the first goal path is shortest.
#include <bits/stdc++.h>
using namespace std;

int ask(string msg, int def) {
    cout << msg << " [" << def << "]: ";
    string s; getline(cin, s);
    return s.empty() ? def : stoi(s);
}

vector<pair<int,int>> nextStates(pair<int,int> s, int ca, int cb) {
    auto [a, b] = s;
    int ab = min(a, cb - b), ba = min(b, ca - a);
    vector<pair<int,int>> v = {{ca,b},{a,cb},{0,b},{a,0},{a-ab,b+ab},{a+ba,b-ba}};
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    return v;
}

int main() {
    int ca = ask("Capacity of jug A", 4), cb = ask("Capacity of jug B", 3), goal = ask("Required amount", 2);
    pair<int,int> start = {0, 0};
    queue<pair<int,int>> q;
    map<pair<int,int>, pair<int,int>> parent;
    pair<int,int> end = {-1, -1};
    q.push(start); parent[start] = {-1, -1};
    while (!q.empty()) {
        auto s = q.front(); q.pop();
        if (s.first == goal || s.second == goal) { end = s; break; }
        for (auto n : nextStates(s, ca, cb)) if (!parent.count(n)) parent[n] = s, q.push(n);
    }
    if (end.first == -1) { cout << "No solution found.\n"; return 0; }
    vector<pair<int,int>> path;
    for (auto s = end; s.first != -1; s = parent[s]) path.push_back(s);
    reverse(path.begin(), path.end());
    cout << "Shortest path:\n";
    for (auto [a, b] : path) cout << "(" << a << ", " << b << ")\n";
}
