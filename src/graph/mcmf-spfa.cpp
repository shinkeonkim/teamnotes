struct MCMF {
  struct Edge {
    ll to;
    ll capacity;
    ll cost;
    
    Edge* rev;
    Edge(ll to, ll capacity, ll cost) : to(to), capacity(capacity), cost(cost) {}
  };
  
  ll n;
  ll source, sink;
  vector<vector<Edge *>> graph;
  vector<bool> check;
  vector<ll> distance;
  vector<pair<ll, ll>> from;
  
  MCMF(ll n, ll source, ll sink): n(n), source(source), sink(sink) {

    // source: 시작점
    // sink: 도착점
    // n: 모델링한 그래프의 정점 개수
    graph.resize(n + 1);
    check.resize(n + 1);
    from.resize(n + 1, make_pair(-1, -1));
    distance.resize(n + 1);
  };
  
  void addEdge(ll u, ll v, ll cap, ll cost) {
    Edge *ori = new Edge(v, cap, cost);
    Edge *rev = new Edge(u, 0, -cost);
    
    ori->rev = rev;
    rev->rev = ori;
    
    graph[u].push_back(ori);
    graph[v].push_back(rev);
  }
  
  void addEdgeFromSrc(ll v, ll cap, ll cost) {
    // 출발지점에서 출발하는 간선 추가
    addEdge(source, v, cap, cost);
  }
  
  void addEdgeToSink(ll u, ll cap, ll cost) {
    // 도착지점으로 가는 간선 추가
    addEdge(u, sink, cap, cost);
  }
  
  bool spfa(ll &total_flow, ll &total_cost) {
    // spfa 기반의 MCMF

    fill(check.begin(), check.end(), false);
    fill(distance.begin(), distance.end(), INF);
    fill(from.begin(), from.end(), make_pair(-1, -1));
    
    distance[source] = 0;
    queue <ll> q;
    q.push(source);
    
    while(!q.empty()) {
      ll x = q.front(); q.pop();
      
      check[x] = false;
      
      for(ll i = 0; i < graph[x].size(); i++) {
        Edge* e = graph[x][i];
        ll y = e->to;
        
        if(e->capacity > 0 && distance[x] + e->cost < distance[y]) {
          distance[y] = distance[x] + e->cost;
          from[y] = make_pair(x, i);
          
          if(!check[y]) {
            check[y] = true;
            q.push(y);
          }
        }
        
      }
    }
    
    if(distance[sink] == INF) return false;
    
    // 간선을 sink에서부터 역추적하여 경로를 만든다.
    ll x = sink;
    ll c = graph[from[x].first][from[x].second]->capacity;
    
    while(from[x].first != -1) {
      if(c > graph[from[x].first][from[x].second]->capacity) {
        c = graph[from[x].first][from[x].second]->capacity;
      }
      x = from[x].first;
    }

    // 만든 경로를 따라 유량을 흘린다.
    x = sink;
    while(from[x].first != -1) {
      Edge* e = graph[from[x].first][from[x].second];
      e->capacity -= c;
      e->rev->capacity += c;
      x = from[x].first;
    }
    
    total_flow += c;
    total_cost += c * distance[sink];
    
    return true;
  }
  
  pair <ll, ll> flow() {
    ll total_flow = 0;
    ll total_cost = 0;
    
    while(spfa(total_flow, total_cost));
    
    return make_pair(total_flow, total_cost);
  }
};
