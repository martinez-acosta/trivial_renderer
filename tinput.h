#ifndef TINPUT_H
#define TINPUT_H
#include "cmdline.h"
#include "tvector4d.h"
#include <boost/math/constants/constants.hpp>
#include <iostream>

struct viewport {
  TPoint p1;
  TPoint p2;
};
class TInput {
public:
  TInput();
  void getInput(int argc, char **argv);
  std::string in_filename;
  std::string out_filename;
  TPoint resolution;
  bool rotate_given;

  bool scale_given;
  bool scale_x_given;
  bool scale_y_given;
  bool scale_z_given;

  bool translate_given;
  bool viewport_given;
  bool rasterWireframe;
  struct viewport view;
  TVector3D rotate_vector;
  TVector3D scale_vector;
  TVector3D translate_vector;

private:
  static constexpr const float pi = boost::math::constants::pi<float>();
  struct gengetopt_args_info args_info;
  void error(const std::string &s) const;
  void getRotate();
  void getScale();
  void getTranslate();
  void getViewport();
  void getResolution();
  float toRad(float degree) const;
};

#endif // TINPUT_H
