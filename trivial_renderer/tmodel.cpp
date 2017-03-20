#include "tmodel.h"
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <sstream>
#include <string>

TModel::TModel() {}
void TModel::readObjFile(const std::string &filename) {
  std::string line;
  std::ifstream input(filename, std::ios::in);

  if (!input.is_open())
    return;

  while (std::getline(input, line)) {
    if (line[0] == 'v' && line[1] == ' ')
      getVertex(line);
    if (line[0] == 'f' && line[1] == ' ')
      getFace(line);
  }
  input.close();
}

void TModel::getVertex(std::string &line) {
  std::string tmp;
  std::size_t i = 0;
  TVector4D v;
  v.w = 1; // Asignamos w por adelantado ya que es muy probable que no
           // especifiquen ese valor
  std::stringstream ss(line);
  while (ss >> tmp) {
    if (i < 3) {
      v[i] = std::stof(tmp);
    } else if (i == 3) {
      v[i] = std::stof(tmp);
      break;
    }
    i++;
  }
  vertexes.push_back(v);
}
void TModel::getFace(std::string &line) {
  int vertex[3];
  int texture[3];
  int normal[3];
  struct face face_vertex;
  struct face face_texture;
  struct face face_normal;
  bool there_is_texture = false, there_is_normal = false;

  std::vector<std::string> white_space;
  std::vector<std::string> vertex_string;
  boost::split(white_space, line, boost::is_any_of(" "));

  for (std::size_t i = 0; i < white_space.size(); i++) {
    // si no hay "//", puede haber vértice, texturas y normales
    if (white_space.at(i).find("//") == std::string::npos) {
      boost::split(vertex_string, white_space.at(i), boost::is_any_of("/"));
      switch (vertex_string.size()) {
      case 0:
      case 1: // Si solo está el vértice
        vertex[i] = std::stoi(vertex_string.at(0));
        break;
      case 2: // Si también hay textura
        there_is_texture = true;
        vertex[i] = std::stoi(vertex_string.at(0));
        texture[i] = std::stoi(vertex_string.at(1));
        break;
      case 3: // Si hay vectores normales
        there_is_normal = true;
        vertex[i] = std::stoi(vertex_string.at(0));
        texture[i] = std::stoi(vertex_string.at(1));
        normal[i] = std::stoi(vertex_string.at(2));
        break;
      }
      vertex_string.clear();
    } else { // Solo hay vértices y normales
      boost::split(vertex_string, white_space.at(i), boost::is_any_of("//"));
      vertex[i] = std::stoi(vertex_string.at(0));
      texture[i] = std::stoi(vertex_string.at(1));
      there_is_normal = true;
    }
  }
  // Asignamos valores a las estructuras
  face_vertex.v1 = vertex[0];
  face_vertex.v2 = vertex[1];
  face_vertex.v3 = vertex[2];

  if (there_is_texture) {
    face_texture.v1 = texture[0];
    face_texture.v2 = texture[1];
    face_texture.v3 = texture[2];
  }
  if (there_is_normal) {
    face_vertex.v1 = normal[0];
    face_vertex.v2 = normal[1];
    face_vertex.v3 = normal[2];
  }
  // Añadimos los vértices, texturas y normales
  faces_vertexes.push_back(face_vertex);
  if (there_is_texture)
    faces_textures.push_back(face_texture);
  if (there_is_normal)
    faces_normals.push_back(face_normal);
}
