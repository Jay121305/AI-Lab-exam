// Q25. Interactive predicate-logic style Bird Classification.
// User facts are checked by rules, similar to Prolog predicates.
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
    string name = ask("Bird name", "sparrow");
    set<string> f = facts(ask("Facts comma-separated", "feathers,flies,small"));
    string type = f.count("swims") && f.count("black_white") ? "Penguin" :
                  f.count("runs") && f.count("large") ? "Ostrich" :
                  f.count("feathers") && f.count("flies") ? "Flying bird" :
                  f.count("feathers") ? "Bird" : "Unknown";
    cout << name << " -> " << type << "\ncan_fly: " << boolalpha << (bool)f.count("flies") << "\n";
}

