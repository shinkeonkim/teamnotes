struct UnionFind {
  int n;
  vector<int> u;

  UnionFind(int n) : n(n) {
    u.resize(n + 1);
    for(int i = 1; i <= n; i++) {
      u[i] = i;
    }
  }

  int find(int k) {
    if(u[u[k]] == u[k]) return u[k];
    else return u[k]=find(u[k]);
  }

  void uni(int a, int b) {
    a = find(a);
    b = find(b);
    if(a < b) u[b] = a;
    else u[a] = b; 
  }
};
