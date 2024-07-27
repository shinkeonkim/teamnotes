pair<Vector2, Vector2> get_max_points(vector<Vector2> &points) {
  int left = 0, right = max_element(points.begin(), points.end()) - points.begin();
  int ret1 = left, ret2 = right;
  double max_len = (points[right] - points[left]).norm();
  int end = right;
  Vector2 left_dir = Vector2(0, -1.0);
  vector<Vector2> edges;
  for (int i = 0; i < points.size(); i++)
    edges.push_back((points[(i + 1) % points.size()] - points[i]).normalized());
  while (right != 0 || left != end) {
    double next1 = left_dir.dot(edges[left]);
    double next2 = -left_dir.dot(edges[right]);
    if (left != end && (right == 0 || next1 > next2)) {
      left_dir = edges[left];
      left = (left + 1) % points.size();
    } else {
      left_dir = -edges[right];
      right = (right + 1) % points.size();
    }
    double len = (points[right] - points[left]).norm();
    if (len > max_len) {
      ret1 = left;
      ret2 = right;
      max_len = len;
    }
  }
  return {points[ret1], points[ret2]};
}
