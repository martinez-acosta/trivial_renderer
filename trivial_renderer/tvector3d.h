#ifndef TVector3D_H
#define TVector3D_H
#include "tpoint.h"
#include <cmath>
class TVector3D {
public:
  float x, y, z;
  // Constructores
  constexpr TVector3D();
  constexpr TVector3D(float x, float y, float z);
  constexpr explicit TVector3D(const TPoint &p);

  // Métodos
  constexpr float length() const;
  constexpr float lengthSquared() const;
  constexpr bool isCeroVector() const;
  constexpr TPoint toPoint() const;
  constexpr TVector3D normalize() const;
  constexpr float dotProduct(const TVector3D &v1, const TVector3D &v2) const;

  constexpr TVector3D crossProduct(const TVector3D &v1,
                                   const TVector3D &v2) const;

  // Operadores:
  float &operator[](int i);
  float operator[](int i) const;
  TVector3D &operator+=(const TVector3D &vector);
  TVector3D &operator-=(const TVector3D &vector);
  TVector3D &operator*=(float m);
  TVector3D &operator/=(float m);

  // Si dos vectores son iguales
  constexpr friend inline bool operator==(const TVector3D &v1,
                                          const TVector3D &v2);
  // Si dos vectores son diferentes
  constexpr friend inline bool operator!=(const TVector3D &v1,
                                          const TVector3D &v2);
  // Adición de vectores
  constexpr friend inline const TVector3D operator+(const TVector3D &v1,
                                                    const TVector3D &v2);
  constexpr friend inline const TVector3D operator-(const TVector3D &v1,
                                                    const TVector3D &v2);
  // Producto por escalar
  constexpr friend inline const TVector3D operator*(float m,
                                                    const TVector3D &vector);
  constexpr friend inline const TVector3D operator*(const TVector3D &vector,
                                                    float m);
  // Producto por el escalar -1
  constexpr friend inline const TVector3D operator-(const TVector3D &vector);
  // División por escalar
  constexpr friend inline const TVector3D operator/(const TVector3D &vector,
                                                    float m);

private:
};

constexpr inline TVector3D::TVector3D() : x(0.0f), y(0.0f), z(0.0f) {}

constexpr inline TVector3D::TVector3D(float x, float y, float z)
    : x(x), y(y), z(z) {}

constexpr inline TVector3D::TVector3D(const TPoint &p)
    : x(p.getX()), y(p.getY()), z(0.0f) {}

constexpr inline float TVector3D::length() const {
  return std::sqrt(x * x + y * y + z * z);
}

constexpr inline float TVector3D::lengthSquared() const {
  return x * x + y * y + z * z;
}

constexpr inline bool TVector3D::isCeroVector() const {
  return x == 0.0f && y == 0.0f && z == 0.0f;
}

inline float &TVector3D::operator[](int i) {
  switch (i) {
  case 0:
    return x;
  case 1:
    return y;
  case 2:
    return z;
  }
}

inline float TVector3D::operator[](int i) const {
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
  return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z;
}

constexpr inline const TVector3D operator+(const TVector3D &v1,
                                           const TVector3D &v2) {
  return TVector3D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

constexpr inline const TVector3D operator-(const TVector3D &v1,
                                           const TVector3D &v2) {
  return TVector3D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

constexpr inline const TVector3D operator*(float m, const TVector3D &vector) {
  return TVector3D(vector.x * m, vector.y * m, vector.z * m);
}

constexpr inline const TVector3D operator*(const TVector3D &vector, float m) {
  return TVector3D(vector.x * m, vector.y * m, vector.z * m);
}

constexpr inline const TVector3D operator-(const TVector3D &vector) {
  return TVector3D(-vector.x, -vector.y, -vector.z);
}

constexpr inline const TVector3D operator/(const TVector3D &vector, float m) {
  return TVector3D(vector.x / m, vector.y / m, vector.z / m);
}

constexpr inline TPoint TVector3D::toPoint() const {
  return TPoint(static_cast<int>(std::round(x)),
                static_cast<int>(std::round(y)));
}

constexpr inline float TVector3D::dotProduct(const TVector3D &v1,
                                             const TVector3D &v2) const {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

constexpr inline TVector3D TVector3D::crossProduct(const TVector3D &v1,
                                                   const TVector3D &v2) const {
  return TVector3D(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
                   v1.x * v2.y - v1.y * v2.x);
}

constexpr inline TVector3D TVector3D::normalize() const {
  return TVector3D(x / length(), y / length(), z / length());
}

#endif // TVector3D_H
