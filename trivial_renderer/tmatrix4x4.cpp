#include "tmatrix4x4.h"

constexpr bool TMatrix4x4::isAffine() const {
  return m[0][3] == 0.0f && m[1][3] == 0.0f && m[2][3] == 0.0f &&
         m[3][3] == 1.0f;
}

constexpr bool TMatrix4x4::isIdentity() const {
  if (m[0][0] != 1.0f || m[0][1] != 0.0f || m[0][2] != 0.0f || m[0][3] != 0.0f)
    return false;
  if (m[1][0] != 0.0f || m[1][1] != 1.0f || m[1][2] != 0.0f || m[1][3] != 0.0f)
    return false;
  if (m[2][0] != 0.0f || m[2][1] != 0.0f || m[2][2] != 1.0f || m[2][3] != 0.0f)
    return false;
  if (m[3][0] != 0.0f || m[3][1] != 0.0f || m[3][2] != 0.0f)
    return false;
  return (m[3][3] == 1.0f);
}

constexpr void TMatrix4x4::setToIdentity() {

  for (auto j = 0; j < 4; j++)
    for (auto i = 0; i < 4; i++)
      m[j][i] = 0.0f;

  m[0][0] = 1.0f;
  m[1][1] = 1.0f;
  m[2][2] = 1.0f;
  m[3][3] = 1.0f;
}

constexpr void TMatrix4x4::fill(float value) {
  for (auto j = 0; j < 4; j++)
    for (auto i = 0; i < 4; i++)
      m[j][i] = value;
}

TVector4D TMatrix4x4::column(int index) const {
  if (index >= 0 && index < 4)
    return TVector4D(m[index][0], m[index][1], m[index][2], m[index][3]);
}

constexpr void TMatrix4x4::setColumn(int index, const TVector4D &value) {
  if (index >= 0 && index < 4) {
    m[index][0] = value.x;
    m[index][1] = value.y;
    m[index][2] = value.z;
    m[index][3] = value.w;
  }
}

TVector4D TMatrix4x4::row(int index) const {
  if (index >= 0 && index < 4)
    return TVector4D(m[0][index], m[1][index], m[2][index], m[3][index]);
}

constexpr void TMatrix4x4::setRow(int index, const TVector4D &value) {
  if (index >= 0 && index < 4) {
    m[0][index] = value.x;
    m[1][index] = value.y;
    m[2][index] = value.z;
    m[3][index] = value.w;
  }
}

constexpr void TMatrix4x4::viewport(const TPoint &p1, const TPoint &p2) {}
