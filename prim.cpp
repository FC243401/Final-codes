
#include <bits/stdc++.h>
using namespace std;

int prims(int n, vector<vector<int>> edges, int start) {
    vector<pair<int,int>> adj[n + 1];

    for(auto &e : edges) {
        int u = e[0];
        int v = e[1];
        int w = e[2];

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<bool> visited(n + 1, false);

    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;

    pq.push({0, start});

    int mstWeight = 0;

    while(!pq.empty()) {
        auto [weight, node] = pq.top();
        pq.pop();

        if(visited[node])
            continue;

        visited[node] = true;
        mstWeight += weight;

        for(auto &[next, w] : adj[node]) {
            if(!visited[next]) {
                pq.push({w, next});
            }
        }
    }

    return mstWeight;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> edges;

    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        edges.push_back({u, v, w});
    }

    int start;
    cin >> start;

    cout << prims(n, edges, start);

    return 0;
}
