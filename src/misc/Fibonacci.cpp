// @ Fibonacci
// @snippet fibonacci
// @alias fib

// require kitamasa
// f(0) = a, f(1) = b, f(i+2) = f(i+1) + f(i)
// return f(n)
// O(log N)
// fibonacci(a, b, n) {{{
#include <vector>
template < class T >
T fibonacci(T a, T b, unsigned long long n) {
  if(n < 16) {
    if(n == 0) return a;
    n--;
    while(n--) a += b, swap(a, b);
    return b;
  }
  std::vector< T > c{1, 1};
  std::vector< T > r{1, 0};
  std::vector< T > s{0, 1};
  while(n) {
    if(n & 1) r = kitamasa< T >(c, r, s);
    n >>= 1;
    if(n) s = kitamasa< T >(c, s, s);
  }
  return r[0] * a + r[1] * b;
}
// }}}
