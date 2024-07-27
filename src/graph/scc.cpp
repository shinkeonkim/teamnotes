struct SCC {
  // 1-index
  // run() 후에 components에 결과가 담김.

  ll V;
  llv2 edges, reversed_edges, components;
  vector<bool> visited;
  stack<ll> visit_log;

  SCC(ll V): V(V) {
    edges.resize(V + 1);
    reversed_edges.resize(V + 1);
  }

  void addEdge(int s, int e) {
    edges[s].push_back(e);
    reversed_edges[e].push_back(s);
  }

  void dfs(int node) {
    visited[node] = true;

    for (int next : edges[node])
      if (!visited[next]) dfs(next);
    visit_log.push(node);
  }
  void dfs2(int node) {
    visited[node] = true;
    for (int next:reversed_edges[node])
      if (!visited[next]) dfs2(next);
    components.back().push_back(node);
  }

  void run() {
    visited = vector<bool>(V + 1, false);
    for (int node = 1; node <= V; node++)
      if (!visited[node]) dfs(node);
    
    visited = vector<bool>(V + 1, false);
    while (!visit_log.empty()) {
      ll node = visit_log.top(); visit_log.pop();
      if (!visited[node]) {
        components.push_back(llv1());
        dfs2(node);
      }
    }
  }
};