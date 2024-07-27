struct FloydWarshall{
  ll N;
  llv2 ar;

  FloydWarshall(ll N) : N(N) {
    ar.resize(N + 1, llv1(N + 1, INF));

    for1(1, N + 1) ar[i][i] = 0; 
  }

  void addEdge(ll a, ll b, ll cost) {
    ar[a][b] = min(ar[a][b], cost);
    ar[b][a] = min(ar[b][a], cost);
  }

  void run() {
    for(int k = 1; k <= N; k++) {
      for(int i =  1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
          if(ar[i][j] > ar[i][k] + ar[k][j]) {
            ar[i][j] = ar[i][k] + ar[k][j];
          }
        }
      }
    }
  }
};
