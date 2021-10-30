class ConvexHullTrick {
  struct Line {
    long long m, b, value;
    double xlo;
    bool is_query, query_max;

    Line (long long m, long long b, long long v, bool is_query, bool query_max)
      : m(m), b(b), value(v), xlo(-std::numeric_limits<double>::max()),
        is_query(is_query), query_max(query_max) {}

    double intersect (const line &l) const {
      if (m == l.m) {
        return std::numeric_limits<double>::max();
      }

      return (double)(l.b - b)/(m - l.m);
    }

    bool operator < (const line &l) const {
      if (l.is_query) {
        return query_max ? (xlo < l.value) : (l.value < xlo);
      }

      return m < l.m;
    }
  };

  set <Line> hull;
  bool query_max;

  typedef set<Line>::iterator hulliter;

  bool hasPrev (hulliter it) const {
    return it != hull.begin();
  }

  bool hasNext (hulliter it) const {
    return (it != hull.end()) && (++it != hull.end());
  }

  bool isIrrelevant (hulliter it) const {
    if (!hasPrev (it) || !hasNext (it)) {
      return false;
    }

    hulliter prev = it, next = it;
    --prev;
    ++next;
    return query_max ? (prev->intersect (*next) <= prev->intersect (*it))
           : (next->intersect (*prev) <= next->intersect (*it));
  }

  hulliter updateLeftBorder (hulliter it) {
    if ((query_max && !has_prev (it)) || (!query_max && !has_next (it))) {
      return it;
    }

    hulliter it2 = it;
    double value = it->intersect (query_max ? *--it2 : *++it2);
    line l (*it);
    l.xlo = value;
    hull.erase (it++);
    return hull.insert (it, l);
  }

public:
  ConvexHullTrick (bool query_max = false) : query_max (query_max) {}

  void addLine (long long m, long long b) {
    Line l (m, b, 0, false, query_max);
    hulliter it = hull.lower_bound (l);

    if (it != hull.end() && it->m == l.m) {
      if ((query_max && it->b < b) || (!query_max && b < it->b)) {
        hull.erase (it++);
      } else {
        return;
      }
    }

    it = hull.insert (it, l);

    if (isIrrelevant (it)) {
      hull.erase (it);
      return;
    }

    while (hasPrev (it) && isIrrelevant (--it)) {
      hull.erase (it++);
    }

    while (hasNext (it) && isIrrelevant (++it)) {
      hull.erase (it--);
    }

    it = updateLeftBorder (it);

    if (hasPrev (it)) {
      updateLeftBorder (--it);
    }

    if (hasNext (++it)) {
      updateLeftBorder (++it);
    }
  }

  long long query (long long x) const {
    line q (0, 0, x, true, query_max);
    hulliter it = hull.lower_bound (q);

    if (query_max) {
      --it;
    }

    return it->m * x + it->b;
  }
};
