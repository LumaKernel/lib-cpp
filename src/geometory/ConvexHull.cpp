// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet     grahamscan
// @alias       scan andrew convexhull
// @ Graham Scan Library

// require Geometory Library
/// --- Graham Scan Library {{{ ///

// make ConvexHull

// if there are 3 points on line,
// just guaranteed that point on hull is scanned exactly;
// if on Line of Hull, sometimes scanned as on Hull.
struct GrahamScan {
  Polygon poly;
  vector< size_t > ids;
  vector< size_t > hull;

  void add(Point p) { poly.emplace_back(p); }

  int operator[](int i) { return hull[(i % hull.size() + hull.size()) % hull.size()]; }

  void scan() {
    ids.resize(poly.size());
    iota(begin(ids), end(ids), 0);

    size_t startID = 0;
    for(size_t i = 1; i < poly.size(); i++) {
      if(make_pair(poly[startID].real(), poly[startID].imag()) >
         make_pair(poly[i].real(), poly[i].imag()))
        startID = i;
    }
    swap(ids[0], ids[startID]);

    sort(begin(ids) + 1, end(ids), [&](int a, int b) {
      Point p1 = poly[a] - poly[ids[0]];
      Point p2 = poly[b] - poly[ids[0]];
      // p1.y / p1.x < p2.y / p2.x
      double ev = p1.imag() * p2.real() - p2.imag() * p1.real();
      return abs(ev) < EPS ? norm(p1) < norm(p2) : ev < 0;
    });

    hull.emplace_back(ids[0]);
    for(size_t i = 1; i <= poly.size(); i++) {
      size_t ii = i % poly.size();
      while(hull.size() >= 2 &&
            ccw(poly[hull[hull.size() - 2]], poly[hull[hull.size() - 1]],
                poly[ids[ii]]) == -1)
        hull.pop_back();
      hull.emplace_back(ids[ii]);
    }

    hull.pop_back();
  }
};

/// }}}--- ///
