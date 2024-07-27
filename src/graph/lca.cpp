#define MAX_DEGREE 20

struct LCA {
  // root: 트리의 루트 설정, n: 트리의 노드 개수
  // addEdge -> init -> query(O(log(n))

  ll root, n;
  llv1 depth;
  llv2 adj;
  llv2 parent; // n X MAX_DEGREE

  LCA(ll root, ll n) : root(root), n(n) {
    depth.resize(n + 1);
    adj.resize(n + 1);
    parent.resize(n + 1, llv1(MAX_DEGREE, 0));
  }

  void addEdge(ll a, ll b) {
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  void init() {
    dfs(root, 0, 1);

    for(int i = 1; i < MAX_DEGREE; i++) {
      for(int j = 1; j <= n; j++) {
        parent[j][i] = parent[parent[j][i-1]][i-1];
      }
    }
  }

  void dfs(int here, int par, int d) {
    depth[here] = d;
    parent[here][0] = par;

    for(int there : adj[here]) {
      if(depth[there] > 0) continue;

      dfs(there, here, d + 1);
    }
  }

  int query(int a, int b) {
    if(depth[a] > depth[b]) {
      swap(a, b);
    }

    for(int i = MAX_DEGREE - 1; i >= 0; i--) {
      if (depth[b] - depth[a] >= (1 << i)) {
        b = parent[b][i];
      }
    }

    if(a == b) {
      return a;
    }

    for(int i = MAX_DEGREE - 1; i >= 0; i--) {
      if(parent[a][i] != parent[b][i]) {
        a = parent[a][i];
        b = parent[b][i];
      }
    }

    return parent[a][0];
  }
};