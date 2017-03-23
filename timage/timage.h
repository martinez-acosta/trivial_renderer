#ifndef TIMAGE_H
#define TIMAGE_H
#include <iostream>
class TImage {

public:
  TImage(const std::size_t &width, const std::size_t &height);
  inline std::size_t getWidth() const { return width; }
  inline std::size_t getHeight() const { return height; }
  inline std::string getName() const { return name; }
  inline unsigned char *getData() const { return data; }

private:
  std::size_t width;
  std::size_t height;
  std::size_t oX, oY;
  unsigned char *data;
  std::string name;
};

#endif // TIMAGE_H
