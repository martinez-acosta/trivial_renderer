#ifndef TMATRIX4X4_H
#define TMATRIX4X4_H

#include "tvector3d.h"
#include "tvector4d.h"

class TMatrix4x4 {
public:
  // Constructores
  inline TMatrix4x4();
  inline TMatrix4x4(float m11, float m12, float m13, float m14, float m21,
                    float m22, float m23, float m24, float m31, float m32,
                    float m33, float m34, float m41, float m42, float m43,
                    float m44);
  inline explicit TMatrix4x4(const float *values);
  inline TMatrix4x4(const float *values, int cols, int rows);

  // Operadores
  inline const float &operator()(int column, int row) const;
  inline float &operator()(int row, int column);
  inline TMatrix4x4 &operator+=(const TMatrix4x4 &other);
  inline TMatrix4x4 &operator-=(const TMatrix4x4 &other);
  inline TMatrix4x4 &operator*=(const TMatrix4x4 &other);
  inline TMatrix4x4 &operator*=(float m);
  inline TMatrix4x4 &operator/=(float m);

  inline bool operator==(const TMatrix4x4 &matrix) const;
  inline bool operator!=(const TMatrix4x4 &matrix) const;

  friend TMatrix4x4 operator+(const TMatrix4x4 &m1, const TMatrix4x4 &m2);
  friend TMatrix4x4 operator-(const TMatrix4x4 &m1, const TMatrix4x4 &m2);

  friend TMatrix4x4 operator*(const TMatrix4x4 &m1, const TMatrix4x4 &m2);
  friend TVector3D operator*(const TVector3D &vector, const TMatrix4x4 &matrix);
  friend TVector3D operator*(const TMatrix4x4 &matrix, const TVector3D &vector);
  friend TVector4D operator*(const TVector4D &vector, const TMatrix4x4 &matrix);
  friend TVector4D operator*(const TMatrix4x4 &matrix, const TVector4D &vector);

  friend TPoint operator*(const TPoint &point, const TMatrix4x4 &matrix);

  friend TMatrix4x4 operator-(const TMatrix4x4 &matrix);
  friend TPoint operator*(const TMatrix4x4 &matrix, const TPoint &point);
  friend TMatrix4x4 operator*(float m, const TMatrix4x4 &matrix);
  friend TMatrix4x4 operator*(const TMatrix4x4 &matrix, float m);
  friend TMatrix4x4 operator/(const TMatrix4x4 &matrix, float m);

  // Métodos
  bool isAffine() const;
  bool isIdentity() const;
  void setToIdentity();
  void fill(float value);
  double determinant() const;
  TMatrix4x4 inverted(bool *invertible = nullptr) const;
  TMatrix4x4 transposed() const;
  TVector4D column(int index) const;
  void setColumn(int index, const TVector4D &value);
  TVector4D row(int index) const;
  void setRow(int index, const TVector4D &value);

  // Escalar
  void scale(const TVector3D &vector);
  void scale(float x, float y);
  void scale(float x, float y, float z);
  void scale(float m);

  // Trasladar
  void translate(const TVector3D &vector);
  void translate(float x, float y);
  void translate(float x, float y, float z);

  // Rotar
  void rotateX(float angle, const TVector3D &vector);
  void rotateY(float angle, const TVector3D &vector);
  void rotateZ(float angle, const TVector3D &vector);

  void viewport(const TPoint &p1, const TPoint &p2);

  inline float *data() { return *m; };
  inline const float *data() const { return *m; }
  inline const float *constData() const { return *m; }

private:
  float m[4][4];
  explicit TMatrix4x4(int) {}
  friend class TVector3D;
  friend class TVector4D;
};
inline TMatrix4x4::TMatrix4x4(){};
inline TMatrix4x4::TMatrix4x4(float m11, float m12, float m13, float m14,
                              float m21, float m22, float m23, float m24,
                              float m31, float m32, float m33, float m34,
                              float m41, float m42, float m43, float m44) {
  m[0][0] = m11;
  m[0][1] = m21;
  m[0][2] = m31;
  m[0][3] = m41;
  m[1][0] = m12;
  m[1][1] = m22;
  m[1][2] = m32;
  m[1][3] = m42;
  m[2][0] = m13;
  m[2][1] = m23;
  m[2][2] = m33;
  m[2][3] = m43;
  m[3][0] = m14;
  m[3][1] = m24;
  m[3][2] = m34;
  m[3][3] = m44;
}

inline const float &TMatrix4x4::operator()(int column, int row) const {
  if (row >= 0 && row < 4 && column >= 0 && column < 4)
    return m[column][row];
}
inline float &TMatrix4x4::operator()(int column, int row) {
  if (row >= 0 && row < 4 && column >= 0 && column < 4)
    return m[column][row];
}
inline TMatrix4x4 &TMatrix4x4::operator+=(const TMatrix4x4 &other) {

  for (auto j = 0; j < 4; j++)
    for (auto i = 0; i < 4; i++)
      m[j][i] += other.m[j][i];

  return *this;
}

