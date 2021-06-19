#include <cmath>
#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
namespace geometry
{
  using Real = double;
  const Real EPS = 1e-8;
  const Real PI = std::acos((Real)(-1));

  inline int sign(const Real &r) {
    return r <= -EPS ? -1 : r >= EPS ? 1 : 0;
  }

  inline bool equals(const Real &a, const Real &b) {
    return sign(a - b) == 0;
  }

  using Point = std::complex<Real>;

  Point operator*(const Point &p, const Real &d) {
    return Point(p.real() * d, p.imag() * d);
  }

  // rotate point p counterclockwise by theta rad
  Point rotate(Real theta, const Point &p) {
    return Point(std::cos(theta) * p.real() - std::sin(theta) * p.imag(), std::sin(theta) * p.real() + std::cos(theta) * p.imag());
  }

  Real cross(const Point &a, const Point &b) {
    return a.real() * b.imag() - a.imag() * b.real();
  }

  Real dot(const Point &a, const Point &b) {
    return a.real() * b.real() + a.imag() * b.imag();
  }

  bool compare_x(const Point &a, const Point &b) {
    return equals(a.real(), b.real()) ? a.imag() < b.imag() : a.real() < b.real();
  }

  bool compare_y(const Point &a, const Point &b) {
    return equals(a.imag(), b.imag()) ? a.real() < b.real() : a.imag() < b.imag();
  }
  
  using Points = std::vector<Point>;
  using Polygon = std::vector<Point>;
  struct Line {
    Point a, b;

    Line() = default;

    Line(const Point &a, const Point &b) : a(a), b(b) {}

    Line(const Real &A, const Real &B, const Real &C) { // Ax+By=C
      if(equals(A, 0)) {
        assert(!equals(B, 0));
        a = Point(0, C / B);
        b = Point(1, C / B);
      } else if(equals(B, 0)) {
        a = Point(C / A, 0);
        b = Point(C / A, 1);
      } else {
        a = Point(0, C / B);
        b = Point(C / A, 0);
      }
    }
  };

  using Lines = std::vector<Line>;
  bool is_parallel(const Line &a, const Line &b)
  {
    return equals(cross(a.b - a.a, b.b - b.a), 0.0);
  }
  bool is_intersect_ll(const Line &l, const Line &m)
  {
    Real A = cross(l.b - l.a, m.b - m.a);
    Real B = cross(l.b - l.a, l.b - m.a);
    if(equals(std::abs<Real>(A), 0) && equals(std::abs<Real>(B), 0)) return true;
    return !is_parallel(l, m);
  }
  struct Segment : Line
  {
    Segment() = default;
    using Line::Line;
  };
  constexpr int COUNTER_CLOCKWISE = +1;
  constexpr int CLOCKWISE = -1;
  constexpr int ONLINE_BACK = +2; // c-a-b
  constexpr int ONLINE_FRONT = -2; // a-b-c
  constexpr int ON_SEGMENT = 0; // a-c-b
  int ccw(const Point &a, Point b, Point c) {
    b = b - a, c = c - a;
    if(sign(cross(b, c)) == +1) return COUNTER_CLOCKWISE;
    if(sign(cross(b, c)) == -1) return CLOCKWISE;
    if(sign(dot(b, c)) == -1) return ONLINE_BACK;
    if(std::norm(b) < std::norm(c)) return ONLINE_FRONT;
    return ON_SEGMENT;
  }
  using Segments = std::vector<Segment>;
  bool is_intersect_ss(const Segment &s, const Segment &t) 
  {
      return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) <= 0 &&
             ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
  }
  Polygon convex_hull(Polygon &p, bool strict = true) {
      int n = (int)p.size(), k = 0;
      if(n <= 2) return p;
      std::sort(p.begin(), p.end(), compare_x);
      std::vector<Point> ch(2 * n);
      auto check = [&](int i) {
        return sign(cross(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1])) <= -1 + strict;
      };
      for(int i = 0; i < n; ch[k++] = p[i++]) {
        while(k >= 2 && check(i)) --k;
      }
      for(int i = n - 2, t = k + 1; i >= 0; ch[k++] = p[i--]) {
        while(k >= t && check(i)) --k;
      }
      ch.resize(k - 1);
      return ch;
    }
}