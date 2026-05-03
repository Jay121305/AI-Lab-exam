// Q23. Interactive Graph Colouring CSP.
// Vertices are variables, colours are values, and adjacent vertices cannot match.
#include <bits/stdc++.h>
using namespace std;

string ask(string msg, string def) {
    cout << msg << " [" << def << "]: ";
    string s; getline(cin, s);
    return s.empty() ? def : s;
}

vector<string> split(string s, char sep) {
    vector<string> out; string x; stringstream ss(s);
    while (getline(ss, x, sep)) if (!x.empty()) out.push_back(x);
    return out;
}

bool solve(int i, vector<string>& v, vector<string>& colors, map<string,vector<string>>& g, map<string,string>& ans) {
    if (i == (int)v.size()) return true;
    string node = v[i];
    for (string color : colors) {
        bool ok = true;
        for (string nb : g[node]) if (ans[nb] == color) ok = false;
        if (ok) { ans[node] = color; if (solve(i + 1, v, colors, g, ans)) return true; ans.erase(node); }
    }
    return false;
}

int main() {
    vector<string> vertices = split(ask("Vertices comma-separated", "WA,NT,SA,Q,NSW,V"), ',');
    vector<string> edges = split(ask("Edges as A-B comma-separated", "WA-NT,WA-SA,NT-SA,NT-Q,SA-Q,SA-NSW,SA-V,Q-NSW,NSW-V"), ',');
    vector<string> colors = split(ask("Colours comma-separated", "Red,Green,Blue"), ',');
    map<string,vector<string>> graph; for (string v : vertices) graph[v];
    for (string e : edges) {
        vector<string> p = split(e, '-');
        if (p.size() == 2) graph[p[0]].push_back(p[1]), graph[p[1]].push_back(p[0]);
    }
    map<string,string> ans;
    if (!solve(0, vertices, colors, graph, ans)) { cout << "No colouring possible.\n"; return 0; }
    for (auto [v, c] : ans) cout << v << " -> " << c << "\n";
}

