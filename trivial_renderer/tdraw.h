#ifndef TDRAW_H
#define TDRAW_H
#include "tmatrix4x4.h"
#include <utility>
class TDraw {
public:
  constexpr TDraw();
  constexpr void bresenhamLine(const TPoint &p1, const TPoint &p2, int *img,
                               const TPoint &resolution);
  constexpr void explicitLine(const TPoint &p1, const TPoint &p2, int *img,
                              const TPoint &resolution);

private:
  int r, g, b, x, y;
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

  constexpr bool isInImage(const TPoint &p, const TPoint &resolution) const;
  Octant toFirstOctant(TPoint &p1, TPoint &p2);
};

#endif // DRAWLINE_H
