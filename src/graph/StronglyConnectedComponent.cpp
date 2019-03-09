// @ Strongly Connected Component
// @snippet scc

// SCC( size )
// SCC( <directed-graph> )
// .add_edge(from, to)
// === .built() ===
//    - O(N)
// .component_size()
// .get_renew() : return directed-graph whose size is .compoent_size()
//    - O(N log N)
// .get_comp_to_vertex() : it[component_id] is vector<size_type>
//    - O(N)
// .topo[i]
// .comp[i] : alias = .[i]
/// --- Strongly Connected Component {{{ ///
#include <algorithm>
#include <cassert>
#include <set>
#include <vector>
// Kosaraju's StronglyConnectedComponent
struct StronglyConnectedComponent {
public:
  using size_type = std::size_t;
  using graph_type = std::vector< std::vector< int > >;
  size_type n;
  graph_type graph, rev;
  std::vector< size_type > topo;
  std::vector< size_type > comp;

private:
  std::vector< int > used;
  size_type k;

public:
  StronglyConnectedComponent() : n(0) {}
  StronglyConnectedComponent(size_type n) : n(n), graph(n), rev(n) {}
  StronglyConnectedComponent(graph_type input_graph)
      : StronglyConnectedComponent(input_graph.size()) {
    for(size_type from = 0; from < n; from++)
      for(auto to : input_graph[from]) add_edge(from, to);
  }

private:
  bool built = 0;

public:
  void add_edge(size_type a, size_type b) {
    assert(!built);
    assert(a < n && b < n);
    graph[a].emplace_back(b);
    rev[b].emplace_back(a);
  }
  void build() {
    assert(!built);
    built = 1;
    used.resize(n, 0);
    comp.resize(n, n);
    for(size_type i = 0; i < n; i++)
      if(!used[i]) dfs1(i);
    reverse(topo.begin(), topo.end());
    k = 0;
    for(auto i : topo)
      if(comp[i] == n) dfs2(i), k++;
  }
  graph_type get_renew() {
    assert(built);
    graph_type renew(k);

    std::set< std::pair< size_type, size_type > > connect;
    for(size_type i = 0; i < n; i++) {
      for(auto j : graph[i]) {
        size_type x = comp[i], y = comp[j];
        if(x == y) continue;
        if(connect.count(std::make_pair(x, y))) continue;
        connect.emplace(x, y);
        renew[x].emplace_back(y);
      }
    }
    return renew;
  }
  std::vector< std::vector< size_type > > get_comp_to_vertex() {
    assert(built);
    std::vector< std::vector< size_type > > comp_to_vertex(k, std::vector< size_type >());
    for(size_type i = 0; i < n; i++) comp_to_vertex[comp[i]].emplace_back(i);
    return comp_to_vertex;
  }

  size_type size() const { return n; }
  size_type component_size() const {
    assert(built);
    return k;
  }
  size_type operator[](size_type i) const {
    assert(built);
    return comp.at(i);
  }

private:
  void dfs1(size_type i) {
    if(used[i]) return;
    used[i] = 1;
    for(auto j : graph[i]) dfs1(j);
    topo.emplace_back(i);
  }
  void dfs2(size_type i) {
    if(comp[i] != n) return;
    comp[i] = k;
    for(auto j : rev[i]) dfs2(j);
  }
};
/// }}}--- ///
using SCC = StronglyConnectedComponent;
