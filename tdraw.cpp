#include "tdraw.h"
#include <algorithm>
TDraw::TDraw() : a(255), r(0), g(0), b(0), x(0), y(0) {}

bool TDraw::isInImage(const TPoint &p, const TPoint &resolution) const {
  return p.x >= 0 && p.x < resolution.x && p.y >= 0 && p.y < resolution.y;
}
void TDraw::bresenhamLine(const TVector4D &p1, const TVector4D &p2,
                          std::vector<unsigned char> &img, const TPoint &res) {
  TPoint p{static_cast<int>(std::round(p1.x)),
           static_cast<int>(std::round(p1.y))};

  TPoint q{static_cast<int>(std::round(p2.x)),
           static_cast<int>(std::round(p2.y))};
  bresenhamLine(p, q, img, res);
}

void TDraw::bresenhamLine(const TPoint &p1, const TPoint &p2,
                          std::vector<unsigned char> &img, const TPoint &res) {

  TPoint p{p1};
  TPoint q{p2};
  // El punto p (punto inicial) debe estar más a la izquierda que
  // el punto q
  if (q.x < p.x) {
    std::swap(q.x, p.x);
    std::swap(q.y, p.y);
  }

  // Si es el mismo punto, lo dibujamos y salimos
  if (p == q) {
    return;
  }

  // Solo podemos dibujar puntos en el rango {0,(N-1)} donde N = {res_x,res_y}
  // Si el punto final, q,  es igual a res_x o res_y
  if (p.x == res.x)
    p.x--;

  if (p.y == res.y)
    p.y--;

  if (q.x == res.x)
    q.x--;

  if (q.y == res.y)
    q.y--;

  // Dibujamos punto inicial y final
  if (isInImage(p, res)) {
    img[4 * res.x * p.y + 4 * p.x + 0] = r;
    img[4 * res.x * p.y + 4 * p.x + 1] = g;
    img[4 * res.x * p.y + 4 * p.x + 2] = b;
    img[4 * res.x * p.y + 4 * p.x + 3] = a;
  }

  if (isInImage(q, res)) {
    img[4 * res.x * q.y + 4 * q.x + 0] = r;
    img[4 * res.x * q.y + 4 * q.x + 1] = g;
    img[4 * res.x * q.y + 4 * q.x + 2] = b;
    img[4 * res.x * q.y + 4 * q.x + 3] = a;
  }
  // Si es una línea horizontal
  if (p.y == q.y) {

    for (x = p.x; x <= q.x; x++)
      if (isInImage(TPoint(x, p.y), res)) {
        img[4 * res.x * p.y + 4 * x + 0] = r;
        img[4 * res.x * p.y + 4 * x + 1] = g;
        img[4 * res.x * p.y + 4 * x + 2] = b;
        img[4 * res.x * p.y + 4 * x + 3] = a;
      }
    return;
  }

  // Si es una línea vertical
  if (p.x == q.x) {

    if (p.y > q.y)
      std::swap(p.y, q.y);
    for (y = p.y; y <= q.y; y++)
      if (isInImage(TPoint(p.x, y), res)) {
        img[4 * res.x * y + 4 * q.x + 0] = r;
        img[4 * res.x * y + 4 * q.x + 1] = g;
        img[4 * res.x * y + 4 * q.x + 2] = b;
        img[4 * res.x * y + 4 * q.x + 3] = a;
      }
    return;
  }

  // Trasladamos el segmento de línea a que empiece en el origen y tenga una
  // pendiente 0 <= m <= 1
  TPoint initial{p};
  Octant octant = toFirstOctant(p, q);
  TPoint delta{q - p};
  TPoint tmp;
  int o = 2 * (delta.y - delta.x);
  int twoDy = 2 * delta.y;
  int twoDyDx = 2 * (delta.y - delta.x);
  TPoint interpolated;
  // Asignamos el punto inicial
  tmp = p;

  while (tmp.x < q.x) {
    tmp.x++;
    if (o < 0) {
      o += twoDy;
    } else {
      tmp.y++;
      o += twoDyDx;
    }

    // interpolated es el punto que dibujaremos en el framebuffer
    interpolated = tmp;

    switch (octant) {
    case Octant::first:
      break;
    case Octant::second:
      std::swap(interpolated.x, interpolated.y);
      break;
    case Octant::third:
      std::swap(interpolated.x, interpolated.y);
      interpolated.x *= -1;
      break;
    case Octant::fourth:
      interpolated.y *= -1;
      break;
    case Octant::fifth:
      interpolated.x *= -1;
      interpolated.y *= -1;
      break;
    case Octant::sixth:
      std::swap(interpolated.x, interpolated.y);
      interpolated.x *= -1;
      interpolated.y *= -1;
      break;
    case Octant::seventh:
      std::swap(interpolated.x, interpolated.y);
      interpolated.y *= -1;
      break;
    case Octant::eighth:
      interpolated.y *= -1;
      break;
    }
    // Sumamos el traslado inicial
    interpolated += initial;
    // Guardamos el punto en el framebuffer
    if (isInImage(interpolated, res)) {
      img[4 * res.x * interpolated.y + 4 * interpolated.x + 0] = r;
      img[4 * res.x * interpolated.y + 4 * interpolated.x + 1] = g;
      img[4 * res.x * interpolated.y + 4 * interpolated.x + 2] = b;
      img[4 * res.x * interpolated.y + 4 * interpolated.x + 3] = a;
    }
  }
}

