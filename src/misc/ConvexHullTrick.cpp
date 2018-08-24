// @import header
// @@
// @type one
// @name Convex Hull Trick Library
// @snippet     cht
// @alias       convexhulltrick
// CHT(bool increasing, Compare comp);
// increasing : is query monotonic-increasing ?
// comp : rhs is better
// add(tuple<T, T> line) : add deacrinsgly!!
/// --- Convex Hull Trick Library {{{ ///

struct CHT {
  vector< tuple<ll, ll> > lines;
  bool increasing;
  function<bool(ll, ll)> comp;
  CHT(bool increasing = false, function<bool(ll, ll)> comp =
      [&] (ll lhs, ll rhs) { return lhs >= rhs; }):
    increasing(increasing), comp(comp) {}
  // is l2 unnecessary ?
  bool check(tuple<ll, ll> l1, tuple<ll, ll> l2, tuple<ll, ll> l3) {
    return comp((se(l1) - se(l2)) * (fi(l3) - fi(l2)), (se(l3) - se(l2)) * (fi(l1) - fi(l2)));
  }
  ll f(int i, ll x) {
    return fi(lines[i]) * x + se(lines[i]);
  }
  // add decrasingly
  void add(ll a, ll b) {
    add(P(a, b));
  }
  void add(tuple<ll, ll> line) {
    while((int) lines.size() >= 2 &&
        check(lines[lines.size()-2], lines.back(), line))
      lines.pop_back();
    lines.emplace_back(line);
  }
  ll query(ll x) {
    if(increasing) {
      static int head = 0;
      while((int) lines.size() - 1 > head &&
          comp(f(head, x), f(head + 1, x)))
        head++;
      return f(head, x);
    } else {
      int low = -1, high = lines.size() - 1;
      while(high - low > 1) {
        int mid = (low + high) >> 1;
        (comp(f(mid, x), f(mid + 1, x)) ? low : high) = mid;
      }
      return f(high, x);
    }
  }
};

/// }}}--- ///

// @new
// @name Dynamic Convex Hull Trick Library
// @snippet     dynamic_cht
// @alias       cht2
/// --- Dynamic Convex Hull Trick Library {{{ ///

struct DynamicCHT {
  DynamicCHT() {
    // sentinel
    S.insert({L(INF,0), L(-INF,0)});
    C.insert(cp(L(INF,0),L(-INF,0)));
  }
  // for debug
  void print() {
#ifdef DEBUG
    cerr << "S : "; for (auto it : S) cerr << "(" << it.a << "," << it.b<< ")" << endl;
    cerr << "C : "; for (auto it : C) cerr << "(" << it.n << "," << it.d<< ")" << endl;
#endif
  }
  // |ab| < LLONG_MAX/4 ???
  void add(ll a, ll b) {
    const L p(a,b);
    It pos = S.insert(p).first;
    if (check(*it_m1(pos), p, *it_p1(pos))) {
      // 直線(a,b)が不要
      S.erase(pos);
      return;
    }
    C.erase(cp(*it_m1(pos), *it_p1(pos)));
    {
      // 右方向の削除
      It it = it_m1(pos);
      while(it!=S.begin() && check(*it_m1(it), *it, p)) --it;
      C_erase(it, it_m1(pos));
      S.erase(++it,pos);
      pos = S.find(p);
    }
    {
      // 左方向の削除
      It it = it_p1(pos);
      while(it_p1(it)!=S.end() && check(p,*it, *it_p1(it))) ++it;
      C_erase(++pos, it);
      S.erase(pos, it);
      pos = S.find(p);
    }
    C.insert(cp(*it_m1(pos), *pos));
    C.insert(cp(*pos, *it_p1(pos)));
  }
  ll query(ll x) {
    const L &p = (--C.lower_bound(CP(x,1,L(0,0))))->p;
    return p.a*x + p.b;
  }
private:
  template<class T> T it_p1(T a) { return ++a; }
  template<class T> T it_m1(T a) { return --a; }  
  struct L {
    ll a, b;
    L(ll a, ll b) : a(a),b(b) {}
    bool operator<(const L &rhs) const {
      return a != rhs.a ? a > rhs.a : b < rhs.b;
    }
  };
  struct CP {
    ll n,d;
    L p;
    CP(ll _n, ll _d, const L &p) : n(_n),d(_d),p(p) {
      if (d < 0) { n *= -1; d *= -1; }
    };
    bool operator<(const CP &rhs) const {
      if (n == INF || rhs.n == -INF) return 0;
      if (n == -INF || rhs.n == INF) return 1;      
      return n * rhs.d < rhs.n * d;
    }
  };
  set<L> S;
  set<CP> C;

  typedef set<L>::iterator It;
  
  void C_erase(It a, It b) {
    for (It it=a; it!=b; ++it)
      C.erase(cp(*it, *it_p1(it)));
  }
  CP cp(const L &p1, const L &p2) {
    if (p1.a == INF) return CP(-INF,1,p2);
    if (p2.a == -INF) return CP(INF,1,p2);
    return CP(p1.b-p2.b, p2.a-p1.a, p2);
  }
  bool check(const L &p1, const L &p2, const L &p3) {
    if (p1.a==p2.a && p1.b <= p2.b) return 1;
    if (p1.a == INF || p3.a == -INF) return 0;
    return (p2.a-p1.a)*(p3.b-p2.b) >= (p2.b-p1.b)*(p3.a-p2.a);
  }
};

/// }}}--- ///
