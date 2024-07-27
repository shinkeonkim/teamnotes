template<typename T> struct Dijkstra {
  /*
    T: 간선 가중치 타입
  */
  struct Edge {
    ll node;
    T cost;
    bool operator<(const Edge &to) const {
      return cost > to.cost;
    }
  };

  ll n; 
  vector<vector<Edge>> adj;
  vector<ll> prev;

  Dijkstra(ll n) : n{n}, adj(n+1) {}

  void addEdge(ll s, ll e, T cost) {
    adj[s].push_back(Edge(e, cost));
  }

  void addUndirectedEdge(ll s, ll e, T cost) {
    addEdge(s, e, cost);
    addEdge(e, s, cost);
  }

  vector <ll> dijkstra(ll s) {
    vector <ll> dist(n+1, INF);
    prev.resize(n+1, -1);
    priority_queue<edge> pq;
    pq.push({ s, 0ll });
    dist[s] = 0;
    while (!pq.empty()) {
      edge cur = pq.top();
      pq.pop();
      if (cur.cost > dist[cur.node]) continue;
      for (auto &nxt : adj[cur.node])
        if (dist[cur.node] + nxt.cost < dist[nxt.node]) {
          prev[nxt.node] = cur.node;
          dist[nxt.node] = dist[cur.node] + nxt.cost;
          pq.push({ nxt.node, dist[nxt.node] });
        }
    }
    return dist;
  }

  vector<ll> getPath(ll s, ll e) {
    vector<ll> ret;
    ll current = e;
    while(current != -1) {
      ret.push_back(current);
      current = prev[current];
    }
    reverse(ret.begin(), ret.end());
    return ret;
  }
};