void TDraw::explicitLine(const TPoint &p1, const TPoint &p2, int *img,
                         const TPoint &res) {
  float m = (p2.y - p1.y) / (p2.x - p1.x);
  float k = 0;
  k = p1.y - m * p1.x;
  for (int x = p1.x; x <= p2.x; x++) {
    y = static_cast<int>(std::round(m * x + k));
    if (isInImage(TPoint(x, y), res))
      img[4 * res.x * y + 4 * x + 0] = r;
    img[4 * res.x * y + 4 * x + 1] = g;
    img[4 * res.x * y + 4 * x + 2] = b;
    img[4 * res.x * y + 4 * x + 3] = a;
  }
}

TDraw::Octant TDraw::toFirstOctant(TPoint &p1, TPoint &p2) {
  TPoint initial{p1};
  TPoint delta(p2 - p1);
  Octant octant;

  // Calculamos el octante inicial al que pertenece el segmento de línea

  // Cada cuadrante tiene dos octantes

  // Primer cuadrante
  if (delta.x > 0 && delta.y > 0) {

    if (delta.x > delta.y)
      octant = Octant::first;
    else
      octant = Octant::second;
  }

  // Segundo cuadrante
  if (delta.x < 0 && delta.y > 0) {
    if (std::abs(delta.y) > std::abs(delta.x))
      octant = Octant::third;
    else
      octant = Octant::fourth;
  }

  // Tercer cuadrante
  if (delta.x < 0 && delta.y < 0) {

    if (std::abs(delta.x) > std::abs(delta.y))
      octant = Octant::fifth;
    else
      octant = Octant::sixth;
  }

  // Cuarto cuadrante
  if (delta.x > 0 && delta.y < 0) {

    if (std::abs(delta.y) > std::abs(delta.x))
      octant = Octant::seventh;
    else
      octant = Octant::eighth;
  }

  // Trasladamos el segmento de línea a que empiece en el origen
  p1 -= initial;
  p2 -= initial;

  // El vector p1 está en la posición (0,0,0,1)
  // Rotamos el segmento de línea al primer octante
  switch (octant) {
  case Octant::first:
    break;
  case Octant::second:
    std::swap(p2.x, p2.y);
    break;
  case Octant::third:
    p2.x *= -1;
    std::swap(p2.x, p2.y);
    break;
  case Octant::fourth:
    p2.y *= -1;
    break;
  case Octant::fifth:
    p2.y *= -1;
    p2.x *= -1;
    break;
  case Octant::sixth:
    p2.y *= -1;
    p2.x *= -1;
    std::swap(p2.x, p2.y);
    break;
  case Octant::seventh:
    p2.y *= -1;
    std::swap(p2.x, p2.y);
    break;
  case Octant::eighth:
    p2.y *= -1;
    break;
  }
  return octant;
}

