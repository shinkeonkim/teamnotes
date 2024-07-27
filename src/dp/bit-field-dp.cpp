#define MOD 9901;
int dp[1 << 14 + 1][200];
int n, m;
int solve(int pos, int check, int dep) {
  if (dp[check][pos] != 0) return dp[check][pos];
  int &ret = dp[check][pos];
  if (dep == n * m) return ret = 1;
  if ((check & 1)) return ret = solve(pos - 1, check >> 1, dep) % MOD;
  int sum = 0;
  if (!(check & 1) && (pos - 1) / m > 0)
    sum += solve(pos - 1, (check >> 1) | (1 << (m - 1)), dep + 2) % MOD;
  if (!(check & 1) && pos % m != 1 && !(check & 2) && pos >= 2 && m > 1)
    sum += solve(pos - 2, check >> 2, dep + 2) % MOD;
  return ret = sum % MOD;
}
int main() {
  cin >> n >> m;
  if (n * m % 2 == 1)
    cout << 0;
  else
    cout << solve(n * m, 0, 0) % MOD;
}
