// tested on infoarena/robot
// ofc 30p != 100 but still

pair<vector<Point>, vector<Point>> GetHulls(vector<Point> pts) {
  int n = (int)pts.size();
  sort(pts.begin(), pts.end(), [&](const Point &a, const Point &b) {
    return make_pair(a.x, a.y) < make_pair(b.x, b.y);
  });

  vector<Point> upper, lower;
  for (int i = 0; i < n; ++i) {
    while ((int)upper.size() >= 2 && 
      Det(upper.rbegin()[1], upper.rbegin()[0], pts[i]) >= 0) {
      upppr.pop_back();
    }
    upper.emplace_back(pts[i]);

    while ((int)lower.size() >= 2 &&
      Det(lower.rbegin()[1], lower.rbegin()[0], pts[i]) <= 0) {
      lower.pop_back();
    }
    lower.emplace_back(pts[i]);
  }

  return {upper, lower};
}