void TDraw::wireframe(std::vector<unsigned char> &data,
                      const TPoint &resolution, const TModel &model) {
  TVector4D w0, w1, w2;
  for (auto face : model.faces_for_vertexes) {
    w0 = model.list_vertexes.at(face.v1 - 1);
    w1 = model.list_vertexes.at(face.v2 - 1);
    w2 = model.list_vertexes.at(face.v3 - 1);
    // w0 con w1
    bresenhamLine(w0, w1, data, resolution);
    // w1 con w2
    bresenhamLine(w1, w2, data, resolution);
    // w2 con w0
    bresenhamLine(w2, w0, data, resolution);
  }
}
void TDraw::interpolateTriangle(std::vector<unsigned char> &data,
                                const TPoint &resolution, const TModel &model) {
  TVector4D w0, w1, w2;
  for (auto face : model.faces_for_vertexes) {
    w0 = model.list_vertexes.at(face.v1 - 1);
    w1 = model.list_vertexes.at(face.v2 - 1);
    w2 = model.list_vertexes.at(face.v3 - 1);
    fillTriangle(w0, w1, w2, data, resolution);
  } // super bezier hermit
}

void TDraw::faceHiding(std::vector<unsigned char> &data,
                       const TPoint &resolution, const TModel &model) {
  TVector4D w0, w1, w2, w3;
  TVector3D v1, v2, v3, n0, n1, n2, n, a, b, k1, k2, k3, view;
  int ddd = 0;
  for (auto face : model.faces_for_vertexes) {
    if (ddd == 30)
      break;
    else
      ddd++;
    w0 = model.list_vertexes.at(face.v1 - 1);
    w1 = model.list_vertexes.at(face.v2 - 1);
    w2 = model.list_vertexes.at(face.v3 - 1);

    n0 = model.list_normals.at(face.v1 - 1);
    n1 = model.list_normals.at(face.v2 - 1);
    n2 = model.list_normals.at(face.v3 - 1);

    // Si w0.x está más a la izquierda
    if (w0.x < w1.x && w0.x < w2.x) {

      v1.x = w0.x;
      v1.y = w0.y;
      v1.z = w0.z;
      // Comparamos w1 y w2
      if (w1.x < w2.x) {

        v2.x = w1.x;
        v2.y = w1.y;
        v2.z = w1.z;

        v3.x = w2.x;
        v3.y = w2.y;
        v3.z = w2.z;

      } else {
        v2.x = w2.x;
        v2.y = w2.y;
        v2.z = w2.z;

        v3.x = w1.x;
        v3.y = w1.y;
        v3.z = w1.z;
      }
    } else if (w1.x < w0.x && w1.x < w2.x) {
      v1.x = w1.x;
      v1.y = w1.y;
      v1.z = w1.z;
      if (w0.x < w2.x) {
        v2.x = w0.x;
        v2.y = w0.y;
        v2.z = w0.z;

        v3.x = w2.x;
        v3.y = w2.y;
        v3.z = w2.z;
      } else {
        v2.x = w2.x;
        v2.y = w2.y;
        v2.z = w2.z;

        v3.x = w0.x;
        v3.y = w0.y;
        v3.z = w0.z;
      }

    } else { // w2 está más a la izquierda
      v1.x = w2.x;
      v1.y = w2.y;
      v1.z = w2.z;
      if (w1.x < w0.x) {
        v2.x = w1.x;
        v2.y = w1.y;
        v2.z = w1.z;

        v3.x = w0.x;
        v3.y = w0.y;
        v3.z = w0.z;
      } else {
        v2.x = w0.x;
        v2.y = w0.y;
        v2.z = w0.z;

        v3.x = w1.x;
        v3.y = w1.y;
        v3.z = w1.z;
      }
    }
    //////////////
    /*
    // Comparamos w1 y w2
    if (v1.y < v2.y && v1.y < v3.y) {

      k1 = v1;
      if (v2.y < v3.y) {
        k2 = v2;
        k3 = v3;
      } else {
        k2 = v3;
        k3 = v2;
      }
    } else if (v2.y < v1.y && v2.y < v3.y) {
      k1 = v2;
      if (v1.y < v3.y) {
        k2 = v1;
        k3 = v3;
      } else {
        k2 = v3;
        k3 = v1;
      }
    } else {
      k1 = v3;
      if (v1.y < v2.y) {
        k2 = v1;
        k3 = v2;
      } else {
        k2 = v2;
        k3 = v1;
      }
    }
    ///////////////
    k1 = k1.normalize();
    k2 = k2.normalize();
    k3 = k3.normalize();

    a = k3 - k1;
    b = k2 - k1;*/
    /*
        if (v1.y > v2.y && v1.y > v3.y) { // Si v1.y es mayor

          if (v2.y > v3.y) {
            a = v2 - v1;
            b = v3 - v1;
          } else {
            a = v2 - v1;
            b = v3 - v1;
          }

        } else if (v2.y > v1.y && v2.y > v3.y) { // Si v2.y es mayor

          if (v1.y > v3.y) {
            a = v2 - v1;
            b = v3 - v1;
          } else {
            a = v2 - v1;
            b = v3 - v1;
          }

        } else if (v3.y > v1.y && v3.y > v2.y) { // Si v3.y es mayor
          if (v2.y > v1.y) {
            a = v2 - v1;
            b = v3 - v1;
          } else {
            a = v2 - v1;
            b = v3 - v1;
          }
        }
        n = n.crossProduct(a, b);*/
    /*TVector3D n2;
   */
    /*
        v1.x = w0.x;
        v1.y = w0.y;
        v1.z = w0.z;

        v2.x = w1.x;
        v2.y = w1.y;
        v2.z = w1.z;

        v3.x = w2.x;
        v3.y = w2.y;
        v3.z = w2.z;
    */
    a = v2 - v1;
    b = v3 - v1;

    //    int z = (a.x * b.y) - (a.y * b.x);
    n = n.crossProduct(a, b);
    w3.x = n.x;
    w3.y = n.y;
    w3.z = n.z;
    w3.w = 1;

    n = n.normalize();
    view = {0, 0, 1};
    v1 = v1.normalize();
    // view = v1 - view;
    // int z = n.x * view.x + n.y * view.y + n.z * view.z;

    int z = n0.x * view.x + n0.y * view.y + n0.z * view.z;
    // z >= 0
    if (true) {
      // w0 con w1
      bresenhamLine(w0, w1, data, resolution);
      // w1 con w2
      bresenhamLine(w1, w2, data, resolution);
      // w2 con w0
      bresenhamLine(w2, w0, data, resolution);
      // normal n0
      bresenhamLine(w0, w3, data, resolution);
    }
  }
}