inline TMatrix4x4 &TMatrix4x4::operator-=(const TMatrix4x4 &other) {
  for (auto j = 0; j < 4; j++)
    for (auto i = 0; i < 4; i++)
      m[j][i] -= other.m[j][i];

  return *this;
}

inline TMatrix4x4 &TMatrix4x4::operator*=(const TMatrix4x4 &other) {
  float m0, m1, m2;
  m0 = m[0][0] * other.m[0][0] + m[1][0] * other.m[0][1] +
       m[2][0] * other.m[0][2] + m[3][0] * other.m[0][3];
  m1 = m[0][0] * other.m[1][0] + m[1][0] * other.m[1][1] +
       m[2][0] * other.m[1][2] + m[3][0] * other.m[1][3];
  m2 = m[0][0] * other.m[2][0] + m[1][0] * other.m[2][1] +
       m[2][0] * other.m[2][2] + m[3][0] * other.m[2][3];
  m[3][0] = m[0][0] * other.m[3][0] + m[1][0] * other.m[3][1] +
            m[2][0] * other.m[3][2] + m[3][0] * other.m[3][3];
  m[0][0] = m0;
  m[1][0] = m1;
  m[2][0] = m2;

  m0 = m[0][1] * other.m[0][0] + m[1][1] * other.m[0][1] +
       m[2][1] * other.m[0][2] + m[3][1] * other.m[0][3];
  m1 = m[0][1] * other.m[1][0] + m[1][1] * other.m[1][1] +
       m[2][1] * other.m[1][2] + m[3][1] * other.m[1][3];
  m2 = m[0][1] * other.m[2][0] + m[1][1] * other.m[2][1] +
       m[2][1] * other.m[2][2] + m[3][1] * other.m[2][3];
  m[3][1] = m[0][1] * other.m[3][0] + m[1][1] * other.m[3][1] +
            m[2][1] * other.m[3][2] + m[3][1] * other.m[3][3];
  m[0][1] = m0;
  m[1][1] = m1;
  m[2][1] = m2;

  m0 = m[0][2] * other.m[0][0] + m[1][2] * other.m[0][1] +
       m[2][2] * other.m[0][2] + m[3][2] * other.m[0][3];
  m1 = m[0][2] * other.m[1][0] + m[1][2] * other.m[1][1] +
       m[2][2] * other.m[1][2] + m[3][2] * other.m[1][3];
  m2 = m[0][2] * other.m[2][0] + m[1][2] * other.m[2][1] +
       m[2][2] * other.m[2][2] + m[3][2] * other.m[2][3];
  m[3][2] = m[0][2] * other.m[3][0] + m[1][2] * other.m[3][1] +
            m[2][2] * other.m[3][2] + m[3][2] * other.m[3][3];
  m[0][2] = m0;
  m[1][2] = m1;
  m[2][2] = m2;

  m0 = m[0][3] * other.m[0][0] + m[1][3] * other.m[0][1] +
       m[2][3] * other.m[0][2] + m[3][3] * other.m[0][3];
  m1 = m[0][3] * other.m[1][0] + m[1][3] * other.m[1][1] +
       m[2][3] * other.m[1][2] + m[3][3] * other.m[1][3];
  m2 = m[0][3] * other.m[2][0] + m[1][3] * other.m[2][1] +
       m[2][3] * other.m[2][2] + m[3][3] * other.m[2][3];
  m[3][3] = m[0][3] * other.m[3][0] + m[1][3] * other.m[3][1] +
            m[2][3] * other.m[3][2] + m[3][3] * other.m[3][3];
  m[0][3] = m0;
  m[1][3] = m1;
  m[2][3] = m2;
  return *this;
}

inline TMatrix4x4 &TMatrix4x4::operator*=(float value) {
  for (auto j = 0; j < 4; j++)
    for (auto i = 0; i < 4; i++)
      m[j][i] *= value;
  return *this;
}

inline bool TMatrix4x4::operator==(const TMatrix4x4 &other) const {
  for (auto j = 0; j < 4; j++)
    for (auto i = 0; i < 4; i++)
      if (m[j][i] != other.m[j][i])
        return false;

  return true;
}

inline bool TMatrix4x4::operator!=(const TMatrix4x4 &other) const {
  for (auto j = 0; j < 4; j++)
    for (auto i = 0; i < 4; i++)
      if (m[j][i] == other.m[j][i])
        return false;
  return true;
}

inline TMatrix4x4 operator+(const TMatrix4x4 &m1, const TMatrix4x4 &m2) {
  TMatrix4x4 m(1);
  for (auto j = 0; j < 4; j++)
    for (auto i = 0; i < 4; i++)
      m.m[j][i] = m1.m[j][i] + m2.m[j][i];
  return m;
}

