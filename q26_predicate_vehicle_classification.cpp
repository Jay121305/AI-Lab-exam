// Q26. Interactive predicate-logic style Vehicle Classification.
// Facts like wheels_4 and rails are tested by classification rules.
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
    string name = ask("Vehicle name", "car");
    set<string> f = facts(ask("Facts comma-separated", "wheels_4,engine,road"));
    string type = f.count("rails") ? "Train" : f.count("public") && f.count("wheels_4") ? "Bus" :
                  f.count("wheels_4") ? "Car" : f.count("wheels_2") ? "Two-wheeler" : "Unknown vehicle";
    cout << name << " -> " << type << "\n";
}

