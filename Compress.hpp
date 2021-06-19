namespace KKT89
{
	template<typename T>
	struct Compress {
		std::vector<T> v;
		Compress() {}
		Compress(std::vector<T> _v) :v(_v) { build(); }
	 
		void add(T x) {
			v.emplace_back(x);
		}
	 
		void build() {
			std::sort(v.begin(), v.end());
			v.erase(unique(v.begin(), v.end()), v.end());
		}
	 
		int get(T x) {
			return std::lower_bound(v.begin(), v.end(), x) - v.begin();
		}
	 
		T& operator[](int i) { return v[i]; }
	 
	 
		int size() {
			return (int)v.size();
		}
	};
}