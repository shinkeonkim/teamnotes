struct SuffixComparator {
  const vector<int> &group;
  int t;

  SuffixComparator(const vector<int> &_group, int _t) : group(_group), t(_t) {}
  bool operator()(int a, int b) {
    if (group[a] != group[b]) return group[a] < group[b];
    return group[a + t] < group[b + t];
  }
};

vector<int> getSuffixArr(const string &s) {
  int n = s.size();
  int t = 1;

  vector<int> group(n + 1);

  for (int i = 0; i < n; i++) group[i] = s[i];
  group[n] = -1;

  vector<int> perm(n);
  for (int i = 0; i < n; i++) perm[i] = i;

  while (t < n) {
    SuffixComparator compare(group, t);
    sort(perm.begin(), perm.end(), compare);
    t *= 2;
    if (t >= n)
      break;

    vector<int> new_group(n + 1);
    new_group[n] = -1;
    new_group[perm[0]] = 0;
    for (int i = 1; i < n; i++)
      if (compare(perm[i - 1], perm[i]))
        new_group[perm[i]] = new_group[perm[i - 1]] + 1;
      else
        new_group[perm[i]] = new_group[perm[i - 1]];
    group = new_group;
  }
  return perm;
}

int getHeight(const string &s, vector<int> &pos) {
   // 최장 중복 부분 문자열의 길이
  const int n = pos.size();
  vector<int> rank(n);
  for (int i = 0; i < n; i++)
    rank[pos[i]] = i;
  int h = 0, ret = 0;
  for (int i = 0; i < n; i++) {
    if (rank[i] > 0) {
      int j = pos[rank[i] - 1];
      while (s[i + h] == s[j + h])
        h++;
      ret = max(ret, h);
      if (h > 0)
        h--;
    }
  }
  return ret;
}