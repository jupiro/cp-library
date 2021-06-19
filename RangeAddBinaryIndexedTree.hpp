template<typename T>
struct RangeAddBinaryIndexedTree {
  int n;
  BinaryIndexedTree<T> bit[2];
  RangeAddBinaryIndexedTree() :n(0) {}
  RangeAddBinaryIndexedTree(int _n) :n(_n) { bit[0] = bit[1] = BinaryIndexedTree<T>(n); }

  //0-indexed, [left, right)
  void add(int left, int right, T val) {
    bit[0].add(left, -val * (left - 1));
    bit[0].add(right, val * (right - 1));
    bit[1].add(left, val);
    bit[1].add(right, -val);
  }
  
  //0-indexed, [left, right)
  T sum(int left, int right) {
    T suml = bit[0].sum(0, left) + bit[1].sum(0, left) * (left - 1);
    T sumr = bit[0].sum(0, right) + bit[1].sum(0, right) * (right - 1);
    return sumr - suml;
  }
};