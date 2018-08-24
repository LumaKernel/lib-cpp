// @import header
// @@
// @name SegmentTree Library
// @snippet     segmenttree
// @ SegmentTree Library
// @alias       seg
// NOTE : query in range!
/// --- SegmentTree Library {{{ ///

// struct Monoid {
//   using T = _underlying_set_;
//   static T op(const T& a, const T& b) { return _a_op_b_; }
//   static constexpr T identity() { return _identity_element_; }
// };

template<class Monoid>
struct SegTree {
private:
  using T = typename Monoid::T;
  int n;
  std::vector<T> data;
  // call after touch data[i]
  void prop(int i) { data[i] = Monoid::op(data[2 * i], data[2 * i + 1]); }
public:
  SegTree(): n(0) {}
  SegTree(int n): n(n) {
    data.resize(n * 2, Monoid::identity());
  }
  template<class InputIter, class = typename std::iterator_traits<InputIter>::value_type>
    SegTree(InputIter first, InputIter last)
    : SegTree(std::distance(first, last)) {
      copy(first, last, std::begin(data) + n);
      // fill from deep
      for(int i = n - 1; i > 0; i--) prop(i);
    }
  void set(int i, const T& v) {
    data[i += n] = v;
    while(i >>= 1) prop(i); // propUp
  }
  T get(int i) { return data[i + n]; }
  T query(int l, int r) {
    T tmpL = Monoid::identity(), tmpR = Monoid::identity();
    for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if(l & 1) tmpL = Monoid::op(tmpL, data[l++]);
      if(r & 1) tmpR = Monoid::op(data[--r], tmpR);
    }
    return Monoid::op(tmpL, tmpR);
  }
  inline void dum(int r = -1) {
#ifdef DEBUG
    std::ostream & o =
#ifdef USE_COUT
      std::cout
#else
      std::cerr
#endif
      ;
    if(r < 0) r = n;
    o << "{";
    for(int i = 0; i < std::min(r, n); i++) o << (i ? ", " : "") << get(i);
    o << "}" << std::endl;
#endif
  }
};

/// }}}--- ///

// Monoid examples {{{

constexpr long long inf = std::numeric_limits<long long>::max();
// using P = pair<ll, ll>

struct MonoidMin {
  using T = long long;
  static T op(const T& a, const T& b) { return std::min(a, b); }
  static constexpr T identity() { return inf; }
};
struct MonoidSum {
  using T = long long;
  static T op(const T& a, const T& b) { return a + b; }
  static constexpr T identity() { return 0; }
};
struct MonoidMax {
  using T = long long;
  static T op(const T& a, const T& b) { return std::max(a, b); }
  static constexpr T identity() { return -inf; }
};

// }}}

// using RMQ = SegTree<MonoidMin>;
// RMQ rmq(N);

