pair<double, double> get_projection(vector<Vector2> &points, Vector2 &axis) {
  double min_val = axis.dot(points[0]);
  double max_val = min_val;
  for (int i = 1; i < points.size(); i++) {
    double projected = axis.dot(points[i]);
    min_val = min(min_val, projected);
    max_val = max(max_val, projected);
  }
  return {min_val, max_val};
}

vector<Vector2> get_normals(vector<Vector2> &points) {
  vector<Vector2> ret;
  if (points.size() == 1)
    return ret;
  for (int i = 0; i < points.size(); i++) {
    Vector2 &a = points[i];
    Vector2 &b = points[(i + 1) % points.size()];
    ret.push_back(Vector2((b - a).y, -(b - a).x));
  }
  return ret;
}
bool can_separate(vector<Vector2> &A, vector<Vector2> &B) {
  if (A.size() == 1 && B.size() == 1)
    return true;
  auto c_a = get_convex_hull(A);
  auto c_b = get_convex_hull(B);
  auto n_a = get_normals(c_a);
  auto n_b = get_normals(c_b);

  n_a.insert(n_a.end(), n_b.begin(), n_b.end());
  if (c_a.size() > 1) n_a.push_back(Vector2(c_a[1] - c_a[0]));
  if (c_b.size() > 1) n_a.push_back(Vector2(c_b[1] - c_b[0]));

  for (Vector2 &axis : n_a) {
    auto p_a = get_projection(c_a, axis);
    auto p_b = get_projection(c_b, axis);
    if (!((p_a.second >= p_b.first) && (p_b.second >= p_a.first))) return true;
  }
  return false;
}