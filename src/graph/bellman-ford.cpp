struct BellmanFord {
  struct BellmanEdge {
    ll to, cost;

    BellmanEdge(ll to, ll cost) : to(to), cost(cost) {}
  };

  ll N;
  vector<vector <BellmanEdge> > adj;
  llv1 D;
  vector<ll> prev;

  BellmanFord(ll N) : N(N) {
    adj.resize(N + 1);
  }

  void addEdge(ll s, ll e, ll cost) {
    adj[s].push_back(BellmanEdge(e, cost));
  }

  bool run(ll start_point) {
    // 음수 간선 cycle 유무를 반환합니다.
    // 거리 정보는 D 벡터에 저장됩니다.
    // O(V * E)

    D.resize(N + 1, INF);
    prev.resize(N + 1, -1);
    D[start_point] = 0;
  
    bool isCycle = false;

    for1(1, N + 1) {
      for1j(1, N + 1) {
        for(int k=0; k < sz(adj[j]); k++) {
          BellmanEdge p = adj[j][k];
          int end = p.to;
          ll dist = D[j] + p.cost;

          if (D[j] != INF && D[end] > dist) {
            D[end] = dist;
            if (i == N) isCycle = true;
          }
        }
      }
    }
    return isCycle;
  }

  llv1 getPath(ll s, ll e) {
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
