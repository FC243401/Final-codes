#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, rankv;

    DSU(int n) {
        parent.resize(n + 1);
        rankv.resize(n + 1, 0);

        for(int i = 1; i <= n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if(parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if(a == b)
            return false;

        if(rankv[a] < rankv[b])
            swap(a, b);

        parent[b] = a;

        if(rankv[a] == rankv[b])
            rankv[a]++;

        return true;
    }
};

int kruskals(int g_nodes,
             vector<int> g_from,
             vector<int> g_to,
             vector<int> g_weight) {

    vector<tuple<int,int,int>> edges;

    for(int i = 0; i < g_weight.size(); i++) {
        edges.push_back({
            g_weight[i],
            min(g_from[i], g_to[i]),
            max(g_from[i], g_to[i])
        });
    }

    sort(edges.begin(), edges.end());

    DSU dsu(g_nodes);

    int mstWeight = 0;

    for(auto &[w,u,v] : edges) {
        if(dsu.unite(u,v))
            mstWeight += w;
    }

    return mstWeight;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> from(m), to(m), weight(m);

    for(int i = 0; i < m; i++) {
        cin >> from[i] >> to[i] >> weight[i];
    }

    cout << kruskals(n, from, to, weight);

    return 0;
}
