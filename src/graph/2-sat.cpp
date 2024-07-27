struct Graph {
  int V;
  vector<bool> visited;
  stack<int> visit_stack;
  vector<int> component_number, source_components;
  vector<vector<int>> edges, reversed_edges, components, components_edges;

  Graph(int V) : V(V) {
    edges.resize(V);
    reversed_edges.resize(V);
  }
  void append(int u, int v) {
    edges[u].push_back(v);
    reversed_edges[v].push_back(u);
  }
  void dfs(int node) {
    visited[node] = true;
    for (int next : edges[node])
      if (!visited[next])
        dfs(next);
    visit_stack.push(node);
  }
  void scc(int node) {
    visited[node] = true;
    for (int next : reversed_edges[node])
      if (!visited[next])
        scc(next);
    components.back().push_back(node);
  }
  void build_scc() {
    visited = vector<bool>(V, false);
    for (int node = 0; node < V; node++)
      if (!visited[node]) dfs(node);
    visited = vector<bool>(V, false);
    while (!visit_stack.empty()) {
      int node = visit_stack.top();
      visit_stack.pop();
      if (!visited[node]) {
        components.push_back(vector<int>());
        scc(node);
      }
    }
    component_number.resize(V);
    for (int i = 0; i < components.size(); i++)
      for (int node : components[i]) component_number[node] = i;
    vector<bool> is_source = vector<bool>(components.size(), true);
    components_edges.resize(components.size());
    for (int u = 0; u < V; u++)
      for (int v : edges[u]) {
        int cu = component_number[u];
        int cv = component_number[v];
        if (cu == cv) continue;
        components_edges[cu].push_back(cv);
        is_source[cv] = false;
      }
    for (int component = 0; component < components.size(); component++) {
      if (is_source[component]) source_components.push_back(component);
    }
  }
};

int main(void) {
  int V, E;
  cin >> V >> E;
  Graph graph(2 * V + 1);
  for (int i = 0; i < E; i++) {
    int u, v;
    cin >> u >> v;
    graph.append(-u + V, v + V);
    graph.append(-v + V, u + V);
  }
  graph.build_scc();
  vector<int> last_component(2 * V + 1, -1);
  bool is_answer = true;
  for (int i = 0; i < graph.components.size(); i++) {
    for (int node : graph.components[i]) {
      int negation = -(node - V) + V;
      if (last_component[negation] == i) is_answer = false;
      last_component[node] = i;
    }
  }
  if (is_answer) {
    vector<int> result(V);
    for (int i = 1; i <= V; i++) {
      int val = i + V;
      int negation = -i + V;
      result[i - 1] = graph.component_number[val] > graph.component_number[negation];
    }
    for (int val : result) cout << val << " ";
    cout << "\n";
  }
}