struct Point {
  int x, y;
  bool operator==(const Point &other) const {
    return x == other.x && y == other.y; 
  }
  int Quad() const {
    if (x >= 0 && y >= 0) return 1;
    if (x <  0 && y >= 0) return 2;
    if (x <  0 && y <  0) return 3;
                          return 4;
  }
  bool operator<(const Point &other) const {
    if (Quad() != other.Quad()) return Quad() < other.Quad();
    return Cross(other) > 0; 
  }
  long long Cross(const Point &other) const {
    return x * (other.y) - other.x * y;
  }
};
