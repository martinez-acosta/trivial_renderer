#ifndef TMODEL_H
#define TMODEL_H
#include "tmatrix4x4.h"
#include "tvector4d.h"
#include <string>
#include <vector>
class TModel {
public:
  struct face {
    int v1;
    int v2;
    int v3;
  };

  TModel(const std::string &filename);
  void rotate(const TVector3D &vector);
  void scale(const TVector3D &vector);
  void translate(const TVector3D &vector);

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
  void readObjFile(const std::string &filename);
  void readRawFile(const std::string &filename);
};

#endif // TMODEL_H
