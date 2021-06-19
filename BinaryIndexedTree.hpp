namespace KKT89
{
	template<typename T>
	struct BinaryIndexedTree {
		int n;
		std::vector<T> bit;
		BinaryIndexedTree() :n(0) {}
		BinaryIndexedTree(int _n) :n(_n) { bit = std::vector<T>(n + 1); }
		void add1(int idx, T val) {
			for (int i = idx; i <= n; i += i & -i) bit[i] += val;
		}
		T sum1(int idx) {
			T res = 0;
			for (int i = idx; i > 0; i -= i & -i) res += bit[i];
			return res;
		}
		//0-indexed
		void add(int idx, T val) { add1(idx + 1, val); }
		//0-indexed [left, right)
		T sum(int left, int right) { return sum1(right) - sum1(left); }

		int lower_bound(T x) {
			int res = 0;
			int k = 1;
			while (2 * k <= n) k <<= 1;
			for (; k > 0; k >>= 1) {
				if (res + k <= n and bit[res + k] < x) {
					x -= bit[res + k];
					res += k;
				}
			}
			return res;
		}
	};
}