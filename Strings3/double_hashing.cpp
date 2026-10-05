mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int64_t rnd(int64_t l, int64_t r) { return uniform_int_distribution<int64_t>(l, r)(rng); }
const int64_t mod1 = 1e9 + 7, mod2 = 1e9 + 9;
const int64_t base1 = rnd(mod1 / 4, mod1 * 3 / 4);
const int64_t base2 = rnd(mod2 / 4, mod2 * 3 / 4);
struct HashedString {
  vector<int64_t> hash1{0}, hash2{0};
  vector<int64_t> pw1{1}, pw2{1};
  HashedString() {}
  HashedString(const string &s) { build(s); }
  void build(const string &s) {
    for (char c : s) {
      push_back(c);
    }
  }
  void push_back(char c) {
    hash1.push_back((hash1.back() * base1 + c) % mod1);
    pw1.push_back(pw1.back() * base1 % mod1);
    hash2.push_back((hash2.back() * base2 + c) % mod2);
    pw2.push_back(pw2.back() * base2 % mod2);
  }
  pair<int64_t, int64_t> get(int l, int r) {
    auto h1 = (hash1[r + 1] - hash1[l] * pw1[r - l + 1] % mod1 + mod1) % mod1;
    auto h2 = (hash2[r + 1] - hash2[l] * pw2[r - l + 1] % mod2 + mod2) % mod2;
    return {h1, h2};
  }
  pair<int64_t, int64_t> operator()() {
    return {hash1.back(), hash2.back()};
  }
};