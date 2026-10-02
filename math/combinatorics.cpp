int64_t nCr(int64_t n, int64_t r) {
  if (r > n || r < 0) return 0;
  r = min(r, n - r);
  int64_t res = 1;
  for (int i = 0; i < r; i++) {
    res = res * (n - i) / (i + 1);
  }
  return res;
}
int64_t nPr(int64_t n, int64_t r) {
  if (r < 0 || r > n) return 0;
  int64_t res = 1;
  for (int64_t i = 0; i < r; i++) {
    res *= n - i;
  }
  return res;
}
int64_t sNb(int n, int k) {
  return nCr(n + k - 1, n);
}