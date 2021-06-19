template<class T>
struct CumulativeSum2D {
	std::vector<std::vector<T>> data;
	int H, W;
	CumulativeSum2D() :H(0), W(0) {}
	CumulativeSum2D(int _H, int _W) :H(_H), W(_W) {
		data.assign(H + 1, std::vector<T>(W + 1));
	}
	CumulativeSum2D(std::vector<std::vector<T>>& _data) :H(_data.size()), W(_data[0].size()) {
		data.assign(H + 1, std::vector<T>(W + 1));
		for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) data[i + 1][j + 1] += _data[i][j];
		build();
	}

	void add(int h, int w, T x) {
		data[h + 1][w + 1] += x;
	}
	void build() {
		for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) data[i + 1][j + 1] += data[i + 1][j] + data[i][j + 1] - data[i][j];
	}

	T query(int sh, int sw, int gh, int gw) const {
		return data[gh][gw] - data[sh][gw] - data[gh][sw] + data[sh][sw];
	}
};