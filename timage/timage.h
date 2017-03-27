#ifndef TIMAGE_H
#define TIMAGE_H
#include <iostream>
class TImage {

public:
  TImage(const int &width, const int &height);
  inline ~TImage() { delete data; }
  inline int getWidth() const { return width; }
  inline int getHeight() const { return height; }
  inline std::string getName() const { return name; }
  inline unsigned char *getData() { return data; }
  void save(const std::string &filename);

private:
  int width;
  int height;
  unsigned char *data;
  std::string name;
};

#endif // TIMAGE_H
