const int N = 1e6 + 1;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
vector<uint64_t> hsh(N);
void prehash() {
  for (int i = 1; i < N; i++) {
    hsh[i] = rng();
  }
}