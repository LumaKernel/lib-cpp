// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet     graph
// @name Graph Template
/// --- Graph Template {{{ ///

template < class T >
struct Edge {
  int from, to;
  T cost;
  Edge(int to, T cost) : from(-1), to(to), cost(cost) {}
  Edge(int from, int to, T cost) : from(from), to(to), cost(cost) {}
};
template < class T >
using WeightedGraph = vector< vector< Edge< T > > >;
using UnWeightedGraph = vector< vector< int > >;

/// }}}--- ///
