// @ binary-to-gray
// @snippet binary_to_gray

unsigned long long binary_to_gray(unsigned long long x) { return x ^ (x >> 1); }

// @new gray-to-binary
// @snippet binary_to_gray
unsigned long long gray_to_binary(unsigned long long x) {
  x = x ^ (x >> 32);
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
  return x;
}

#include <cassert>
#include <vector>
void toGray(unsigned base, unsigned digits, unsigned value) {
  std::vector< unsigned > gray(digits);
  std::vector< unsigned > baseN(digits);
  unsigned i; // The loop variable

  // Put the normal baseN number into the baseN array. For base 10, 109
  // would be stored as [9,0,1]
  for(i = 0; i < digits; i++) {
    baseN[i] = value % base;
    value = value / base;
  }

  // Convert the normal baseN number into the Gray code equivalent. Note that
  // the loop starts at the most significant digit and goes down.
  unsigned shift = 0;
  while(i--) {
    // The Gray digit gets shifted down by the sum of the higher
    // digits.
    gray[i] = (baseN[i] + shift) % base;
    shift = shift + base - gray[i]; // Subtract from base so shift is positive
  }
}

#include <bitset>
#include <iostream>
using namespace std;
int main() {
  for(int i = 0; i < 1 << 3; i++) cout << bitset< 8 >(binary_to_gray(i)) << endl;
}
