#ifndef TDRAW_H
#define TDRAW_H
#include "tmatrix4x4.h"
#include "tmodel.h"
#include "tvector4d.h"
#include <utility>
class TDraw {
public:
  TDraw();
  void bresenhamLine(const TPoint &p1, const TPoint &p2, unsigned int *img,
                     const TPoint &resolution);
  void bresenhamLine(const TVector4D &p1, const TVector4D &p2,
                     unsigned int *img, const TPoint &resolution);
  void explicitLine(const TPoint &p1, const TPoint &p2, int *img,
                    const TPoint &resolution);
  void wireframe(unsigned int *data, const TPoint &resolution,
                 const TModel &model);

private:
  int a, r, g, b, x, y;
  enum class Octant {
    first = 1,
    second = 2,
    third = 3,
    fourth = 4,
    fifth = 5,
    sixth = 6,
    seventh = 7,
    eighth = 8
  };
  unsigned int getColor(int a, int r, int g, int b) const;
  unsigned int getColor(int r, int g, int b) const;
  bool isInImage(const TPoint &p, const TPoint &resolution) const;
  Octant toFirstOctant(TPoint &p1, TPoint &p2);
};

#endif // DRAWLINE_H
