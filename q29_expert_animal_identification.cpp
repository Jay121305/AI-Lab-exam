// Q29. Interactive expert system for Animal Identification.
// Observed features are compared with expert rules to identify an animal.
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

bool has(set<string>& f, initializer_list<string> need) {
    for (string x : need) if (!f.count(x)) return false;
    return true;
}

int main() {
    set<string> f = facts(ask("Observed features", "fur,stripes,carnivore"));
    string animal = has(f, {"feathers","flies"}) ? "Eagle" : has(f, {"fur","stripes","carnivore"}) ? "Tiger" :
                    has(f, {"fur","long_neck","spots"}) ? "Giraffe" : has(f, {"scales","swims"}) ? "Fish" : "Unknown animal";
    cout << "Animal: " << animal << "\n";
}

