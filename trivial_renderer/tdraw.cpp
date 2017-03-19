#include "tdraw.h"

constexpr TDraw::TDraw() : r(255), g(255), b(255), x(0), y(0) {}

constexpr bool TDraw::isInImage(const TPoint &p,
                                const TPoint &resolution) const {
  return p.x >= 0 && p.x < resolution.x && p.y >= 0 && p.y < resolution.y;
}

constexpr void TDraw::bresenhamLine(const TPoint &p1, const TPoint &p2,
                                    int *img, const TPoint &res) {
  TPoint p(p1);
  TPoint q(p2);

  // El punto p (punto inicial) debe estar más a la izquierda que
  // el punto q
  if (q.x > p.x) {
    std::swap(q.x, p.x);
    std::swap(q.y, p.y);
  }

  // Si es el mismo punto, lo dibujamos y salimos
  if (p.y == q.y && p.x == q.x) {
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
  if (isInImage(p, res))
    img[res.x * p.y + p.x] = (r << 16) | (g << 8) | b;

  if (isInImage(q, res))
    img[res.x * q.y + q.x] = (r << 16) | (g << 8) | b;

  // Si es una línea horizontal
  if (p.y == q.y) {

    for (x = p.x; x <= q.x; x++)
      if (isInImage(TPoint(x, p.y), res))
        img[res.x * p.y + x] = (r << 16) | (g << 8) | b;
    return;
  }

  // Si es una línea vertical
  if (p.x == q.x) {

    if (p.y > q.y)
      std::swap(p.y, q.y);
    for (y = p.y; y <= q.y; y++)
      if (isInImage(TPoint(p.x, y), res))
        img[res.x * y + q.x] = (r << 16) | (g << 8) | b;
    return;
  }

  // Trasladamos el segmento de línea a que empiece en el origen y tenga una
  // pendiente 0 <= m <= 1
  Octant octant = toFirstOctant(p, q);
  TPoint initial{p};
  TPoint delta{p - q};
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
    if (isInImage(interpolated, res))
      img[res.x * interpolated.y + interpolated.x] =
          (r << 16) | (g << 8) | (b & 0xff);
  }
}

constexpr void TDraw::explicitLine(const TPoint &p1, const TPoint &p2, int *img,
                                   const TPoint &res) {
  float m = (p2.y - p1.y) / (p2.x - p1.x);
  float k = 0;
  k = p1.y - m * p1.x;
  for (int x = p1.x; x <= p2.x; x++) {
    y = static_cast<int>(std::round(m * x + k));
    if (isInImage(TPoint(x, y), res))
      img[res.x * y + x] = (r << 16) | (g << 8) | (b & 0xff);
  }
}

TDraw::Octant TDraw::toFirstOctant(TPoint &p1, TPoint &p2) {
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
  p1 -= delta;
  p2 -= delta;

  // El vector p está en la posición (0,0,0,1)
  // Rotamos el segmento de línea al primer octante
  switch (octant) {
  case Octant::first:
    break;
  case Octant::second:
    std::swap(p1.x, p2.y);
    break;
  case Octant::third:
    p2.x *= -1;
    std::swap(p1.x, p2.y);
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
