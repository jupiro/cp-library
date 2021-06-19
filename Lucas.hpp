namespace KKT89
{
	int Lucas(int n, int m, int mod)
	{
		auto com = [&](int p, int q)
		{
			int res = 1;
			for (int i = 1; i <= q; ++i)
			{
				res *= (p - i + 1);
				res /= i;
			}
			return res % mod;
		};
		int ret = 1;
		while(n > 0 and m > 0)
		{
			ret *= com(n % mod, m % mod);
			ret %= mod;
			n /= mod;
			m /= mod;
		}
		return ret;
	}
}
