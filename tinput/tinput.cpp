#include "tinput.h"
#include <boost/algorithm/string.hpp>
#include <boost/math/constants/constants.hpp>
#include <vector>

TInput::TInput() {
  rotate_given = false;

  scale_given = false;
  scale_x_given = false;
  scale_y_given = false;
  scale_z_given = false;

  translate_given = false;
  viewport_given = false;
  rasterWireframe = false;
  rotate_vector = TVector3D(0.0f, 0.0f, 0.0f);
  scale_vector = TVector3D(0.0f, 0.0f, 0.0f);
  translate_vector = TVector3D(0.0f, 0.0f, 0.0f);
}

void TInput::getInput(int argc, char *argv[]) {
  if (cmdline_parser(argc, argv, &args_info))
    error("Error from cmdline_parse() in getInput(int argc, char *argv[])");

  if (args_info.input_given)
    std::string input = std::string{args_info.input_arg};

  if (args_info.output_given)
    std::string output = std::string{args_info.output_arg};

  if (args_info.rotate_given || args_info.rotate_x_given ||
      args_info.rotate_y_given || args_info.rotate_z_given)
    getRotate();

  if (args_info.scale_given || args_info.scale_x_given ||
      args_info.scale_y_given || args_info.scale_z_given)
    getScale();

  if (args_info.translate_given)
    getTranslate();

  if (args_info.viewport_given)
    getViewport();

  if (args_info.resolution_given)
    getResolution();
}

void TInput::getRotate() {
  std::string tmp;

  if (args_info.rotate_given) {
    rotate_given = true;
    tmp = std::string{args_info.rotate_arg};
    rotate_vector.x = toRad(stof(tmp));
    rotate_vector.y = toRad(stof(tmp));
    rotate_vector.z = toRad(stof(tmp));
  }

  if (args_info.rotate_x_given) {

    tmp = std::string{args_info.rotate_x_arg};
    rotate_vector.x = toRad(stof(tmp));
  }

  if (args_info.rotate_y_given) {

    tmp = std::string{args_info.rotate_y_arg};
    rotate_vector.y = toRad(stof(tmp));
  }

  if (args_info.rotate_z_given) {
    tmp = std::string{args_info.rotate_z_arg};
    rotate_vector.z = toRad(stof(tmp));
  }
}
void TInput::getScale() {
  std::string tmp;
  float m;
  if (args_info.scale_given) {
    scale_given = true;
    tmp = std::string{args_info.scale_arg};
    m = stof(tmp);
    scale_vector.x = m;
    scale_vector.y = m;
    scale_vector.z = m;
  }

  if (args_info.scale_x_given) {
    scale_x_given = true;
    tmp = std::string{args_info.scale_x_arg};
    scale_vector.x = stof(tmp);
  }

  if (args_info.scale_y_given) {
    scale_y_given = true;
    tmp = std::string{args_info.scale_y_arg};
    scale_vector.y = stof(tmp);
  }

  if (args_info.scale_z_given) {
    scale_z_given = true;
    tmp = std::string{args_info.scale_z_arg};
    scale_vector.z = stof(tmp);
  }
}

void TInput::getTranslate() {

  translate_given = true;

  std::vector<std::string> strs;
  std::string tmp{args_info.translate_arg};
  boost::split(strs, tmp, boost::is_any_of(","));

  switch (strs.size()) {
  case 1:
    translate_vector = TVector3D(std::stof(strs.at(0)), 0.0f, 0.0f);
    break;
  case 2:
    translate_vector =
        TVector3D(std::stof(strs.at(0)), std::stof(strs.at(1)), 0.0f);
    break;
  case 3:
    translate_vector = TVector3D(std::stof(strs.at(0)), std::stof(strs.at(1)),
                                 std::stof(strs.at(2)));
    break;
  }
}

void TInput::getViewport() {
  viewport_given = true;

  std::vector<std::string> str_vector;
  std::string tmp{args_info.translate_arg};
  boost::split(str_vector, tmp, boost::is_any_of(","));

  if (str_vector.size() == 4) {
    view.p1 = TPoint(std::stoi(str_vector.at(0)), std::stoi(str_vector.at(1)));
    view.p2 = TPoint(std::stoi(str_vector.at(2)), std::stoi(str_vector.at(3)));
  }
}

void TInput::getResolution() {

  std::vector<std::string> str_vector;
  std::string tmp{args_info.resolution_arg};
  boost::split(str_vector, tmp, boost::is_any_of(","));
  viewport_given = true;
  if (str_vector.size() == 2) {
    resolution =
        TPoint(std::stoi(str_vector.at(0)), std::stoi(str_vector.at(1)));
  }
}

constexpr float TInput::toRad(float degree) const {

  return degree * (boost::math::constants::pi<float>() / 180.0f);
}

void TInput::error(const std::string &s) const {
  std::cout << s << ": " << '\n';
  std::exit(1);
}
