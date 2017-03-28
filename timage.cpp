#include "timage.h"
#include "lodepng.h"
#include <memory>

TImage::TImage(const int &w, const int &h) {

  data.resize(w * h * 4);
  width = w;
  height = h;
}
void TImage::save(const std::string &filename) {
  //Encode the image
  unsigned error = lodepng::encode(filename, data, width, height);

  //if there's an error, display it
  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}
