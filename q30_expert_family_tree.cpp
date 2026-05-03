// Q30. Interactive expert system for Family Tree.
// It infers father, mother, grandparent, sibling, and cousin from facts.
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
    set<string> people = male; people.insert(female.begin(), female.end());
    auto sibling = [&](string a, string b){ for (auto [p, c] : parent) if (a != b && parent.count({p,a}) && parent.count({p,b})) return true; return false; };
    auto relation = [&](string a, string b) {
        if (parent.count({a,b})) return male.count(a) ? "father" : "mother";
        for (string x : people) if (parent.count({a,x}) && parent.count({x,b})) return "grandparent";
        if (sibling(a,b)) return "sibling";
        for (string p1 : people) for (string p2 : people) if (parent.count({p1,a}) && parent.count({p2,b}) && sibling(p1,p2)) return "cousin";
        return "no direct rule found";
    };
    string line = ask("Ask relation as person1 person2", "john sue");
    stringstream ss(line); string a, b; ss >> a >> b;
    cout << a << " -> " << b << ": " << relation(a, b) << "\n";
}

