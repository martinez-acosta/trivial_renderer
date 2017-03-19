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
  float &operator[](int i);
  float operator[](int i) const;
  TVector4D &operator+=(const TVector4D &vector);
  TVector4D &operator-=(const TVector4D &vector);
  TVector4D &operator*=(float m);
  TVector4D &operator/=(float m);

  // Si dos vectores son iguales
  constexpr friend inline bool operator==(const TVector4D &v1,
                                          const TVector4D &v2);
  // Si dos vectores son diferentes
  constexpr friend inline bool operator!=(const TVector4D &v1,
                                          const TVector4D &v2);
  // Adición de vectores
  constexpr friend inline const TVector4D operator+(const TVector4D &v1,
                                                    const TVector4D &v2);
  constexpr friend inline const TVector4D operator-(const TVector4D &v1,
                                                    const TVector4D &v2);
  // Producto por escalar
  constexpr friend inline const TVector4D operator*(float m,
                                                    const TVector4D &vector);
  constexpr friend inline const TVector4D operator*(const TVector4D &vector,
                                                    float m);
  // Producto por el escalar -1
  constexpr friend inline const TVector4D operator-(const TVector4D &vector);
  // División por escalar
  constexpr friend inline const TVector4D operator/(const TVector4D &vector,
                                                    float m);

private:
  friend class TVector3D;
  friend class TPoint;
  friend TVector4D operator*(const TVector4D &vector, const TMatrix4x4 &matrix);
  friend TVector4D operator*(const TMatrix4x4 &matrix, const TVector4D &vector);
};

constexpr inline TVector4D::TVector4D() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

constexpr inline TVector4D::TVector4D(float x, float y, float z)
    : x(x), y(y), z(z), w(0.0f) {}

constexpr inline TVector4D::TVector4D(float x, float y, float z, float w)
    : x(x), y(y), z(z), w(w) {}

constexpr inline TVector4D::TVector4D(const TVector3D &vector)
    : x(vector.x), y(vector.y), z(vector.z), w(0.0f) {}

constexpr inline TVector4D::TVector4D(const TVector3D &vector, float w)
    : x(vector.x), y(vector.y), z(vector.z), w(w) {}

constexpr inline TVector4D::TVector4D(const TPoint &p)
    : x(p.getX()), y(p.getY()), z(0.0f), w(0.0f) {}

constexpr inline float TVector4D::length() const {
  return std::sqrt(x * x + y * y + z * z + w * w);
}

constexpr inline float TVector4D::lengthSquared() const {
  return x * x + y * y + z * z + w * w;
}

constexpr inline bool TVector4D::isCeroVector() const {
  return x == 0.0f && y == 0.0f && z == 0.0f && w == 0.0f;
}

inline float &TVector4D::operator[](int i) {
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

inline float TVector4D::operator[](int i) const {
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
  return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z || v1.w != v2.w;
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

constexpr inline TPoint TVector4D::toPoint() const {
  return TPoint(static_cast<int>(std::round(x)),
                static_cast<int>(std::round(y)));
}

constexpr inline float TVector4D::dotProduct(const TVector4D &v1,
                                             const TVector4D &v2) const {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

constexpr inline TVector4D TVector4D::normalize() const {
  return TVector4D(x / length(), y / length(), z / length(), w / length());
}
#endif // TVECTOR4D_H
