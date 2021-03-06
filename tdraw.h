#ifndef TDRAW_H
#define TDRAW_H
#include "timage.h"
#include "tmatrix4x4.h"
#include "tmodel.h"
#include "tshading.h"
#include "tvector4d.h"
#include <utility>
#include <vector>
class TDraw {
public:
  TDraw();
  void bresenhamLine(const TPoint &p1, const TPoint &p2,
                     std::vector<unsigned char> &img, const TPoint &resolution);
  void bresenhamLine(const TVector4D &p1, const TVector4D &p2,
                     std::vector<unsigned char> &img, const TPoint &resolution);

  void faceHiding(std::vector<unsigned char> &data, const TPoint &resolution,
                  TModel &model, TPoint &interpolated);
  void zBuffer(std::vector<unsigned char> &data,
               std::vector<float> &depthBuffer, const TPoint &resolution,
               TModel &model, TPoint &interpolated);
  void flatShading(std::vector<unsigned char> &data,
                   std::vector<float> &depthBuffer, const TPoint &resolution,
                   TModel &model, TPoint &interpolated);
  void gourandShading(std::vector<unsigned char> &data,
                      std::vector<float> &depthBuffer, const TPoint &resolution,
                      TModel &model, TPoint &interpolated);
  void phongShading(std::vector<unsigned char> &data,
                    std::vector<float> &depthBuffer, const TPoint &resolution,
                    TModel &model, TPoint &interpolated);
  void bezierSurface(TImage &frame, std::vector<float> &depthBuffer,
                     const TPoint &resolution, TModel &model);
  void bezierCurve(TImage &frame, std::vector<float> &depthBuffer,
                   const TPoint &resolution, TModel &model,
                   struct bezier_curve *curv);
  void ambientLight(std::vector<unsigned char> &data,
                    std::vector<float> &depthBuffer, const TPoint &resolution,
                    TModel &model);
  void explicitLine(const TPoint &p1, const TPoint &p2, int *img,
                    const TPoint &resolution);
  void wireframe(std::vector<unsigned char> &data, const TPoint &resolution,
                 TModel &model, TPoint &interpolated);
  void interpolateTriangle(std::vector<unsigned char> &data,
                           const TPoint &resolution, const TModel &model);

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

  bool isInImage(const TPoint &p, const TPoint &resolution) const;
  Octant toFirstOctant(TPoint &p1, TPoint &p2);
  void fillTriangle(const TVector4D &p1, const TVector4D &p2,
                    const TVector4D &p3, std::vector<unsigned char> &img,
                    const TPoint &resolution);
  void fillTriangle(const TVector4D &p1, const TVector4D &p2,
                    const TVector4D &p3, std::vector<unsigned char> &img,
                    std::vector<float> &depthBuffer, const TPoint &resolution,
                    const TPoint &interpolated);
  void setAmbientLight(const TVector4D &p1, const TVector4D &p2,
                       const TVector4D &p3, std::vector<unsigned char> &img,
                       std::vector<float> &depthBuffer,
                       const TPoint &resolution);
  float areaTriangle(const TVector4D &p1, const TVector4D &p2,
                     const TVector4D &p3);
};

#endif // DRAWLINE_H
