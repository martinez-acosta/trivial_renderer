#ifndef TMODEL_H
#define TMODEL_H
#include "tvector3d.h"
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
  void readObjFile(const std::string &filename);
  void readRawFile(const std::string &filename);
  std::vector<TVector4D> list_vertexes;
  std::vector<TVector3D> list_textures;
  std::vector<TVector3D> list_normals;
  std::vector<TVector3D> space_vertexes;
  std::vector<struct face> faces_for_vertexes;
  std::vector<struct face> faces_for_textures;
  std::vector<struct face> faces_for_normals;

private:
  std::string name;
  void getVertex(std::string &line);
  void getFace(std::string &line);
};

#endif // TMODEL_H
