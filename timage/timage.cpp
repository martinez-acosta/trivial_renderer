#include "timage.h"
#include "lodepng.h"
#include <memory>

TImage::TImage(const int &width, const int &height) {

  data = new unsigned char[static_cast<std::size_t>(width * height)];
  this->width = width;
  this->height = height;
}
void TImage::save(const std::string &filename) {
  /*Encode the image*/
  unsigned error = lodepng_encode32_file(filename.c_str(), data, width, height);

  // if there's an error, display it
  if (error)
    std::cout << "encoder error " << error << ": " << lodepng_error_text(error)
              << std::endl;
}
