#ifndef TPOINT_H
#define TPOINT_H
#include <cmath>
class TPoint {
public:
  int x;
  int y;
  constexpr TPoint();
  constexpr TPoint(int xpos, int ypos);

  constexpr inline bool isCeroVector() const;
  constexpr static inline int dotProduct(const TPoint &p1, const TPoint &p2) {
    return p1.x * p2.x + p1.y * p2.y;
  }

  inline int &rx();
  inline int &ry();

  // Operadores:
  TPoint &operator+=(const TPoint &p);
  TPoint &operator-=(const TPoint &p);
  TPoint &operator*=(float m);
  TPoint &operator*=(double m);
  TPoint &operator*=(int m);
  TPoint &operator/=(float m);

  constexpr friend inline bool operator==(const TPoint &, const TPoint &);
  constexpr friend inline bool operator!=(const TPoint &, const TPoint &);

  constexpr friend inline const TPoint operator+(const TPoint &,
                                                 const TPoint &);
  constexpr friend inline const TPoint operator-(const TPoint &,
                                                 const TPoint &);

  friend inline const TPoint operator*(const TPoint &, float);
  friend inline const TPoint operator*(float, const TPoint &);

  friend inline const TPoint operator*(const TPoint &, double);
  friend inline const TPoint operator*(double, const TPoint &);

  friend inline const TPoint operator*(const TPoint &, int);
  friend inline const TPoint operator*(int, const TPoint &);

  friend inline const TPoint operator+(const TPoint &);
  friend inline const TPoint operator-(const TPoint &);
  friend inline const TPoint operator/(const TPoint &, float);

private:
};

constexpr inline TPoint::TPoint() : x(0), y(0) {}

constexpr inline TPoint::TPoint(int x, int y) : x(x), y(y) {}

constexpr inline bool TPoint::isCeroVector() const { return x == 0 && y == 0; }

inline int &TPoint::rx() { return x; }

inline int &TPoint::ry() { return y; }

inline TPoint &TPoint::operator+=(const TPoint &p) {
  x += p.x;
  y += p.y;
  return *this;
}

inline TPoint &TPoint::operator-=(const TPoint &p) {
  x -= p.x;
  y -= p.y;
  return *this;
}

inline TPoint &TPoint::operator*=(float m) {
  x = static_cast<int>(std::round(x * m));
  y = static_cast<int>(std::round(y * m));
  return *this;
}

inline TPoint &TPoint::operator*=(double m) {
  x = static_cast<int>(std::round(x * m));
  y = static_cast<int>(std::round(y * m));
  return *this;
}

inline TPoint &TPoint::operator*=(int m) {
  x = x * m;
  y = y * m;
  return *this;
}

inline TPoint &TPoint::operator/=(float c) {
  x = static_cast<int>(std::round(x / c));
  y = static_cast<int>(std::round(y / c));
  return *this;
}

constexpr inline bool operator==(const TPoint &p1, const TPoint &p2) {
  return p1.x == p2.x && p1.y == p2.y;
}

constexpr inline bool operator!=(const TPoint &p1, const TPoint &p2) {
  return p1.x != p2.x || p1.y != p2.y;
}

constexpr inline const TPoint operator+(const TPoint &p1, const TPoint &p2) {
  return TPoint(p1.x + p2.x, p1.y + p2.y);
}

constexpr inline const TPoint operator-(const TPoint &p1, const TPoint &p2) {
  return TPoint(p1.x - p2.x, p1.y - p2.y);
}

inline const TPoint operator*(const TPoint &p, float m) {
  return TPoint(static_cast<int>(std::round(p.x * m)),
                static_cast<int>(std::round(p.y * m)));
}

inline const TPoint operator*(float m, const TPoint &p) {
  return TPoint(static_cast<int>(std::round(p.x * m)),
                static_cast<int>(std::round(p.y * m)));
}

inline const TPoint operator*(const TPoint &p, double m) {
  return TPoint(static_cast<int>(std::round(p.x * m)),
                static_cast<int>(std::round(p.y * m)));
}

inline const TPoint operator*(double m, const TPoint &p) {
  return TPoint(static_cast<int>(std::round(p.x * m)),
                static_cast<int>(std::round(p.y * m)));
}

inline const TPoint operator*(const TPoint &p, int m) {
  return TPoint(p.x * m, p.y * m);
}

inline const TPoint operator*(int m, const TPoint &p) {
  return TPoint(p.x * m, p.y * m);
}

inline const TPoint operator+(const TPoint &p) { return p; }

inline const TPoint operator-(const TPoint &p) { return TPoint(-p.x, -p.y); }

inline const TPoint operator/(const TPoint &p, float c) {
  return TPoint(static_cast<int>(std::round(p.x / c)),
                static_cast<int>(std::round(p.y / c)));
}

#endif // TPOINT_H
