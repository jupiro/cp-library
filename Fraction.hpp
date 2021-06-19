namespace KKT89
{
  //p / q
  template<typename T>
  struct Fraction
  {
    T p, q;
    Fraction() : p(0), q(0) {}
    Fraction(int p, int q) : p(p), q(q) {}

    bool operator< (const Fraction &f) const
    {
      return p * f.q < q * f.p;
    }

    bool operator<= (const Fraction &f) const
    {
      return p * f.q <= q * f.p;
    }
  };
}