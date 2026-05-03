// Q24. Interactive predicate-logic style Family Tree.
// Facts are sets; rule functions infer father, mother, sibling, and grandparent.
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

set<string> nameSet(string s) { vector<string> v = split(s, ','); return set<string>(v.begin(), v.end()); }

set<pair<string,string>> pairSet(string s) {
    set<pair<string,string>> out;
    for (string p : split(s, ',')) { auto x = split(p, '-'); if (x.size() == 2) out.insert({x[0], x[1]}); }
    return out;
}

int main() {
    set<string> male = nameSet(ask("Male names", "john,bob,alex"));
    set<string> female = nameSet(ask("Female names", "mary,ann,sue"));
    set<pair<string,string>> parent = pairSet(ask("Parent-child facts", "john-bob,mary-bob,john-ann,mary-ann,bob-sue,ann-alex"));
    auto father = [&](string x, string y){ return male.count(x) && parent.count({x,y}); };
    auto mother = [&](string x, string y){ return female.count(x) && parent.count({x,y}); };
    auto sibling = [&](string x, string y){ for (auto [p, c] : parent) if (x != y && parent.count({p,x}) && parent.count({p,y})) return true; return false; };
    auto grandparent = [&](string x, string y){ for (auto [p, mid] : parent) if (p == x && parent.count({mid,y})) return true; return false; };
    int q = stoi(ask("Number of queries", "4"));
    vector<string> def = {"father john bob", "mother mary ann", "sibling bob ann", "grandparent john sue"};
    for (int i = 0; i < q; i++) {
        string line = ask("Query: rule person1 person2", def[i % def.size()]);
        stringstream ss(line); string rule, a, b; ss >> rule >> a >> b;
        bool ans = rule == "father" ? father(a,b) : rule == "mother" ? mother(a,b) : rule == "sibling" ? sibling(a,b) : rule == "grandparent" ? grandparent(a,b) : false;
        cout << rule << "(" << a << ", " << b << ") = " << boolalpha << ans << "\n";
    }
}
