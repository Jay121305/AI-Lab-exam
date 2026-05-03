// Q27. Interactive predicate-logic style Fruit/Vegetable Classification.
// Rules use facts such as has_seeds, from_flower, root, leaf, and stem.
#include <bits/stdc++.h>
using namespace std;

string ask(string msg, string def) {
    cout << msg << " [" << def << "]: ";
    string s; getline(cin, s);
    return s.empty() ? def : s;
}

set<string> facts(string s) {
    set<string> f; string x; stringstream ss(s);
    while (getline(ss, x, ',')) if (!x.empty()) f.insert(x);
    return f;
}

int main() {
    string item = ask("Item name", "apple");
    set<string> f = facts(ask("Facts comma-separated", "has_seeds,sweet,from_flower"));
    string type = f.count("has_seeds") && f.count("from_flower") ? "Fruit" :
                  (f.count("root") || f.count("leaf") || f.count("stem")) ? "Vegetable" : "Unknown";
    cout << item << " -> " << type << "\n";
}

