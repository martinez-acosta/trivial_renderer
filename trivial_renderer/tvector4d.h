#ifndef TVECTOR4D_H
#define TVECTOR4D_H
#include "tmatrix4x4.h"
#include "tpoint.h"
#include "tvector3d.h"
#include <cmath>
class TVector4D {
public:
  float x, y, z, w;
  // Constructores
  constexpr TVector4D();
  constexpr TVector4D(float x, float y, float z);
  constexpr TVector4D(float x, float y, float z, float w);
  constexpr explicit TVector4D(const TVector3D &vector);
  constexpr explicit TVector4D(const TVector3D &vector, float w);
  constexpr explicit TVector4D(const TPoint &p);

  // Métodos
  constexpr float length() const;
  constexpr float lengthSquared() const;
  constexpr float dotProduct(const TVector4D &v1, const TVector4D &v2) const;
  constexpr bool isCeroVector() const;
  constexpr TVector4D normalize() const;
  constexpr TPoint toPoint() const;
  constexpr TVector3D toVector3D() const;
  constexpr TVector3D toVector3DAffine() const;

  // Operadores:
  float &operator[](std::size_t i);
  float operator[](std::size_t i) const;
  TVector4D &operator+=(const TVector4D &vector);
  TVector4D &operator-=(const TVector4D &vector);
  TVector4D &operator*=(float m);
  TVector4D &operator/=(float m);

  constexpr friend inline bool operator==(const TVector4D &v1,
                                          const TVector4D &v2);
  constexpr friend inline bool operator!=(const TVector4D &v1,
                                          const TVector4D &v2);
  constexpr friend inline const TVector4D operator+(const TVector4D &v1,
                                                    const TVector4D &v2);
  constexpr friend inline const TVector4D operator-(const TVector4D &v1,
                                                    const TVector4D &v2);
  constexpr friend inline const TVector4D operator*(float m,
                                                    const TVector4D &vector);
  constexpr friend inline const TVector4D operator*(const TVector4D &vector,
                                                    float m);
  constexpr friend inline const TVector4D operator-(const TVector4D &vector);
  constexpr friend inline const TVector4D operator/(const TVector4D &vector,
                                                    float m);

private:
  friend class TVector3D;
  friend class TPoint;
  friend TMatrix4x4;
};

inline float &TVector4D::operator[](std::size_t i) {
  switch (i) {
  case 0:
    return x;
  case 1:
    return y;
  case 2:
    return z;
  case 3:
    return w;
  }
}

inline float TVector4D::operator[](std::size_t i) const {
  switch (i) {
  case 0:
    return x;
  case 1:
    return y;
  case 2:
    return z;
  case 3:
    return w;
  }
}

inline TVector4D &TVector4D::operator+=(const TVector4D &vector) {
  x += vector.x;
  y += vector.y;
  z += vector.z;
  w += vector.w;
  return *this;
}

inline TVector4D &TVector4D::operator-=(const TVector4D &vector) {
  x -= vector.x;
  y -= vector.y;
  z -= vector.z;
  w -= vector.w;
  return *this;
}

inline TVector4D &TVector4D::operator*=(float m) {
  x *= m;
  y *= m;
  z *= m;
  w *= m;
  return *this;
}

inline TVector4D &TVector4D::operator/=(float m) {
  x /= m;
  y /= m;
  z /= m;
  w /= m;
  return *this;
}

constexpr inline bool operator==(const TVector4D &v1, const TVector4D &v2) {
  return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
}

constexpr inline bool operator!=(const TVector4D &v1, const TVector4D &v2) {
  return !(v1 == v2);
}

constexpr inline const TVector4D operator+(const TVector4D &v1,
                                           const TVector4D &v2) {
  return TVector4D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

constexpr inline const TVector4D operator-(const TVector4D &v1,
                                           const TVector4D &v2) {
  return TVector4D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

constexpr inline const TVector4D operator*(float m, const TVector4D &vector) {
  return TVector4D(vector.x * m, vector.y * m, vector.z * m, vector.w * m);
}

constexpr inline const TVector4D operator*(const TVector4D &vector, float m) {
  return TVector4D(vector.x * m, vector.y * m, vector.z * m, vector.w * m);
}

constexpr inline const TVector4D operator-(const TVector4D &vector) {
  return TVector4D(-vector.x, -vector.y, -vector.z, -vector.w);
}

constexpr inline const TVector4D operator/(const TVector4D &vector, float m) {
  return TVector4D(vector.x / m, vector.y / m, vector.z / m, vector.w / m);
}

#endif // TVECTOR4D_H
