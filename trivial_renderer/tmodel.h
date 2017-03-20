#ifndef TMODEL_H
#define TMODEL_H
#include "tvector3d.h"
#include "tvector4d.h"
#include <string>
#include <vector>
class TModel {
public:
  TModel();
  void readObjFile(const std::string &filename);
  void readRawFile(const std::string &filename);

private:
  struct face {
    int v1;
    int v2;
    int v3;
  };
  std::vector<TVector4D> vertexes;
  std::vector<TVector3D> textures;
  std::vector<TVector3D> normal_vertexes;
  std::vector<TVector3D> space_vertexes;
  std::vector<struct face> faces_vertexes;
  std::vector<struct face> faces_textures;
  std::vector<struct face> faces_normals;
  void getVertex(std::string &line);
  void getFace(std::string &line);
};

#endif // TMODEL_H
