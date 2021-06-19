template<typename U = unsigned, int B = 32>
class BinaryTrie {
private:
  struct node {
    int cnt;
    node* ch[2];
    node() :cnt(0), ch{ nullptr, nullptr }{}
  };
  node* root;

  node* add(node* t, U val, int b = B - 1) {
    if (!t) t = new node;
    t->cnt += 1;
    if (b < 0) return t;
    bool f = val >> b & 1;
    t->ch[f] = add(t->ch[f], val, b - 1);
    return t;
  }

  node* sub(node* t, U val, int b = B - 1) {
    t->cnt -= 1;
    if (t->cnt == 0) return nullptr;
    if (b < 0) return t;
    bool f = val >> b & 1;
    t->ch[f] = sub(t->ch[f], val, b - 1);
    return t;
  }

  U kth_element(node* t, int k, U xor_val, int b = B - 1) const {
    if (b < 0) return 0;
    bool f = xor_val >> b & 1;
    if ((t->ch[f] ? t->ch[f]->cnt : 0) <= k) {
      U ret = kth_element(t->ch[f ^ 1], k - (t->ch[f] ? t->ch[f]->cnt : 0), xor_val, b - 1);
      ret |= U(1) << b;
      return ret;
    }
    else {
      return kth_element(t->ch[f], k, xor_val, b - 1);
    }
  }

  int count_lower(node* t, U val, int b = B - 1) {
    if (!t or b < 0) return 0;
    bool f = val >> b & 1;
    return ((f and t->ch[0]) ? t->ch[0]->cnt : 0) + count_lower(t->ch[f], val, b - 1);
  }

  U calc(node* t, U xor_val, int cnt, int b = B - 1) const
  {
    if(b < 0) return 0;
    
    const int f = xor_val >> b & 1;
    if(f == 0)
    {
      if((t->ch[0] ? t->ch[0]->cnt : 0) < cnt and t->ch[1])
      {
        return calc(t->ch[1], xor_val, cnt - (t->ch[0] ? t->ch[0]->cnt : 0) , b - 1) | (1 << b);
      }
      else
      {
        return calc(t->ch[0], xor_val, cnt, b - 1);
      }
    }
    else
    {
      if(t->ch[0])
      {
        return calc(t->ch[0], xor_val, cnt, b - 1);
      }
      else
      {
        return calc(t->ch[1], xor_val, cnt - (t->ch[0] ? t->ch[0]->cnt : 0), b - 1) | (1 << b);
      }
    }
    
    return 0;
  }
public:
  BinaryTrie() :root(nullptr) {}
  int size() const { return root ? root->cnt : 0; }
  bool empty() const { return !root; }
  void insert(U val) { root = add(root, val); }
  void erase(U val) { root = sub(root, val); }
  U kth_element(U k, U xor_val = 0)  const { return kth_element(root, k, xor_val); }
  U min_element(U xor_val = 0) const { return  kth_element(0, xor_val); }
  U max_element(U xor_val = 0) const { return kth_element(root->cnt - 1, xor_val); }
  int lower_bound(U val) { return count_lower(root, val); }
  int upper_bound(U val) { return count_lower(root, val + 1); }

  U calc(U xor_val, U cnt)
  {
    return calc(root, xor_val, cnt);
  }
};