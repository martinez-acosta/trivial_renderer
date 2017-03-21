#ifndef TVector3D_H
#define TVector3D_H
#include "tpoint.h"
#include <cmath>
class TVector3D {
public:
  float x, y, z;
  // Constructores
  TVector3D();
  TVector3D(float x, float y, float z);
  explicit TVector3D(const TPoint &p);

  // Métodos
  constexpr float length() const;
  constexpr float lengthSquared() const;
  constexpr bool isCeroVector() const;
  constexpr float dotProduct(const TVector3D &v1, const TVector3D &v2) const;
  TPoint toPoint() const;
  TVector3D normalize() const;
  TVector3D crossProduct(const TVector3D &v1, const TVector3D &v2) const;

  // Operadores:
  float &operator[](std::size_t i);
  float operator[](std::size_t i) const;
  TVector3D &operator+=(const TVector3D &vector);
  TVector3D &operator-=(const TVector3D &vector);
  TVector3D &operator*=(float m);
  TVector3D &operator/=(float m);

  constexpr friend inline bool operator==(const TVector3D &v1,
                                          const TVector3D &v2);
  constexpr friend inline bool operator!=(const TVector3D &v1,
                                          const TVector3D &v2);
  friend inline TVector3D operator+(const TVector3D &v1, const TVector3D &v2);
  friend inline TVector3D operator-(const TVector3D &v1, const TVector3D &v2);
  friend inline TVector3D operator*(float m, const TVector3D &vector);
  friend inline TVector3D operator*(const TVector3D &vector, float m);
  friend inline TVector3D operator-(const TVector3D &vector);
  friend inline TVector3D operator/(const TVector3D &vector, float m);

private:
};

inline float &TVector3D::operator[](std::size_t i) {
  switch (i) {
  case 0:
    return x;
  case 1:
    return y;
  case 2:
    return z;
  }
}

inline float TVector3D::operator[](std::size_t i) const {
  switch (i) {
  case 0:
    return x;
  case 1:
    return y;
  case 2:
    return z;
  }
}

inline TVector3D &TVector3D::operator+=(const TVector3D &vector) {
  x += vector.x;
  y += vector.y;
  z += vector.z;
  return *this;
}

inline TVector3D &TVector3D::operator-=(const TVector3D &vector) {
  x -= vector.x;
  y -= vector.y;
  z -= vector.z;
  return *this;
}

inline TVector3D &TVector3D::operator*=(float m) {
  x *= m;
  y *= m;
  z *= m;
  return *this;
}

inline TVector3D &TVector3D::operator/=(float m) {
  x /= m;
  y /= m;
  z /= m;
  return *this;
}

constexpr inline bool operator==(const TVector3D &v1, const TVector3D &v2) {
  return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

constexpr inline bool operator!=(const TVector3D &v1, const TVector3D &v2) {
  return !(v1 == v2);
}

inline TVector3D operator+(const TVector3D &v1, const TVector3D &v2) {
  return TVector3D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline TVector3D operator-(const TVector3D &v1, const TVector3D &v2) {
  return TVector3D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline TVector3D operator*(float m, const TVector3D &vector) {
  return TVector3D(vector.x * m, vector.y * m, vector.z * m);
}

inline TVector3D operator*(const TVector3D &vector, float m) {
  return TVector3D(vector.x * m, vector.y * m, vector.z * m);
}

inline TVector3D operator-(const TVector3D &vector) {
  return TVector3D(-vector.x, -vector.y, -vector.z);
}

inline TVector3D operator/(const TVector3D &vector, float m) {
  return TVector3D(vector.x / m, vector.y / m, vector.z / m);
}

#endif // TVector3D_H
