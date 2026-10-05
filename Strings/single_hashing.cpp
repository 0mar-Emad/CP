mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int64_t rnd(int64_t l, int64_t r) { return uniform_int_distribution<int64_t>(l, r)(rng); }
const uint64_t base = rnd(1e6, 1e9) | 1;
struct HashedString {
  vector<uint64_t> hash{0}, pw{1};
  HashedString() {};
  HashedString(const string &s) { build(s); }
  void build(const string &s) {
    for (char c : s) {
      push_back(c);
    }
  }
  void push_back(char c) {
    hash.push_back(hash.back() * base + c);
    pw.push_back(pw.back() * base);
  }
  uint64_t get(int l, int r) {
    return hash[r + 1] - hash[l] * pw[r - l + 1];
  }
  uint64_t operator()() {
    return hash.back();
  }
};