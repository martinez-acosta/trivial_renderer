#include "tdraw.h"
#include <algorithm>
#include <cmath>
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
  // if (!isInImage(p, res) && !isInImage(q, res))
  // return;
  // El punto p (punto inicial) debe estar más a la izquierda que
  // el punto q
  if (q.x < p.x) {
    std::swap(q.x, p.x);
    std::swap(q.y, p.y);
  }

  // Si es el mismo punto, lo dibujamos y salimos
  /* if (p == q && isInImage(p, res)) {
     img[4 * res.x * p.y + 4 * p.x + 0] = r;
     img[4 * res.x * p.y + 4 * p.x + 1] = g;
     img[4 * res.x * p.y + 4 * p.x + 2] = b;
     img[4 * res.x * p.y + 4 * p.x + 3] = a;
     return;
   }*/

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

void homogeneusDivide(TVector4D &v) {
  if (v.w != 1.0) {
    v.x /= v.w;
    v.y /= v.w;
    v.z /= v.w;
  }
}
void TDraw::wireframe(std::vector<unsigned char> &data,
                      const TPoint &resolution, TModel &model) {
  TVector4D w0, w1, w2, w3;
  TVector4D camVector0, camVector1, camVector2, camVector3;
  // Matriz de cambio de base: Espacio global a espacio de cámara
  TMatrix4x4 MworldToCam;
  TMatrix4x4 MProj;
  TPoint p0, p1, p2, p3;
  float aspectRatio = model.info.cam.aspectRatio;
  MworldToCam.fill(0);
  MProj.fill(0);
  // Asignamos cámara
  MProj(0, 0) = 1;
  MProj(1, 1) = 1;
  MProj(2, 2) = 1;
  MProj(3, 3) = 1;

  MworldToCam(0, 0) = 1;
  MworldToCam(1, 1) = 1;
  MworldToCam(2, 2) = 1;
  MworldToCam(3, 3) = 1;
  MworldToCam(0, 3) = model.info.cam.pos.x;
  MworldToCam(1, 3) = model.info.cam.pos.y;
  MworldToCam(2, 3) = model.info.cam.pos.z;

  // Asignamos perspectiva y frustum
  model.setPerspective();
  model.setFrustum(MProj);

  for (auto face : model.faces_for_vertexes) {

    w0 = model.list_vertexes.at(face.v1 - 1);
    w1 = model.list_vertexes.at(face.v2 - 1);
    w2 = model.list_vertexes.at(face.v3 - 1);
    if (face.n_faces == 4)
      w3 = model.list_vertexes.at(face.v4 - 1);

    // Cambio de base: Global a espacio de la cámara

    camVector0 = w0 * MworldToCam;
    camVector1 = w1 * MworldToCam;
    camVector2 = w2 * MworldToCam;

    homogeneusDivide(camVector0);
    homogeneusDivide(camVector1);
    homogeneusDivide(camVector2);

    // multPointMatrix(w0, camVector0, MworldToCam);
    if (face.n_faces == 4)
      camVector3 = w3 * MworldToCam;

    // Proyección en perspectiva
    w0 = camVector0 * MProj;
    w1 = camVector1 * MProj;
    w2 = camVector2 * MProj;

    homogeneusDivide(w0);
    homogeneusDivide(w1);
    homogeneusDivide(w2);

    if (face.n_faces == 4) {
      w3 = camVector3 * MProj;
    }
    // Comprobamos que cada punto esté dentro del cubo unitario
    if (w0.x < -aspectRatio || w0.x > aspectRatio || w0.y < -1 || w0.y > 1)
      continue;
    if (w1.x < -aspectRatio || w1.x > aspectRatio || w1.y < -1 || w1.y > 1)
      continue;
    if (w2.x < -aspectRatio || w2.x > aspectRatio || w2.y < -1 || w2.y > 1)
      continue;
    if (face.n_faces == 4)
      if (w3.x < -aspectRatio || w3.x > aspectRatio || w3.y < -1 || w3.y > 1)
        continue;

    // Cambiamos a espacio de raster
    p0.x = std::min((u_int32_t)resolution.x - 1,
                    (u_int32_t)((w0.x + 1) * 0.5 * resolution.x));
    p0.y = std::min((u_int32_t)resolution.y - 1,
                    (u_int32_t)((1 - (w0.y + 1) * 0.5) * resolution.y));

    p1.x = std::min((u_int32_t)resolution.x - 1,
                    (u_int32_t)((w1.x + 1) * 0.5 * resolution.x));
    p1.y = std::min((u_int32_t)resolution.y - 1,
                    (u_int32_t)((1 - (w1.y + 1) * 0.5) * resolution.y));

    p2.x = std::min((u_int32_t)resolution.x - 1,
                    (u_int32_t)((w2.x + 1) * 0.5 * resolution.x));
    p2.y = std::min((u_int32_t)resolution.y - 1,
                    (u_int32_t)((1 - (w2.y + 1) * 0.5) * resolution.y));

    if (face.n_faces == 4) {
      p3.x = std::min((u_int32_t)resolution.x - 1,
                      (u_int32_t)((w3.x + 1) * 0.5 * resolution.x));
      p3.y = std::min((u_int32_t)resolution.y - 1,
                      (u_int32_t)((1 - (w3.y + 1) * 0.5) * resolution.y));
    }

    // p0 con p1
    bresenhamLine(p0, p1, data, resolution);
    // p1 con p2
    bresenhamLine(p1, p2, data, resolution);
    // p2 con p0
    bresenhamLine(p2, p0, data, resolution);

    switch (face.n_faces) {
    case 3:
      break;
    case 4:
      // p0 con p1
      bresenhamLine(p0, p1, data, resolution);
      // p1 con p2
      bresenhamLine(p1, p2, data, resolution);
      // p2 con p0
      bresenhamLine(p2, p3, data, resolution);
      // p3 con p0
      bresenhamLine(p3, p0, data, resolution);
      break;
    }
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
                       const TPoint &resolution, TModel &model) {
  TVector4D w0, w1, w2, w3;
  TVector4D camVector0, camVector1, camVector2, camVector3;
  // Matriz de cambio de base: Espacio global a espacio de cámara
  TMatrix4x4 MworldToCam;
  TMatrix4x4 MProj;
  TPoint p0, p1, p2, p3;
  float aspectRatio = model.info.cam.aspectRatio;
  MworldToCam.fill(0);
  MProj.fill(0);
  // Asignamos cámara
  MProj(0, 0) = 1;
  MProj(1, 1) = 1;
  MProj(2, 2) = 1;
  MProj(3, 3) = 1;

  MworldToCam(0, 0) = 1;
  MworldToCam(1, 1) = 1;
  MworldToCam(2, 2) = 1;
  MworldToCam(3, 3) = 1;
  MworldToCam(0, 3) = model.info.cam.pos.x;
  MworldToCam(1, 3) = model.info.cam.pos.y;
  MworldToCam(2, 3) = model.info.cam.pos.z;

  // Asignamos perspectiva y frustum
  model.setPerspective();
  model.setFrustum(MProj);
  TVector3D tmp3D, view = {0, -10, -20}, normal, v1, v2;
  TVector4D tmp4D;
  float res;
  for (auto face : model.faces_for_vertexes) {

    w0 = model.list_vertexes.at(face.v1 - 1);
    w1 = model.list_vertexes.at(face.v2 - 1);
    w2 = model.list_vertexes.at(face.v3 - 1);
    if (face.n_faces == 4)
      w3 = model.list_vertexes.at(face.v4 - 1);

    // Cambio de base: Global a espacio de la cámara

    camVector0 = w0 * MworldToCam;
    camVector1 = w1 * MworldToCam;
    camVector2 = w2 * MworldToCam;

    homogeneusDivide(camVector0);
    homogeneusDivide(camVector1);
    homogeneusDivide(camVector2);

    // multPointMatrix(w0, camVector0, MworldToCam);
    if (face.n_faces == 4)
      camVector3 = w3 * MworldToCam;

    // Proyección en perspectiva
    w0 = camVector0 * MProj;
    w1 = camVector1 * MProj;
    w2 = camVector2 * MProj;

    homogeneusDivide(w0);
    homogeneusDivide(w1);
    homogeneusDivide(w2);

    if (face.n_faces == 4) {
      w3 = camVector3 * MProj;
    }
    // Comprobamos que cada punto esté dentro del cubo unitario
    if (w0.x < -aspectRatio || w0.x > aspectRatio || w0.y < -1 || w0.y > 1)
      continue;
    if (w1.x < -aspectRatio || w1.x > aspectRatio || w1.y < -1 || w1.y > 1)
      continue;
    if (w2.x < -aspectRatio || w2.x > aspectRatio || w2.y < -1 || w2.y > 1)
      continue;
    if (face.n_faces == 4)
      if (w3.x < -aspectRatio || w3.x > aspectRatio || w3.y < -1 || w3.y > 1)
        continue;

    // Cambiamos a espacio de raster
    p0.x = std::min((u_int32_t)resolution.x - 1,
                    (u_int32_t)((w0.x + 1) * 0.5 * resolution.x));
    p0.y = std::min((u_int32_t)resolution.y - 1,
                    (u_int32_t)((1 - (w0.y + 1) * 0.5) * resolution.y));

    p1.x = std::min((u_int32_t)resolution.x - 1,
                    (u_int32_t)((w1.x + 1) * 0.5 * resolution.x));
    p1.y = std::min((u_int32_t)resolution.y - 1,
                    (u_int32_t)((1 - (w1.y + 1) * 0.5) * resolution.y));

    p2.x = std::min((u_int32_t)resolution.x - 1,
                    (u_int32_t)((w2.x + 1) * 0.5 * resolution.x));
    p2.y = std::min((u_int32_t)resolution.y - 1,
                    (u_int32_t)((1 - (w2.y + 1) * 0.5) * resolution.y));

    if (face.n_faces == 4) {
      p3.x = std::min((u_int32_t)resolution.x - 1,
                      (u_int32_t)((w3.x + 1) * 0.5 * resolution.x));
      p3.y = std::min((u_int32_t)resolution.y - 1,
                      (u_int32_t)((1 - (w3.y + 1) * 0.5) * resolution.y));
    }
    // p0 con p1
    tmp4D.x = w0.x - view.x;
    tmp4D.y = w0.y - view.y;
    tmp4D.z = w0.z - view.z;

    v1.x = w1.x - w0.x;
    v1.y = w1.y - w0.y;
    v1.z = w1.z - w0.z;

    v2.x = w2.x - w0.x;
    v2.y = w2.y - w0.y;
    v2.z = w2.z - w0.z;
    normal = normal.crossProduct(v1, v2);
    tmp3D = {tmp4D.x, tmp4D.y, tmp4D.z};
    res = tmp3D.dotProduct(normal, view);

    if (res >= 0) {
      bresenhamLine(p0, p1, data, resolution);
      // p1 con p2
      bresenhamLine(p1, p2, data, resolution);
      // p2 con p0
      bresenhamLine(p2, p0, data, resolution);
    }
    switch (face.n_faces) {
    case 3:
      break;
    case 4:
      // p0 con p1
      bresenhamLine(p0, p1, data, resolution);
      // p1 con p2
      bresenhamLine(p1, p2, data, resolution);
      // p2 con p0
      bresenhamLine(p2, p3, data, resolution);
      // p3 con p0
      bresenhamLine(p3, p0, data, resolution);
      break;
    }
  }
}

void TDraw::zBuffer(std::vector<unsigned char> &data,
                    std::vector<float> &depthBuffer, const TPoint &resolution,
                    TModel &model) {
  TVector4D w0, w1, w2, w3;
  TVector4D camVector0, camVector1, camVector2, camVector3;
  // Matriz de cambio de base: Espacio global a espacio de cámara
  TMatrix4x4 MworldToCam;
  TMatrix4x4 MProj;
  TPoint p0, p1, p2, p3;
  float aspectRatio = model.info.cam.aspectRatio;
  MworldToCam.fill(0);
  MProj.fill(0);
  // Asignamos cámara
  MProj(0, 0) = 1;
  MProj(1, 1) = 1;
  MProj(2, 2) = 1;
  MProj(3, 3) = 1;

  MworldToCam(0, 0) = 1;
  MworldToCam(1, 1) = 1;
  MworldToCam(2, 2) = 1;
  MworldToCam(3, 3) = 1;
  MworldToCam(0, 3) = model.info.cam.pos.x;
  MworldToCam(1, 3) = model.info.cam.pos.y;
  MworldToCam(2, 3) = model.info.cam.pos.z;

  // Asignamos perspectiva y frustum
  model.setPerspective();
  model.setFrustum(MProj);
  // Inicializamos el z buffer
  for (unsigned y = 0; y < resolution.y; y++)
    for (unsigned x = 0; x < resolution.x; x++) {
      depthBuffer[resolution.x * y + x] = model.info.cam.far;
    }

  TVector3D tmp3D, view = {0, -10, -20}, normal, v1, v2;
  TVector4D tmp4D;
  float res;
  for (auto face : model.faces_for_vertexes) {

    w0 = model.list_vertexes.at(face.v1 - 1);
    w1 = model.list_vertexes.at(face.v2 - 1);
    w2 = model.list_vertexes.at(face.v3 - 1);
    if (face.n_faces == 4)
      w3 = model.list_vertexes.at(face.v4 - 1);

    // Cambio de base: Global a espacio de la cámara

    camVector0 = w0 * MworldToCam;
    camVector1 = w1 * MworldToCam;
    camVector2 = w2 * MworldToCam;

    homogeneusDivide(camVector0);
    homogeneusDivide(camVector1);
    homogeneusDivide(camVector2);

    // multPointMatrix(w0, camVector0, MworldToCam);
    if (face.n_faces == 4)
      camVector3 = w3 * MworldToCam;

    // Proyección en perspectiva
    w0 = camVector0 * MProj;
    w1 = camVector1 * MProj;
    w2 = camVector2 * MProj;

    homogeneusDivide(w0);
    homogeneusDivide(w1);
    homogeneusDivide(w2);

    if (face.n_faces == 4) {
      w3 = camVector3 * MProj;
    }
    // Comprobamos que cada punto esté dentro del cubo unitario
    if (w0.x < -aspectRatio || w0.x > aspectRatio || w0.y < -1 || w0.y > 1)
      continue;
    if (w1.x < -aspectRatio || w1.x > aspectRatio || w1.y < -1 || w1.y > 1)
      continue;
    if (w2.x < -aspectRatio || w2.x > aspectRatio || w2.y < -1 || w2.y > 1)
      continue;
    if (face.n_faces == 4)
      if (w3.x < -aspectRatio || w3.x > aspectRatio || w3.y < -1 || w3.y > 1)
        continue;

    tmp4D.x = w0.x - view.x;
    tmp4D.y = w0.y - view.y;
    tmp4D.z = w0.z - view.z;

    v1.x = w1.x - w0.x;
    v1.y = w1.y - w0.y;
    v1.z = w1.z - w0.z;

    v2.x = w2.x - w0.x;
    v2.y = w2.y - w0.y;
    v2.z = w2.z - w0.z;
    normal = normal.crossProduct(v1, v2);
    tmp3D = {tmp4D.x, tmp4D.y, tmp4D.z};
    res = tmp3D.dotProduct(normal, view);

    if (res >= 0) {
      fillTriangle(w0, w1, w2, data, depthBuffer, resolution);
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
void TDraw::fillTriangle(const TVector4D &p1, const TVector4D &p2,
                         const TVector4D &p3, std::vector<unsigned char> &img,
                         std::vector<float> &depthBuffer, const TPoint &res) {
  TVector4D q0{p1};
  TVector4D q1{p2};
  TVector4D q2{p3};
  TVector4D p;

  const TVector3D c0 = {1, 0, 0};
  const TVector3D c1 = {0, 1, 0};
  const TVector3D c2 = {0, 0, 1};
  TPoint min, max;

  // Cambiamos a espacio de raster
  q0.x = std::min((u_int32_t)res.x - 1, (u_int32_t)((q0.x + 1) * 0.5 * res.x));
  q0.y = std::min((u_int32_t)res.y - 1,
                  (u_int32_t)((1 - (q0.y + 1) * 0.5) * res.y));

  q1.x = std::min((u_int32_t)res.x - 1, (u_int32_t)((q1.x + 1) * 0.5 * res.x));
  q1.y = std::min((u_int32_t)res.y - 1,
                  (u_int32_t)((1 - (q1.y + 1) * 0.5) * res.y));

  q2.x = std::min((u_int32_t)res.x - 1, (u_int32_t)((q2.x + 1) * 0.5 * res.x));
  q2.y = std::min((u_int32_t)res.y - 1,
                  (u_int32_t)((1 - (q2.y + 1) * 0.5) * res.y));

  // Calculamos coordenadas que acotan al triángulo
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
      w0 /= area;
      w1 /= area;
      w2 /= area;
      if (w0 >= 0 && w1 >= 0 && w2 >= 0) {

        r0 = w0 * c0[0] + w1 * c1[0] + w2 * c2[0];
        g0 = w0 * c0[1] + w1 * c1[1] + w2 * c2[1];
        b0 = w0 * c0[2] + w1 * c1[2] + w2 * c2[2];
        /*q0.z = 1 / q0.z;
        q1.z = 1 / q1.z;
        q2.z = 1 / q2.z;*/

        float oneOverZ = q0.z * w0 + q1.z * w1 + q2.z * w2;
        float z = 1 / oneOverZ;
        if (z < depthBuffer[y * res.x + x]) {
          depthBuffer[y * res.x + x] = z;

          if (isInImage(TPoint(x, y), res)) {
            img[4 * res.x * y + 4 * x + 0] = r0 * 255;
            img[4 * res.x * y + 4 * x + 1] = g0 * 255;
            img[4 * res.x * y + 4 * x + 2] = b0 * 255;
            img[4 * res.x * y + 4 * x + 3] = a;
          }
        }
      }
    }
}
