#include "tdraw.h"

TDraw::TDraw() : a(255), r(0), g(0), b(0), x(0), y(0) {}

bool TDraw::isInImage(const TPoint &p, const TPoint &resolution) const {
  return p.x >= 0 && p.x < resolution.x && p.y >= 0 && p.y < resolution.y;
}
void TDraw::bresenhamLine(const TVector4D &p1, const TVector4D &p2,
                          unsigned int *img, const TPoint &res) {
  TPoint p{static_cast<int>(std::round(p1.x)),
           static_cast<int>(std::round(p1.y))};

  TPoint q{static_cast<int>(std::round(p2.x)),
           static_cast<int>(std::round(p2.y))};
  bresenhamLine(p, q, img, res);
}

unsigned int TDraw::getColor(int a, int r, int g, int b) const {
  unsigned int color = ((a << 24) & 0xff000000) | ((r << 16) & 0x00ff0000) |
                       ((g << 8) & 0x0000ff00) | (b & 0x000000ff);
  return color;
}

unsigned int TDraw::getColor(int r, int g, int b) const {
  unsigned int color = (0xff000000) | ((r << 16) & 0x00ff0000) |
                       ((g << 8) & 0x0000ff00) | (b & 0x000000ff);
  return color;
}

void TDraw::bresenhamLine(const TPoint &p1, const TPoint &p2, unsigned int *img,
                          const TPoint &res) {

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
  if (isInImage(p, res))
    img[res.x * p.y + p.x] = getColor(a, r, g, b);

  if (isInImage(q, res))
    img[res.x * q.y + q.x] = getColor(a, r, g, b);

  // Si es una línea horizontal
  if (p.y == q.y) {

    for (x = p.x; x <= q.x; x++)
      if (isInImage(TPoint(x, p.y), res))
        img[res.x * p.y + x] = getColor(a, r, g, b);
    return;
  }

  // Si es una línea vertical
  if (p.x == q.x) {

    if (p.y > q.y)
      std::swap(p.y, q.y);
    for (y = p.y; y <= q.y; y++)
      if (isInImage(TPoint(p.x, y), res))
        img[res.x * y + q.x] = getColor(a, r, g, b);
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
    if (isInImage(interpolated, res))
      img[res.x * interpolated.y + interpolated.x] = getColor(a, r, g, b);
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
      img[res.x * y + x] = getColor(a, r, g, b);
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

void TDraw::wireframe(unsigned int *data, const TPoint &resolution,
                      const TModel &model) {
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
