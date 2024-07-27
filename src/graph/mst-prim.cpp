struct edge {
  ll crt;
  ll node, cost;
};
struct WGraph {
  ll V; 
  vector<edge> adj[MAX];
  vector<ll> prev;
  WGraph(ll V) : V{V} {}
  void addEdge(ll s, ll e, ll cost) {
    adj[s].push_back({s, e, cost});
    adj[e].push_back({e, s, cost});
  }
  
  ll prim(vector<edge> &selected) { // selected에 선택된 간선정보 vector 담김
    selected.clear();
  
    vector<bool> added(V, false);
    llv1 minWeight(V, INF), parent(V, -1);
  
    ll ret = 0;
    minWeight[0] = parent[0] = 0;
    for (int iter = 0; iter < V; iter++) {
      int u = -1;
      for (int v = 0; v < V; v++) {
        if (!added[v] && (u == -1 || minWeight[u]>minWeight[v]))
          u = v;
      }
  
      if (parent[u] != u)
        selected.push_back({parent[u], u, minWeight[u]});
  
      ret += minWeight[u];
      added[u] = true;

      for1(0, sz(adj[u])) {
        int v = adj[u][i].node, weight = adj[u][i].cost;
        if (!added[v] && minWeight[v]>weight) {
          parent[v] = u;
          minWeight[v] = weight;
        }
      }
    }
    return ret;
  }
};
