#include "tvector3d.h"
TVector3D::TVector3D() : x(0.0f), y(0.0f), z(0.0f) {}

TVector3D::TVector3D(float x, float y, float z) : x(x), y(y), z(z) {}

TVector3D::TVector3D(const TPoint &p) : x(p.x), y(p.y), z(0.0f) {}

constexpr float TVector3D::length() const {
  return std::sqrt(x * x + y * y + z * z);
}

constexpr float TVector3D::lengthSquared() const {
  return x * x + y * y + z * z;
}

constexpr bool TVector3D::isCeroVector() const {
  return x == 0.0f && y == 0.0f && z == 0.0f;
}

TPoint TVector3D::toPoint() const {
  return TPoint(static_cast<int>(std::round(x)),
                static_cast<int>(std::round(y)));
}

constexpr float TVector3D::dotProduct(const TVector3D &v1,
                                      const TVector3D &v2) const {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

TVector3D TVector3D::crossProduct(const TVector3D &v1,
                                  const TVector3D &v2) const {
  return TVector3D(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
                   v1.x * v2.y - v1.y * v2.x);
}

TVector3D TVector3D::normalize() const {
  return TVector3D(x / length(), y / length(), z / length());
}
