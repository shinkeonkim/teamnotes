ll N, maxWeight, ans;
ll D[2][11000];
ll weight[110], cost[110];
void knapsack() {
  for (int x = 1; x <= N; x++) {
    for (int y = 0; y <= maxWeight; y++) {
      if (y >= weight[x]) {
        D[x % 2][y] = max(D[(x + 1) % 2][y], D[(x + 1) % 2][y - weight[x]] + cost[x]);
      } else {
        D[x % 2][y] = D[(x + 1) % 2][y];
      }
      ans = max(ans, D[x % 2][y]);
    }
  }
}
void input() {
  cin >> N >> maxWeight;
  for (int x = 1; x <= N; x++) {
    cin >> weight[x] >> cost[x];
  }
}
