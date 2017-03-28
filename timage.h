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
  void save(const std::string &filename);

private:
  int width;
  int height;
  std::vector<unsigned char> data;
  std::string name;
};

#endif // TIMAGE_H
