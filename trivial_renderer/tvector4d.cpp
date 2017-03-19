#include "tvector4d.h"
constexpr TVector4D::TVector4D() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

constexpr TVector4D::TVector4D(float x, float y, float z)
    : x(x), y(y), z(z), w(0.0f) {}

constexpr TVector4D::TVector4D(float x, float y, float z, float w)
    : x(x), y(y), z(z), w(w) {}

constexpr TVector4D::TVector4D(const TVector3D &vector)
    : x(vector.x), y(vector.y), z(vector.z), w(0.0f) {}

constexpr TVector4D::TVector4D(const TVector3D &vector, float w)
    : x(vector.x), y(vector.y), z(vector.z), w(w) {}

constexpr TVector4D::TVector4D(const TPoint &p)
    : x(p.x), y(p.y), z(0.0f), w(0.0f) {}

constexpr float TVector4D::length() const {
  return std::sqrt(x * x + y * y + z * z + w * w);
}

constexpr float TVector4D::lengthSquared() const {
  return x * x + y * y + z * z + w * w;
}

constexpr bool TVector4D::isCeroVector() const {
  return x == 0.0f && y == 0.0f && z == 0.0f && w == 0.0f;
}

constexpr TPoint TVector4D::toPoint() const {
  return TPoint(static_cast<int>(std::round(x)),
                static_cast<int>(std::round(y)));
}

constexpr float TVector4D::dotProduct(const TVector4D &v1,
                                      const TVector4D &v2) const {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

constexpr TVector4D TVector4D::normalize() const {
  return TVector4D(x / length(), y / length(), z / length(), w / length());
}
