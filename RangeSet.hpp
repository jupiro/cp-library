//線分区間管理
template<typename T>
struct RangeSet
{
  std::set<std::pair<T, T>> sp;
  T INF;
  RangeSet() 
  {
    INF = std::numeric_limits<T>::max()/2;
  }

  //[l, r)の区間をinsert
  //増加量を返す
  T insert(T l, T r)
  {
    sp.emplace(INF,INF);
    sp.emplace(-INF,-INF);
    auto itr = std::prev(sp.lower_bound({l + 1, -INF}));
    //すでに覆われてる
    if(itr->first <= l and r <=itr->second)
    {
      return T(0);
    }
    T erase = 0;
    //左端の処理
    if(itr->first <= l and l <= itr->second)
    {
      l = itr->first;
      erase += itr->second - itr->first;
      itr = sp.erase(itr);
    }
    else
    {
      itr = std::next(itr);
    }
    //右端の処理
    while(itr->second < r)
    {
      erase += itr->second - itr->first;
      itr = sp.erase(itr);
    }
    if(itr->first <= r and r <= itr->second)
    {
      erase += itr->second - itr->first;
      r = itr->second;
      itr = sp.erase(itr);
    }
    sp.emplace(l, r);
    sp.erase(sp.find({INF, INF}));
    sp.erase(sp.find({-INF, -INF}));
    return r - l - erase;
  }

  //[l, r)のerase
  //減少量を返す
  T erase(T l, T r)
  {
    sp.emplace(INF,INF);
    sp.emplace(-INF,-INF);
    auto itr = std::prev(sp.upper_bound({l, INF}));
    if(itr->first <= l and r <= itr->second)
    {
        const auto p = *itr;
        sp.erase(itr);
        if(p.first < l)
            sp.emplace(p.first, l);
        if(r < p.second)
            sp.emplace(r, p.second);
        return r - l;
    }
    T ret = 0;
    if(itr->first <= l and l < itr->second)
    {
        const auto p = *itr;
        itr = sp.erase(itr);
        ret += p.second - l;
        if(p.first < l)
        {
            sp.emplace(p.first, l);
        }
    }
    else
    {
        itr = std::next(itr);
    }
    while(itr->second <= r)
    {
        ret += itr->second - itr->first;
        itr = sp.erase(itr);
    }
    if(itr->first < r and r <= itr->second)
    {
        const auto p = *itr;
        sp.erase(itr);
        ret += r - p.first;
        if(r < p.second)
            sp.emplace(r, p.second);

    }
    return ret;
  }
};
