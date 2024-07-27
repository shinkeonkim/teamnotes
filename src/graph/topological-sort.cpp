struct TopologicalSort {
  // 1-index

  int n;
  iv1 in_degree;
  iv2 graph;
  iv1 result;

  TopologicalSort(int n) : n(n) {
    in_degree.resize(n + 1, 0);
    graph.resize(n + 1);
  }

  void addEdge(int s, int e) {
    graph[s].push_back(e);
    in_degree[e]++;
  }

  void run() {
    queue<int> q;

    for1(1, n+1) {
      if(in_degree[i] == 0) q.push(i);
    }
    while(!q.empty()) {
      int here = q.front(); q.pop();
      result.push_back(here);

      for1(0, sz(graph[here])) {
        int there = graph[here][i];

        if(--in_degree[there]==0) q.push(there);
      }
    }
  }
};
