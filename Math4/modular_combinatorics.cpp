int mult(int a, int b) {
  return 1ll * (a % mod) * (b % mod) % mod;
}
int fpm(int b, int p) {
  if (!p) return 1;
  int x = fpm(b, p >> 1);
  x = mult(x, x);
  return p & 1 ? mult(x, b) : x;
}
int modInv(int n) {
  return fpm(n, mod - 2);
}
vector<int> fact(N + 1), ifact(N + 1);
void preFact() {
  fact[0] = 1;
  for (int i = 1; i <= N; i++) {
    fact[i] = mult(fact[i - 1], i);
  }
  ifact[N] = modInv(fact[N]);
  for (int i = N; i > 0; i--) {
    ifact[i - 1] = mult(ifact[i], i);
  }
}
int nCr(int n, int r) {
  if (r < 0 || r > n) return 0;
  return mult(fact[n], mult(ifact[r], ifact[n - r]));
}
int nPr(int n, int r) {
  if (r < 0 || r > n) return 0;
  return mult(fact[n], ifact[n - r]);
}
int sNb(int n, int k) {
  return nCr(n + k - 1, n);
}