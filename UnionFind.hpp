namespace KKT89
{
  struct UnionFind
  {
    std::vector<int> par;
    UnionFind(int n)
    {
        par.assign(n, -1);
    }
    int root(int a)
    {
        if (par[a] < 0)
        {
            return a;
        }
        return par[a] = root(par[a]);
    }

    int size(int a)
    {
        return -par[root(a)];
    }
    bool connect(int a, int b)
    {
        a = root(a);
        b = root(b);
        if (a == b)
        {
            return false;
        }
        if (size(a) < size(b))
        {
            std::swap(a, b);
        }

        par[a] += par[b];
        par[b] = a;

        return true;
    }
    bool same(int a, int b)
    {
        return root(a) == root(b);
    }
  };
}