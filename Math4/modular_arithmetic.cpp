int add(int a, int b) {
  return (a + b + mod) % mod;
}
int mult(int a, int b) {
  return 1ll * (a % mod) * (b % mod) % mod;
}
int fpm(int b, int p) {
  if (!p) {
    return 1;
  }
  int x = fpm(b, p >> 1);
  x = mult(x, x);
  return p & 1 ? mult(x, b) : x;
}
int modInv(int n) {
  return fpm(n, mod - 2);
}
int divi(int a, int b) {
  return mult(a, modInv(b));
}