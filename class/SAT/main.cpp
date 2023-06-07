#include <iostream>
#include <vector>
#include <string>

using namespace std;

void parse(vector<bool> &variables, vector<vector<int>> &v) {
    // Assume DIMACS CNF format w/o comments
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string filename;
    cout << "FILENAME: " << flush;
    cin >> filename;
    cout << endl;
    
    freopen(filename.c_str(),"r", stdin);
    int vars, clauses;
    string t;
    cin >> t >> t >> vars >> clauses;
    v.resize(clauses);
    variables.resize(vars);
    for (int i = 0; i < clauses; ++i) {
        v[i].resize(vars);

        int x; 
        cin >> x;
        while (x != 0) {
            v[i][abs(x) - 1] = (x > 0) - (x < 0);
            cin >> x;
        }
    }

}

bool satisfy(vector<bool> &vars, vector<int> &clause) {
    for (int i = 0; i < clause.size(); ++i) {
        if (clause[i] == 1 && vars[i] || clause[i] == -1 && !vars[i]) return true;
    }
    return false;
}

bool satisfy(vector<bool> &vars, vector<vector<int>> &v) {
    for (int i = 0; i < v.size(); ++i) {
        if (!satisfy(vars, v[i])) return false;
    }
    return true;
}

bool solve(vector<bool> &vars, vector<vector<int>> &v, int j) {
    // Base case
    if (j >= vars.size()) return satisfy(vars, v);

    vars[j] = 1;
    if (solve(vars, v, j + 1)) return true;

    vars[j] = 0;
    if (solve(vars, v, j + 1)) return true;

    return false;
}

int main() {
    vector<vector<int>> v;
    vector<bool> vars;
    parse(vars, v);
    if (solve(vars, v, 0)) {
        cout << "SATISFIABLE: ";
        for (int i = 0; i < vars.size(); ++i) {
            cout << (vars[i] ? (i + 1) : -(i + 1)) << " ";
        }
        cout << endl;
    }
    else {
        cout << "UNSATISFIABLE";
    }

    // for (int i = 0; i < v.size(); ++i) {
    //     for (int j = 0; j < v[i].size(); ++j) {
    //         cout << v[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // for (int i = 0; i < vars.size(); ++i) {
    //     cout << vars[i] << " ";
    // }

}