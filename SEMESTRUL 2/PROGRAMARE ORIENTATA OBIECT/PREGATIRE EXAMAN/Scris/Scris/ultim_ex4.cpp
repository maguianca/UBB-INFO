/*#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

class Sesiune {
private:
    vector<string> studenti;

public:
    Sesiune() = default;

    Sesiune& operator+(const string& name) {
        studenti.push_back(name);
        return *this;
    }

    Sesiune& operator=(const Sesiune& other) {
        if (this != &other) {
            studenti = other.studenti;
        }
        return *this;
    }

    vector<string>::iterator begin() {
        return studenti.begin();
    }

    vector<string>::iterator end() {
        return studenti.end();
    }

    vector<string> select(const string& sir) {
        vector<string> rez;
        for (auto& name : studenti) {
            if (name.find(sir) != string::npos) {
                rez.push_back(name);
            }
        }
        return rez;
    }

    void tipareste(ostream& out) const {
        for (const string& name : studenti) {
            out << name << " ";
        }
        out << endl;
    }
};

class Conferinta {
private:
    map<string, Sesiune*> tracks;

public:
    Conferinta() = default;

    Sesiune& track(const string& name) {
        if (tracks.find(name) == tracks.end()) {
            tracks[name] = new Sesiune();
        }
        return *tracks[name];
    }

    ~Conferinta() {
        for (auto& pair : tracks) {
            delete pair.second;
        }
        tracks.clear();
    }
};

int main() {
    Conferinta conf;

    // Add 2 attendants to "Artificial Intelligence" track
    conf.track("Artificial Intelligence") + "Ion Ion" + "Vasile Aron";

    // Add 2 attendants to "Software" track
    Sesiune& s = conf.track("Software");
    s + "Anar Lior" + "Aurora Bran";

    // Print all attendants from group "Artificial Intelligence"
    for (auto& name : conf.track("Artificial Intelligence")) {
        cout << name << ",";
    }
    cout << endl;

    // Find and print all names from "Software" track that contains "ar"
    vector<string> v = conf.track("Software").select("ar");
    for (auto& name : v) {
        cout << name << ",";
    }
    cout << endl;

    return 0;
}
*/
#include "iostream"
#include "vector"

#include "map"

using namespace std;

class Sesiune {
private:
    vector<string > v;
public:
    Sesiune& operator+ (const string& n) {
        v.push_back(n);
        return *this;
    }
    vector<string > select(const string& n) {
        vector<string> rez;
        for (const auto& p : v) {
            if (p.find(n) != std::string::npos) {
                rez.push_back(p);
            }
        }
        return rez;
    }
    vector<string >::iterator begin() {
        return v.begin();
    }
    vector<string >::iterator end() {
        return v.end();
    }
};

class Conferinta {
private:
    map<string, Sesiune> m;
public:
    Sesiune& track(const string& n)
    {
        return m[n];
    }
};
/*
int main() {
    Conferinta conf;
    conf.track("AI") + "Ion Ion" + "Vasile Aron";
    Sesiune& s = conf.track("Software");
    s + "Anar Lior" + "Aurora Bran";
    for (auto name : conf.track("AI")) {
        cout << name << ';';
    }
    vector<string> v = conf.track("Software").select("ar");
    for (auto name : v) {
        cout << name << ';';
    }

    return 0;

}*/