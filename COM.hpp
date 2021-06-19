const int MAX = (int)1e6;
mint fac[MAX], finv[MAX], inv[MAX];
 
void COMinit() {
	fac[0] = fac[1] = 1;
	finv[0] = finv[1] = 1;
	inv[1] = 1;
	for (int i = 2; i < MAX; i++) {
		fac[i] = fac[i - 1] * i;
		inv[i] = -inv[mod % i] * (mod / i);
		finv[i] = finv[i - 1] * inv[i];
	}
}
 
mint COM(int n, int k) {
	if (n < k) return 0;
	if (n < 0 || k < 0) return 0;
	return fac[n] * finv[k] * finv[n - k];
}
 
mint LCOM(ll n, ll k) {
	if (n < k) return 0;
	if (n < 0 || k < 0) return 0;
	if (k > n / 2) k = n - k;
	mint res = 1;
	for (int i = 0; i < k; i++) res *= (n - i);
	res *= finv[k];
	return res;
}