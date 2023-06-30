#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int edges[200005];
vector<int> adj[200005];
unordered_set<int> deleted, v;

int dfs(int n){
    if (deleted.find(n) != deleted.end() || v.find(n) != v.end()) return 0;
    v.insert(n);
    int size = 1;
    for (int x: adj[n]) {
        if (deleted.find(x) != deleted.end() || v.find(x) != v.end()) continue;
        size += dfs(x);
    }
    return size;
}

void del(int n, int k){
    // n: deleted node
    // k: min degree
    deleted.insert(n);
    for (int x : adj[n]) {
        if (deleted.find(x) != deleted.end()) continue;
        edges[x]--;
        if (edges[x] < k) del(x, k);
    }
}

int main(){
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        edges[a]++;
        edges[b]++;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int best = 0;
    for (int x = 1; x < m; ++x) {
        // x = O(sqrt(m))
        // delete nodes with degree < x O(m)
        // dfs O(n)

        // delete node:
        //  recursively delete nodes with degree < x
        
        for (int i = 0; i < n; ++i) {
            if (deleted.find(i) != deleted.end()) continue;
            if (edges[i] < x) {
                del(i, x);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (deleted.size() == n) continue;
            if (edges[i] != x) continue;
            if (v.find(i) != v.end() || deleted.find(i) != deleted.end()) continue;
            best = max(best, x * dfs(i));
        }
        v.clear();
        if (deleted.size() == n) break;
    }
    cout << best << endl;

}