float TDraw::areaTriangle(const TVector4D &p1, const TVector4D &p2,
                          const TVector4D &p3) {
  float res = (p3.x - p1.x) * (p2.y - p1.y) - (p3.y - p1.y) * (p2.x - p1.x);
  return res;
}

void TDraw::fillTriangle(const TVector4D &p1, const TVector4D &p2,
                         const TVector4D &p3, std::vector<unsigned char> &img,
                         const TPoint &res) {
  TVector4D q0{p1};
  TVector4D q1{p2};
  TVector4D q2{p3};
  TVector4D p;

  const TVector3D c0 = {1, 0, 0};
  const TVector3D c1 = {0, 1, 0};
  const TVector3D c2 = {0, 0, 1};
  TPoint min, max;

  // Calculamos coordanadas que acotan al triángulo
  min.x = static_cast<int>(std::min({q0.x, q1.x, q2.x}));
  min.y = static_cast<int>(std::min({q0.y, q1.y, q2.y}));
  max.x = static_cast<int>(std::max({q0.x, q1.x, q2.x}));
  max.y = static_cast<int>(std::max({q0.y, q1.y, q2.y}));
  float r0, g0, b0;
  float area = areaTriangle(q0, q1, q2);
  float w0, w1, w2;
  for (int y = min.y; y < max.y; y++)
    for (int x = min.x; x < max.x; x++) {
      p = {static_cast<float>(x), static_cast<float>(y), 0};
      w0 = areaTriangle(q1, q2, p);
      w1 = areaTriangle(q2, q0, p);
      w2 = areaTriangle(q0, q1, p);
      if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
        w0 /= area;
        w1 /= area;
        w2 /= area;
        r0 = w0 * c0[0] + w1 * c1[0] + w2 * c2[0];
        g0 = w0 * c0[1] + w1 * c1[1] + w2 * c2[1];
        b0 = w0 * c0[2] + w1 * c1[2] + w2 * c2[2];
        if (isInImage(TPoint(x, y), res)) {
          img[4 * res.x * y + 4 * x + 0] = r0 * 255;
          img[4 * res.x * y + 4 * x + 1] = g0 * 255;
          img[4 * res.x * y + 4 * x + 2] = b0 * 255;
          img[4 * res.x * y + 4 * x + 3] = a;
        }
      }
    }
}
