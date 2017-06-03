#ifndef TMODEL_H
#define TMODEL_H
#include "tmatrix4x4.h"
#include "tvector4d.h"
#include <string>
#include <vector>

typedef struct bezier_curve {
  TVector3D p0;
  TVector3D p1;
  TVector3D p2;
  TVector3D p3;
} bezier_curve;

typedef struct hermite_curve {
  TVector3D p0;
  TVector3D p1;
} hermite_curve;

typedef struct bezier_surface {
  struct bezier_curve c0;
  struct bezier_curve c1;
  struct bezier_curve c2;
  struct bezier_curve c3;
} bezier_surface;

typedef struct hermite_surface {
  struct hermite_curve c0;
  struct hermite_curve c1;
  struct hermite_curve c2;
  struct hermite_curve c3;
} hermite_surface;

typedef struct line_segment {
  TPoint p0;
  TPoint p1;
} line_segment;

typedef struct camera {
  // perspectiva
  float angleOfView;
  float aspectRatio;

  // frustrum
  float bottom;
  float top;
  float left;
  float right;
  float near;
  float far;
  TVector3D pos;
} camera;

class TModel {
public:
  struct face {
    int n_faces;
    int v1;
    int v2;
    int v3;
    int v4;
  };
  struct input {
    bool wireframe;
    bool faceHiding;
    bool flatShading;

    bool lightAmbient;
    bool lightDiffuse;
    bool lightSpecular;

    bool phong;
    bool gourand;

    bool bezierCurve;
    bool hermiteCurve;
    bool bezierSurface;
    bool hermiteSurface;

    // Rotación
    float angleX;
    float angleY;
    float angleZ;

    struct line_segment line;
    struct bezier_curve cbezier;
    struct hermite_curve chermite;
    struct bezier_surface bsurface;
    struct hermite_surface hsurface;
    struct camera cam;
    TPoint resolution;
  };
  TModel();
  struct input info;
  void rotate(const TVector3D &vector);
  void scale(const TVector3D &vector);
  void translate(const TVector3D &vector);
  void setPerspective();
  void getInfo(const std::string &name);
  void setFrustum(TMatrix4x4 &MProj);

private:
  friend class TDraw;
  std::string name;
  std::vector<TVector4D> list_vertexes;
  std::vector<TVector3D> list_textures;
  std::vector<TVector3D> list_normals;
  std::vector<TVector3D> space_vertexes;
  std::vector<struct face> faces_for_vertexes;
  std::vector<struct face> faces_for_textures;
  std::vector<struct face> faces_for_normals;

  void getVertex(std::string &line);
  void getFace(std::string &line);
  void getNormal(std::string &line);
  void readObjFile(const std::string &filename);
  void readRawFile(const std::string &filename);
};

#endif // TMODEL_H
