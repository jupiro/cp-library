template<typename OperatorMonoid, typename H>
struct DualSegmentTree {
	int sz, height;
	std::vector<OperatorMonoid> lazy;
	const H h;
	const OperatorMonoid OMI;

	DualSegmentTree(int n, const H h, const OperatorMonoid& OMI):h(h), OMI(OMI) {
		sz = 1;
		height = 0;
		while (sz < n) sz <<= 1, height++;
		lazy.assign(2 * sz, OMI);
	}

	void propagate(int k) {
		if (lazy[k] != OMI) {
			lazy[2 * k] = h(lazy[2 * k], lazy[k]);
			lazy[2 * k + 1] = h(lazy[2 * k + 1], lazy[k]);
			lazy[k] = OMI;
		}
	}

	void thrust(int k) {
		for (int i = height; i > 0; i--) propagate(k >> i);
	}

	void update(int a, int b, const OperatorMonoid& x) {
		thrust(a += sz);
		thrust(b += sz - 1);
		for (int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) lazy[l] = h(lazy[l], x), l += 1;
			if (r & 1) r -= 1, lazy[r] = h(lazy[r], x);
		}
	}
	OperatorMonoid operator[](int k) {
		thrust(k += sz);
		return lazy[k];
	}
};