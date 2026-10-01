struct XorBasis {
  static constexpr int B = 20;
  int sz = 0;
  array<int, B> b{};
  void insert(int x) {
    for (int i = B - 1; ~i; --i) {
      if (!(x >> i & 1)) continue;
      if (!b[i]) {
        b[i] = x, ++sz;
        return;
      }
      x ^= b[i];
    }
  }
  // Checks if a target number x can be formed by XOR combinations.
  bool can(int x) {
    for (int i = B - 1; ~i; --i) {
      if (!(x >> i & 1)) continue;
      if (!b[i]) return 0;
      x ^= b[i];
    }
    return !x;
  }
  // Returns the maximum possible XOR sum from any subset.
  int max_xor() {
    int x = 0;
    for (int i = B - 1; ~i; --i) {
      x = max(x, x ^ b[i]);
    }
    return x;
  }
  // Returns the k-th smallest unique XOR sum (1-indexed, k=1 is 0).
  int kth_smallest_xor(int k) {
    int x = 0, cnt = 1ll << sz;
    for (int i = B - 1; ~i; --i) {
      if (!b[i]) continue;
      cnt /= 2;
      if (x >> i & 1) {
        if (cnt >= k) {
          x ^= b[i];
        } else {
          k -= cnt;
        }
      } else if (cnt < k) {
        x ^= b[i], k -= cnt;
      }
    }
    return x;
  }
};