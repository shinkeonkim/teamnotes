int dist(Point &p, Point &q) {
  return (p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y);
}
struct Comp {
  bool comp_in_x;
  Comp(bool b) : comp_in_x(b) {}
  bool operator()(Point &p, Point &q) {
    return (this->comp_in_x ? p.x < q.x : p.y < q.y);
  }
};
int nearest(vector<Point>::iterator it, int n) {
  if (n == 2) return dist(it[0], it[1]);
  if (n == 3) return min({dist(it[0], it[1]), dist(it[1], it[2]), dist(it[2], it[0])});
  int line = (it[n / 2 - 1].x + it[n / 2].x) / 2;
  int d = min(nearest(it, n / 2), nearest(it + n / 2, n - n / 2));
  vector<Point> mid;
  for (int i = 0; i < n; i++) {
    int t = line - it[i].x;
    if (t * t < d) mid.push_back(it[i]);
  }
  sort(mid.begin(), mid.end(), Comp(false));
  int mid_sz = mid.size();
  for (int i = 0; i < mid_sz - 1; i++)
    for (int j = i + 1; j < mid_sz && (mid[j].y - mid[i].y) * (mid[j].y - mid[i].y) < d; j++)
      d = min(d, dist(mid[i], mid[j]));
  return d;
}