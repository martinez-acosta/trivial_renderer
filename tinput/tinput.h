#ifndef TINPUT_H
#define TINPUT_H
#include "../tmath/tvector4d.h"
#include "cmdline.h"
#include <iostream>
#include <tuple>
struct viewport {
  TPoint p1;
  TPoint p2;
};
class TInput {
public:
  TInput();
  void getInput(int argc, char *argv[]);
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
  struct gengetopt_args_info args_info;
  void error(const std::string &s) const;
  void getRotate();
  void getScale();
  void getTranslate();
  void getViewport();
  void getResolution();
  constexpr float toRad(float degree) const;
};

#endif // TINPUT_H
