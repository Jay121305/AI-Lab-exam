// Q20. Interactive A* Search for route finding.
// A* combines actual road cost g with straight-line estimate h to find a low-cost path.
#include <bits/stdc++.h>
using namespace std;

map<string, vector<pair<string,int>>> graph = {
    {"Arad",{{"Zerind",75},{"Sibiu",140},{"Timisoara",118}}}, {"Zerind",{{"Arad",75},{"Oradea",71}}},
    {"Oradea",{{"Zerind",71},{"Sibiu",151}}}, {"Sibiu",{{"Arad",140},{"Oradea",151},{"Fagaras",99},{"Rimnicu",80}}},
    {"Timisoara",{{"Arad",118},{"Lugoj",111}}}, {"Lugoj",{{"Timisoara",111},{"Mehadia",70}}},
    {"Mehadia",{{"Lugoj",70},{"Drobeta",75}}}, {"Drobeta",{{"Mehadia",75},{"Craiova",120}}},
    {"Craiova",{{"Drobeta",120},{"Rimnicu",146},{"Pitesti",138}}}, {"Rimnicu",{{"Sibiu",80},{"Craiova",146},{"Pitesti",97}}},
    {"Fagaras",{{"Sibiu",99},{"Bucharest",211}}}, {"Pitesti",{{"Rimnicu",97},{"Craiova",138},{"Bucharest",101}}},
    {"Bucharest",{{"Fagaras",211},{"Pitesti",101}}}
};
map<string, pair<int,int>> pos = {{"Arad",{91,492}},{"Zerind",{108,531}},{"Oradea",{131,571}},{"Sibiu",{207,457}},{"Timisoara",{94,410}},{"Lugoj",{165,379}},{"Mehadia",{168,339}},{"Drobeta",{165,299}},{"Craiova",{253,288}},{"Rimnicu",{233,410}},{"Fagaras",{305,449}},{"Pitesti",{320,368}},{"Bucharest",{400,327}}};

string askCity(string msg, string def) {
    cout << msg << " [" << def << "]: ";
    string s; getline(cin, s); if (s.empty()) s = def;
    return graph.count(s) ? s : def;
}

int h(string a, string goal) {
    auto [x1,y1] = pos[a]; auto [x2,y2] = pos[goal];
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

int main() {
    cout << "Cities: "; for (auto [c, _] : graph) cout << c << " "; cout << "\n";
    string start = askCity("Start city", "Arad"), goal = askCity("Goal city", "Bucharest");
    using Node = tuple<int,int,string,vector<string>>;
    priority_queue<Node, vector<Node>, greater<Node>> pq; map<string,int> best;
    pq.push({h(start, goal), 0, start, {start}}); best[start] = 0;
    while (!pq.empty()) {
        auto [f, cost, city, path] = pq.top(); pq.pop();
        if (city == goal) { cout << "Route: "; for (string c : path) cout << c << " "; cout << "\nOptimal cost: " << cost << "\n"; return 0; }
        for (auto [n, d] : graph[city]) if (!best.count(n) || cost + d < best[n]) {
            best[n] = cost + d; auto p = path; p.push_back(n); pq.push({cost + d + h(n, goal), cost + d, n, p});
        }
    }
}