inline TMatrix4x4 operator-(const TMatrix4x4 &m1, const TMatrix4x4 &m2) {
  TMatrix4x4 m(1);
  for (auto j = 0; j < 4; j++)
    for (auto i = 0; i < 4; i++)
      m.m[j][i] = m1.m[j][i] - m2.m[j][i];
  return m;
}

inline TMatrix4x4 operator*(const TMatrix4x4 &m1, const TMatrix4x4 &m2) {
  TMatrix4x4 m(1);
  m.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[1][0] * m2.m[0][1] +
              m1.m[2][0] * m2.m[0][2] + m1.m[3][0] * m2.m[0][3];
  m.m[0][1] = m1.m[0][1] * m2.m[0][0] + m1.m[1][1] * m2.m[0][1] +
              m1.m[2][1] * m2.m[0][2] + m1.m[3][1] * m2.m[0][3];
  m.m[0][2] = m1.m[0][2] * m2.m[0][0] + m1.m[1][2] * m2.m[0][1] +
              m1.m[2][2] * m2.m[0][2] + m1.m[3][2] * m2.m[0][3];
  m.m[0][3] = m1.m[0][3] * m2.m[0][0] + m1.m[1][3] * m2.m[0][1] +
              m1.m[2][3] * m2.m[0][2] + m1.m[3][3] * m2.m[0][3];

  m.m[1][0] = m1.m[0][0] * m2.m[1][0] + m1.m[1][0] * m2.m[1][1] +
              m1.m[2][0] * m2.m[1][2] + m1.m[3][0] * m2.m[1][3];
  m.m[1][1] = m1.m[0][1] * m2.m[1][0] + m1.m[1][1] * m2.m[1][1] +
              m1.m[2][1] * m2.m[1][2] + m1.m[3][1] * m2.m[1][3];
  m.m[1][2] = m1.m[0][2] * m2.m[1][0] + m1.m[1][2] * m2.m[1][1] +
              m1.m[2][2] * m2.m[1][2] + m1.m[3][2] * m2.m[1][3];
  m.m[1][3] = m1.m[0][3] * m2.m[1][0] + m1.m[1][3] * m2.m[1][1] +
              m1.m[2][3] * m2.m[1][2] + m1.m[3][3] * m2.m[1][3];

  m.m[2][0] = m1.m[0][0] * m2.m[2][0] + m1.m[1][0] * m2.m[2][1] +
              m1.m[2][0] * m2.m[2][2] + m1.m[3][0] * m2.m[2][3];
  m.m[2][1] = m1.m[0][1] * m2.m[2][0] + m1.m[1][1] * m2.m[2][1] +
              m1.m[2][1] * m2.m[2][2] + m1.m[3][1] * m2.m[2][3];
  m.m[2][2] = m1.m[0][2] * m2.m[2][0] + m1.m[1][2] * m2.m[2][1] +
              m1.m[2][2] * m2.m[2][2] + m1.m[3][2] * m2.m[2][3];
  m.m[2][3] = m1.m[0][3] * m2.m[2][0] + m1.m[1][3] * m2.m[2][1] +
              m1.m[2][3] * m2.m[2][2] + m1.m[3][3] * m2.m[2][3];

  m.m[3][0] = m1.m[0][0] * m2.m[3][0] + m1.m[1][0] * m2.m[3][1] +
              m1.m[2][0] * m2.m[3][2] + m1.m[3][0] * m2.m[3][3];
  m.m[3][1] = m1.m[0][1] * m2.m[3][0] + m1.m[1][1] * m2.m[3][1] +
              m1.m[2][1] * m2.m[3][2] + m1.m[3][1] * m2.m[3][3];
  m.m[3][2] = m1.m[0][2] * m2.m[3][0] + m1.m[1][2] * m2.m[3][1] +
              m1.m[2][2] * m2.m[3][2] + m1.m[3][2] * m2.m[3][3];
  m.m[3][3] = m1.m[0][3] * m2.m[3][0] + m1.m[1][3] * m2.m[3][1] +
              m1.m[2][3] * m2.m[3][2] + m1.m[3][3] * m2.m[3][3];
  return m;
}

inline TVector3D operator*(const TVector3D &vector, const TMatrix4x4 &matrix) {
  float x, y, z, w;
  x = vector.x * matrix.m[0][0] + vector.y * matrix.m[0][1] +
      vector.z * matrix.m[0][2] + matrix.m[0][3];
  y = vector.x * matrix.m[1][0] + vector.y * matrix.m[1][1] +
      vector.z * matrix.m[1][2] + matrix.m[1][3];
  z = vector.x * matrix.m[2][0] + vector.y * matrix.m[2][1] +
      vector.z * matrix.m[2][2] + matrix.m[2][3];
  w = vector.x * matrix.m[3][0] + vector.y * matrix.m[3][1] +
      vector.z * matrix.m[3][2] + matrix.m[3][3];
  if (w == 1.0f)
    return TVector3D(x, y, z);
  else
    return TVector3D(x / w, y / w, z / w);
}

