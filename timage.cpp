#include "timage.h"
#include "lodepng.h"
#include <limits>
#include <memory>

TImage::TImage(const int &w, const int &h) {
  data.resize(w * h * 4);
  width = w;
  height = h;
  for (unsigned y = 0; y < height; y++)
    for (unsigned x = 0; x < width; x++) {
      data[4 * width * y + 4 * x + 0] = 0;
      data[4 * width * y + 4 * x + 1] = 0;
      data[4 * width * y + 4 * x + 2] = 0;
      data[4 * width * y + 4 * x + 3] = 255;
    }
  // zbuffer
  depthBuffer.resize(w * h);
}
void TImage::restart() {
  data.resize(width * height * 4);
  for (unsigned y = 0; y < height; y++)
    for (unsigned x = 0; x < width; x++) {
      data[4 * width * y + 4 * x + 0] = 0;
      data[4 * width * y + 4 * x + 1] = 0;
      data[4 * width * y + 4 * x + 2] = 0;
      data[4 * width * y + 4 * x + 3] = 255;
    }
  // zbuffer
  // depthBuffer.resize(width * height);
}
void TImage::save(const std::string &filename) {
  // Encode the image
  unsigned error = lodepng::encode(filename, data, width, height);

  // if there's an error, display it
  if (error)
    std::cout << "encoder error " << error << ": " << lodepng_error_text(error)
              << std::endl;
}
