#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, sz;

    DSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);

        for (int i = 1; i <= n; i++)
            parent[i] = i;
    }

    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) return false;

        if (sz[a] < sz[b]) swap(a, b);

        parent[b] = a;
        sz[a] += sz[b];

        return true;
    }
};

struct Edge {
    int u, v, c;
};

int n, m;
vector<vector<pair<int,int>>> tree;
vector<long long> bitCnt;
vector<int> subSize;

int dfs(int u, int p) {
    subSize[u] = 1;

    for (auto &[v, cost] : tree[u]) {
        if (v == p) continue;

        int child = dfs(v, u);

        long long pairs = 1LL * child * (n - child);

        bitCnt[cost] += pairs;

        subSize[u] += child;
    }

    return subSize[u];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    vector<Edge> edges(m);

    int maxC = 0;

    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].c;
        maxC = max(maxC, edges[i].c);
    }

    sort(edges.begin(), edges.end(),
         [](const Edge &a, const Edge &b) {
             return a.c < b.c;
         });

    DSU dsu(n);

    tree.assign(n + 1, {});

    for (auto &e : edges) {
        if (dsu.unite(e.u, e.v)) {
            tree[e.u].push_back({e.v, e.c});
            tree[e.v].push_back({e.u, e.c});
        }
    }

    bitCnt.assign(maxC + 300000, 0);
    subSize.assign(n + 1, 0);

    dfs(1, -1);

    for (size_t i = 0; i + 1 < bitCnt.size(); i++) {
        bitCnt[i + 1] += bitCnt[i] / 2;
        bitCnt[i] %= 2;
    }

    int last = (int)bitCnt.size() - 1;

    while (last > 0 && bitCnt[last] == 0)
        last--;

    string ans;

    for (int i = last; i >= 0; i--)
        ans.push_back(char('0' + bitCnt[i]));

    cout << ans << '\n';

    return 0;
}