inline TVector3D operator*(const TMatrix4x4 &matrix, const TVector3D &vector) {
  float x, y, z, w;

  x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] +
      vector.z * matrix.m[2][0] + matrix.m[3][0];
  y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] +
      vector.z * matrix.m[2][1] + matrix.m[3][1];
  z = vector.z * matrix.m[0][2] + vector.y * matrix.m[1][2] +
      vector.z * matrix.m[2][2] + matrix.m[3][2];
  w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] +
      vector.z * matrix.m[2][3] + matrix.m[3][3];
  if (w == 1.0f)
    return TVector3D(x, y, z);
  else
    return TVector3D(x / w, y / w, z / w);
}

inline TVector4D operator*(const TVector4D &vector, const TMatrix4x4 &matrix) {
  float x, y, z, w;
  x = vector.x * matrix.m[0][0] + vector.y * matrix.m[0][1] +
      vector.z * matrix.m[0][2] + vector.w * matrix.m[0][3];
  y = vector.x * matrix.m[1][0] + vector.y * matrix.m[1][1] +
      vector.z * matrix.m[1][2] + vector.w * matrix.m[1][3];
  z = vector.x * matrix.m[2][0] + vector.y * matrix.m[2][1] +
      vector.z * matrix.m[2][2] + vector.w * matrix.m[2][3];
  w = vector.x * matrix.m[3][0] + vector.y * matrix.m[3][1] +
      vector.z * matrix.m[3][2] + vector.w * matrix.m[3][3];

  return TVector4D(x, y, z, w);
}

inline TVector4D operator*(const TMatrix4x4 &matrix, const TVector4D &vector) {
  float x, y, z, w;
  x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] +
      vector.z * matrix.m[2][0] + vector.w * matrix.m[3][0];
  y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] +
      vector.z * matrix.m[2][1] + vector.w * matrix.m[3][1];
  z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] +
      vector.z * matrix.m[2][2] + vector.w * matrix.m[3][2];
  w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] +
      vector.z * matrix.m[2][3] + vector.w * matrix.m[3][3];

  return TVector4D(x, y, z, w);
}

inline TPoint operator*(const TPoint &point, const TMatrix4x4 &matrix) {
  float xin, yin;
  float x, y, w;
  xin = point.x;
  yin = point.y;
  x = xin * matrix.m[0][0] + yin * matrix.m[0][1] + matrix.m[0][3];
  y = xin * matrix.m[1][0] + yin * matrix.m[1][1] + matrix.m[1][3];
  w = xin * matrix.m[3][0] + yin * matrix.m[3][1] + matrix.m[3][3];
  if (w == 1.0f)
    return TPoint(static_cast<int>(round(x)), static_cast<int>(round(y)));
  else
    return TPoint(static_cast<int>(round(x / w)),
                  static_cast<int>(round(y / w)));
}

inline TPoint operator*(const TMatrix4x4 &matrix, const TPoint &point) {
  float xin, yin;
  float x, y, w;
  xin = point.x;
  yin = point.y;
  x = xin * matrix.m[0][0] + yin * matrix.m[1][0] + matrix.m[3][0];
  y = xin * matrix.m[0][1] + yin * matrix.m[1][1] + matrix.m[3][1];
  w = xin * matrix.m[0][3] + yin * matrix.m[1][3] + matrix.m[3][3];
  if (w == 1.0f)
    return TPoint(static_cast<int>(round(x)), static_cast<int>(round(y)));
  else
    return TPoint(static_cast<int>(round(x / w)),
                  static_cast<int>(round(y / w)));
}

inline TMatrix4x4 operator-(const TMatrix4x4 &matrix) {
  TMatrix4x4 m(1);
  for (auto j = 0; j < 4; j++)
    for (auto i = 0; i < 4; i++)
      m.m[j][i] = -matrix.m[j][i];
  return m;
}

inline TMatrix4x4 operator*(float factor, const TMatrix4x4 &matrix) {
  TMatrix4x4 m(1);
  for (auto j = 0; j < 4; j++)
    for (auto i = 0; i < 4; i++)
      m.m[j][i] = matrix.m[j][i] * factor;
  return m;
}

inline TMatrix4x4 operator*(const TMatrix4x4 &matrix, float factor) {
  TMatrix4x4 m(1);
  for (auto j = 0; j < 4; j++)
    for (auto i = 0; i < 4; i++)
      m.m[j][i] = matrix.m[j][i] * factor;
  return m;
}

#endif // TMATRIX4X4_H
