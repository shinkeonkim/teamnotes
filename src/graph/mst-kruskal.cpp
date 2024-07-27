template <class T>  struct MinimumSpanningTree {
  /*
    T: 가중치의 타입

    n: 노드 개수
    m: 간선 개수
    result : MST 결과 (가중치 합)
  */ 
  struct Edge { 
    int u, v;
    T weight;

    Edge(int u, int v, T weight) : u(u), v(v), weight(weight) {}
    bool operator< (Edge other) const { return weight < other.weight; }
  };

  int n, m;
  vector<int> uf;
  vector<Edge> edges;
  vector<Edge> chosen_edges;

  T result; // MST의 가중치 합
  int cnt; // 뽑은 간선 수

  MinimumSpanningTree(int n, int m) : n(n), m(m) {
    uf.resize(n + 1);
  
    for1(0, n + 1) {
      uf[i] = i;
    }
    result = 0;
    cnt = 0;
  }

  int find(int a) {
    /*
      Union-Find: Find 연산
    */
    if(uf[a] == a) return a;
    return uf[a] = find(uf[a]);
  }

  int merge(int a, int b) {
    /*
      Union-Find: Union
      합쳐진 경우 true 반환
    */

    a = find(a);
    b = find(b);

    if(a == b) return false;

    uf[b] = a;
    return true;
  }

  void add_edge(int u, int v, T cost) {
    edges.push_back(Edge(u, v, cost));
  }

  void run() {
    sort(edges.begin(), edges.end());

    for(int i = 0; i < edges.size(); i++) {
      if(merge(edges[i].u,  edges[i].v)) {
        result += edges[i].weight;

        // chosen_edges.push_back(edges[i]);
        if(++cnt >= n - 1) break;
      }
    }
  }
};
