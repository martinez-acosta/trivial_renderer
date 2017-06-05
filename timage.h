#ifndef TIMAGE_H
#define TIMAGE_H
#include <iostream>
#include <vector>
class TImage {

public:
  TImage(const int &width, const int &height);
  inline int getWidth() const { return width; }
  inline int getHeight() const { return height; }
  inline std::string getName() const { return name; }
  inline std::vector<unsigned char> &getData() { return data; }
  inline std::vector<float> &getDepthBuffer() { return depthBuffer; }
  void save(const std::string &filename);
  void restart();

private:
  int width;
  int height;
  std::vector<unsigned char> data;
  std::vector<float> depthBuffer;
  std::string name;
};

#endif // TIMAGE_H
