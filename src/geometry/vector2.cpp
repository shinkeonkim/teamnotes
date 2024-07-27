const double EPSILON = 1e-10;
struct Vector2 {
  double x, y;
  Vector2() : x(0), y(0) {}
  Vector2(double x, double y) : x(x), y(y) {}
  Vector2(const Vector2 &other) : x(other.x), y(other.y) {}
  double norm() {
    return sqrt(x * x + y * y);
  }
  Vector2 normalized() {
    Vector2 result = *this / norm();
    return result;
  }
  double dot(Vector2 rhs) {
    return x * rhs.x + y * rhs.y;
  }
  double cross(Vector2 rhs) {
    return x * rhs.y - y * rhs.x;
  }
  Vector2 operator+(Vector2 rhs) {
    Vector2 result(x + rhs.x, y + rhs.y);
    return result;
  }
  Vector2 operator+=(Vector2 rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }
  Vector2 operator-(Vector2 rhs) {
    Vector2 result(x - rhs.x, y - rhs.y);
    return result;
  }
  Vector2 operator-=(Vector2 rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }
  Vector2 operator-() {
    Vector2 result(-x, -y);
    return result;
  }
  Vector2 operator*(double scalar) {
    Vector2 result(x * scalar, y * scalar);
    return result;
  }
  Vector2 operator/(double scalar) {
    Vector2 result(x / scalar, y / scalar);
    return result;
  }
  bool operator==(Vector2 rhs) {
    return x == rhs.x && y == rhs.y;
  }
  bool operator<(Vector2 rhs) {
    if (x == rhs.x) return y < rhs.y;
    return x < rhs.x;
  }
  bool operator<=(Vector2 rhs) {
    if (x == rhs.x)
      return y <= rhs.y;
    return x <= rhs.x;
  }
  bool operator>(Vector2 rhs) {
    return rhs < *this;
  }
  bool operator>=(Vector2 rhs) {
    return rhs <= *this;
  }
};
bool is_intersect(Vector2 a, Vector2 b, Vector2 c, Vector2 d) {
  double ret1 = (b - a).cross(c - a) * (b - a).cross(d - a);
  double ret2 = (d - c).cross(a - c) * (d - c).cross(b - c);
  if (ret1 == 0 && ret2 == 0) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return a <= d && c <= b;
  }
  return ret1 <= 0 && ret2 <= 0;
}
pair<bool, Vector2> get_intersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d) {
  if (a > b) swap(a, b);
  if (c > d) swap(c, d);
  if (a > c) {
    swap(a, c);
    swap(b, d);
  }
  if (!is_intersect(a, b, c, d)) return {false, Vector2(NAN, NAN)};
  Vector2 dir1 = (b - a).normalized();
  Vector2 dir2 = (d - c).normalized();
  double den = dir1.cross(dir2);
  if (-EPSILON <= den && den <= EPSILON) {
    if (b == c) return {true, b};
    return {true, Vector2(NAN, NAN)};
  }
  else {
    double l = (c - a).cross(dir1) / den;
    Vector2 intersection = c + dir2 * l;
    return {true, intersection};
  }
}
