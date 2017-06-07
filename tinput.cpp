#include "tinput.h"
#include <boost/algorithm/string.hpp>
#include <vector>

void TInput::getBezierSurface(std::string &file, TModel &model) {}
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

void TInput::getInput(int argc, char **argv, TModel &model) {
  char a;
  if (cmdline_parser(argc, argv, &args_info))
    error("Error from cmdline_parse() in getInput(int argc, char *argv[])");

  if (args_info.input_given)
    in_filename = std::string{args_info.input_arg};

  if (args_info.rotate_given)
    getRotate();

  if (args_info.scale_given || args_info.scale_x_given ||
      args_info.scale_y_given || args_info.scale_z_given)
    getScale();

  if (args_info.resolution_given)
    getResolution();
  // Obtenemos datos
  if (args_info.wireframe_given)
    model.info.wireframe = true;

  if (args_info.faceHiding_given)
    model.info.faceHiding = true;

  if (args_info.zBuffer_given) {
    model.info.zBuffer = true;
  }
  if (args_info.time_given) {
    model.info.atime = true;
    model.info.tiempo = std::stoi(args_info.time_arg);
  }
  if (args_info.flatShading_given) {
    model.info.flatShading = true;
    sscanf(args_info.flatShading_arg, "%f%c%f%c%f%c%f%c%f%c%f",
           &model.info.luces.flatShading.pos.x, &a,
           &model.info.luces.flatShading.pos.y, &a,
           &model.info.luces.flatShading.pos.z, &a,
           &model.info.luces.flatShading.color.x, &a,
           &model.info.luces.flatShading.color.y, &a,
           &model.info.luces.flatShading.color.z);
  }

  if (args_info.ambient_given) {

    model.info.lightAmbient = true;
    sscanf(args_info.ambient_arg, "%f%c%f%c%f%c%f%c%f%c%f",
           &model.info.luces.ambient.pos.x, &a, &model.info.luces.ambient.pos.y,
           &a, &model.info.luces.ambient.pos.z, &a,
           &model.info.luces.ambient.color.x, &a,
           &model.info.luces.ambient.color.y, &a,
           &model.info.luces.ambient.color.z);
  }

  if (args_info.diffuse_given)
    model.info.lightDiffuse = true;

  if (args_info.specular_given)
    model.info.lightSpecular = true;

  if (args_info.phong_given) {
    model.info.phong = true;
    sscanf(args_info.phong_arg, "%f%c%f%c%f%c%f%c%f%c%f%c%d",
           &model.info.luces.phong.light_dir.pos.x, &a,
           &model.info.luces.phong.light_dir.pos.y, &a,
           &model.info.luces.phong.light_dir.pos.z, &a,
           &model.info.luces.phong.Ka, &a, &model.info.luces.phong.Kd, &a,
           &model.info.luces.phong.Ks, &a, &model.info.luces.phong.shin);
  }

  if (args_info.gourand_given) {
    model.info.gourand = true;
    sscanf(args_info.gourand_arg, "%f%c%f%c%f%c%f%c%f%c%f",
           &model.info.luces.gourand.pos.x, &a, &model.info.luces.gourand.pos.y,
           &a, &model.info.luces.gourand.pos.z, &a,
           &model.info.luces.gourand.color.x, &a,
           &model.info.luces.gourand.color.y, &a,
           &model.info.luces.gourand.color.z);
  }

  if (args_info.bezier_curve_given)
    model.info.bezierCurve = true;

  if (args_info.bcurve_given) {
    model.info.curvaDeBezier = true;
    sscanf(args_info.bcurve_arg,
           "%f%c%f%c%f%c%f%c%f%c%f%c%f%c%f%c%f%c%f%c%f%c%f",
           &model.info.cbezier.p0.x, &a, &model.info.cbezier.p0.y, &a,
           &model.info.cbezier.p0.z, &a, &model.info.cbezier.p1.x, &a,
           &model.info.cbezier.p1.y, &a, &model.info.cbezier.p1.z, &a,
           &model.info.cbezier.p2.x, &a, &model.info.cbezier.p2.y, &a,
           &model.info.cbezier.p2.z, &a, &model.info.cbezier.p3.x, &a,
           &model.info.cbezier.p3.y, &a, &model.info.cbezier.p3.z);
  }
  if (args_info.hermite_curve_given)
    model.info.hermiteCurve = true;

  if (args_info.bezier_surface_given) {
    model.info.bezierSurface = true;
    // getBezierSurface(args_info.bezierSurface_arg, model);
  }

  if (args_info.hermite_surface_given)
    model.info.hermiteSurface = true;

  // Cámara

  if (args_info.angleOfView_given) {
    model.info.cam.angleOfView = std::stoi(args_info.angleOfView_arg);
    model.info.cam.aspectRatio = resolution.x / (float)resolution.y;
    if (args_info.near_given && args_info.far_given) {
      model.info.cam.near = std::stof(args_info.near_arg);
      model.info.cam.far = std::stof(args_info.far_arg);
    }
  }

  // Segmento de línea
  if (args_info.line_given) {
    char *tmp;

    tmp = strtok(args_info.line_arg, ",");
    model.info.line.p0.x = strtol(tmp, (char **)NULL, 10);
    model.info.line.p0.y = strtol(strtok(NULL, ","), (char **)NULL, 10);
    model.info.line.p1.x = strtol(strtok(NULL, ","), (char **)NULL, 10);
    model.info.line.p1.y = strtol(strtok(NULL, "\n\r\v\f"), (char **)NULL, 10);
  }
  if (args_info.camera_given) {
    char a;
    sscanf(args_info.camera_arg, "%f%c%f%c%f", &model.info.cam.pos.x, &a,
           &model.info.cam.pos.y, &a, &model.info.cam.pos.z);
  }
  // Curvas

  if (args_info.bezier_curve_given) {
    sscanf(args_info.bezier_curve_arg, "%f%c%f%c%f%c%f%c%f%c%f%c%f%c%f",
           &model.info.cbezier.p0.x, &a, &model.info.cbezier.p0.y, &a,
           &model.info.cbezier.p1.x, &a, &model.info.cbezier.p1.x, &a,
           &model.info.cbezier.p2.x, &a, &model.info.cbezier.p2.y, &a,
           &model.info.cbezier.p3.x, &a, &model.info.cbezier.p3.y);
  }
  if (args_info.hermite_curve_given) {
    sscanf(args_info.hermite_curve_arg, "%f%c%f%c%f%c%f%",
           &model.info.chermite.p0.x, &a, &model.info.chermite.p0.y, &a,
           &model.info.chermite.p1.x, &a, &model.info.chermite.p1.x);
  }
}

void TInput::getRotate() {
  rotate_given = true;
  char a;
  sscanf(args_info.rotate_arg, "%f%c%f%c%f", &rotate_vector.x, &a,
         &rotate_vector.y, &a, &rotate_vector.z);
  rotate_vector.x = toRad(rotate_vector.x);
  rotate_vector.y = toRad(rotate_vector.y);
  rotate_vector.z = toRad(rotate_vector.z);
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
  // std::string tmp{args_info.translate_arg};
  /*boost::split(strs, tmp, boost::is_any_of(","));

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
  }*/
}

void TInput::getViewport() {
  /*viewport_given = true;

  std::vector<std::string> str_vector;
  // std::string tmp{args_info.viewport_arg};

  boost::split(str_vector, tmp, boost::is_any_of(","));

  if (str_vector.size() == 4) {
    view.p1 = TPoint(std::stoi(str_vector.at(0)), std::stoi(str_vector.at(1)));
    view.p2 = TPoint(std::stoi(str_vector.at(2)), std::stoi(str_vector.at(3)));
  }*/
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

float TInput::toRad(float degree) const { return degree * (pi / 180.0f); }

void TInput::error(const std::string &s) const {
  std::cout << s << ": " << '\n';
  std::exit(1);
}
