#include "timage.h"
#include "lodepng.h"
#include <memory>

TImage::TImage(const int &w, const int &h) {

  data.resize(w * h * 4);
  width = w;
  height = h;
  for (unsigned y = 0; y < height; y++)
    for (unsigned x = 0; x < width; x++) {
      data[4 * width * y + 4 * x + 0] = 255;
      data[4 * width * y + 4 * x + 1] = 255;
      data[4 * width * y + 4 * x + 2] = 255;
      data[4 * width * y + 4 * x + 3] = 255;
    }
}
void TImage::save(const std::string &filename) {
  // Encode the image
  unsigned error = lodepng::encode(filename, data, width, height);

  // if there's an error, display it
  if (error)
    std::cout << "encoder error " << error << ": " << lodepng_error_text(error)
              << std::endl;
}
