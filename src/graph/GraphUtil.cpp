// @ Tree Diametor
// @snippet tree_diameter
// @alias diameter_of_tree chokkei_of_tree
// tree_diameter( <tree> ) : (size, p1, p2) {{{
#include <stack>
#include <tuple>
#include <vector>
std::tuple< int, std::size_t, std::size_t > tree_diameter(
    const std::vector< std::vector< int > > &tree) {
  using size_type = std::size_t;
  size_type farthest, a, b, depth;
  auto dfs = [&](size_type i) {
    farthest = i;
    std::stack< std::tuple< size_type, int, size_type > > stk;
    stk.emplace(i, -1, 0);
    while(stk.size()) {
      size_type i, d;
      int p;
      std::tie(i, p, d) = stk.top();
      stk.pop();
      if(depth < d) farthest = i, depth = d;
      for(int j : tree[i])
        if(j != p) stk.emplace(j, i, d + 1);
    }
  };
  dfs(0);
  dfs(a = farthest);
  b = farthest;
  return std::make_tuple(depth, a, b);
}
// }}}

// @new
// @ Distance of Tree
// @snippet dist_tree
// @alias tree_dist
// get_dist_tree( <tree>, from ) {{{
#include <cassert>
#include <stack>
#include <vector>
std::vector< int > get_dist_tree(const std::vector< std::vector< int > > tree,
                                 std::size_t from) {
  using size_type = std::size_t;
  size_type n = tree.size();
  assert(from < n);
  std::vector< int > res(n);
  std::stack< std::tuple< size_type, int, int > > stk;
  stk.emplace(from, -1, 0);
  while(stk.size()) {
    size_type i;
    int p, d;
    std::tie(i, p, d) = stk.top();
    stk.pop();
    res[i] = d;
    for(auto j : tree[i])
      if(j != p) stk.emplace(j, i, d + 1);
  }
  return res;
}
// }}}

// @new
// @ dijkstra graph
// @snippet     dijkstra_graph
vector< ll > dist(n, 1e18);
// dijkstra {{{
{
  using P = tuple< ll, int >;
  priority_queue< P, vector< P >, greater< P > > pq;
  pq.emplace(0, s);
  dist[s] = 0;
  while(pq.size()) {
    ll di;
    int i;
    tie(di, i) = pq.top();
    pq.pop();
    if(dist[i] < di) continue;
    for(auto to : g[i]) {
      int j, co;
      tie(j, co) = to;
      ll ndi = di + co;
      if(dist[j] > ndi) {
        dist[j] = ndi;
        pq.emplace(ndi, j);
      }
    }
  }
}
// }}}

// @new
// @ dijkstra grid
// @snippet dijkstragrid
// @alias bfs01 01bfs
vector< vector< ll > > dist(h, vector< ll >(w, 1e18));
// dijkstra {{{
{
  using P = tuple< ll, int, int >;
  deque< P > pq;
  pq.emplace_back(0, sy, sx);
  dist[sy][sx] = 0;
  while(pq.size()) {
    ll di;
    int y, x;
    tie(di, y, x) = pq.front();
    pq.pop_front();
    if(dist[y][x] < di) continue;
    for(int d = 0; d < 4; d++) {
      int ny = y + dy[d];
      int nx = x + dx[d];
      if(ny < 0 || nx < 0 || ny >= h || nx >= w) continue;
      if(dist[ny][nx] > di + 1) {
        dist[ny][nx] = di + 1;
        pq.emplace_back(di + 1, j);
      }
    }
  }
}
// }}}
