#include "tdraw.h"
#include "timage.h"
#include "tinput.h"
#include "tmatrix4x4.h"
#include "tmodel.h"
#include <iostream>

float toRad(float degree) { return degree * (M_PI / 180.0f); }

int main(int argc, char *argv[]) {
  // Obtenemos datos de entrada
  TInput input;

  // Obtenemos información del modelo 3D
  TModel model;

  input.getInput(argc, argv, model);
  model.getInfo(input.in_filename);
  model.info.resolution = input.resolution;

  /* Realizamos transformaciones*/
  // Si hay rotación
  // if (input.rotate_given)
  // model.rotate(input.rotate_vector);
  // model.rotate(TVector3D(toRad(0), toRad(180), 0));

  // Si hay multiplicación por escalar
  // if (input.scale_given)
  // model.scale(TVector3D(100, 100, 100));
  // model.scale(input.scale_vector);

  // Si hay traslación
  // if (input.translate_given)
  // model.translate(TVector3D(100, 100, -100));

  /* Rasterizamos el modelo 3D */

  // Creamos imagen
  TImage frame(input.resolution.x, input.resolution.y);

  // Aplicamos algoritmo
  TDraw draw;
  float rotate = 0;
  int frames = model.info.tiempo * 60 * 24;
  float t, k0, k1, k2, k3;
  TPoint interpolated;
  char name[255];

  if (model.info.wireframe) {
    struct bezier_curve *curve = &model.info.cbezier;

    for (int i = 0; i <= frames; ++i) {
      // Rotamos
      rotate += 0.01;
      model.rotate(TVector3D(toRad(rotate), toRad(rotate), 0));
      // model.scale(TVector3D(rotate, rotate, rotate));
      t = i / static_cast<float>(frames);
      k0 = (1 - t) * (1 - t) * (1 - t);
      k1 = 3 * (1 - t) * (1 - t) * t;
      k2 = 3 * (1 - t) * t * t;
      k3 = t * t * t;
      interpolated.x = static_cast<int>(curve->p0.x * k0 + curve->p1.x * k1 +
                                        curve->p2.x * k2 + curve->p3.x * k3);

      interpolated.y = static_cast<int>(curve->p0.y * k0 + curve->p1.y * k1 +
                                        curve->p2.y * k2 + curve->p3.y * k3);
      draw.wireframe(frame.getData(), input.resolution, model, interpolated);
      // Guardamos frame
      sprintf(name, "%06d", i);
      frame.save(std::string(name) + ".png");
      frame.restart();
      memset(name, 0, 255);
    }
  } else if (model.info.faceHiding) {
    struct bezier_curve *curve = &model.info.cbezier;

    for (int i = 0; i <= frames; ++i) {
      // Rotamos
      rotate += 0.01;
      model.rotate(TVector3D(toRad(rotate), toRad(rotate), 0));
      // model.scale(TVector3D(rotate, rotate, rotate));
      t = i / static_cast<float>(frames);
      k0 = (1 - t) * (1 - t) * (1 - t);
      k1 = 3 * (1 - t) * (1 - t) * t;
      k2 = 3 * (1 - t) * t * t;
      k3 = t * t * t;
      interpolated.x = static_cast<int>(curve->p0.x * k0 + curve->p1.x * k1 +
                                        curve->p2.x * k2 + curve->p3.x * k3);

      interpolated.y = static_cast<int>(curve->p0.y * k0 + curve->p1.y * k1 +
                                        curve->p2.y * k2 + curve->p3.y * k3);
      draw.faceHiding(frame.getData(), input.resolution, model, interpolated);
      // Guardamos frame
      sprintf(name, "%06d", i);
      frame.save(std::string(name) + ".png");
      frame.restart();
      memset(name, 0, 255);
    }
  } else if (model.info.zBuffer) {
    struct bezier_curve *curve = &model.info.cbezier;

    for (int i = 0; i <= frames; ++i) {
      // Rotamos
      rotate += 0.01;
      model.rotate(TVector3D(0, toRad(rotate), 0));
      // model.scale(TVector3D(rotate, rotate, rotate));
      t = i / static_cast<float>(frames);
      k0 = (1 - t) * (1 - t) * (1 - t);
      k1 = 3 * (1 - t) * (1 - t) * t;
      k2 = 3 * (1 - t) * t * t;
      k3 = t * t * t;
      interpolated.x = static_cast<int>(curve->p0.x * k0 + curve->p1.x * k1 +
                                        curve->p2.x * k2 + curve->p3.x * k3);

      interpolated.y = static_cast<int>(curve->p0.y * k0 + curve->p1.y * k1 +
                                        curve->p2.y * k2 + curve->p3.y * k3);
      draw.zBuffer(frame.getData(), frame.getDepthBuffer(), input.resolution,
                   model, interpolated);
      // Guardamos frame
      sprintf(name, "%06d", i);
      frame.save(std::string(name) + ".png");
      frame.restart();
      memset(name, 0, 255);
    }

  } else if (model.info.flatShading) {
    struct bezier_curve *curve = &model.info.cbezier;

    for (int i = 0; i <= frames; ++i) {
      // Rotamos
      rotate += 0.01;
      model.rotate(TVector3D(toRad(rotate), toRad(rotate), 0));
      // model.scale(TVector3D(rotate, rotate, rotate));
      t = i / static_cast<float>(frames);
      k0 = (1 - t) * (1 - t) * (1 - t);
      k1 = 3 * (1 - t) * (1 - t) * t;
      k2 = 3 * (1 - t) * t * t;
      k3 = t * t * t;
      interpolated.x = static_cast<int>(curve->p0.x * k0 + curve->p1.x * k1 +
                                        curve->p2.x * k2 + curve->p3.x * k3);

      interpolated.y = static_cast<int>(curve->p0.y * k0 + curve->p1.y * k1 +
                                        curve->p2.y * k2 + curve->p3.y * k3);
      draw.flatShading(frame.getData(), frame.getDepthBuffer(),
                       input.resolution, model, interpolated);
      // Guardamos frame
      sprintf(name, "%06d", i);
      frame.save(std::string(name) + ".png");
      frame.restart();
      memset(name, 0, 255);
    }
  } else if (model.info.gourand) {
    struct bezier_curve *curve = &model.info.cbezier;

    for (int i = 0; i <= frames; ++i) {
      // Rotamos
      rotate += 0.01;
      model.rotate(TVector3D(toRad(rotate), toRad(rotate), 0));
      // model.scale(TVector3D(rotate, rotate, rotate));
      t = i / static_cast<float>(frames);
      k0 = (1 - t) * (1 - t) * (1 - t);
      k1 = 3 * (1 - t) * (1 - t) * t;
      k2 = 3 * (1 - t) * t * t;
      k3 = t * t * t;
      interpolated.x = static_cast<int>(curve->p0.x * k0 + curve->p1.x * k1 +
                                        curve->p2.x * k2 + curve->p3.x * k3);

      interpolated.y = static_cast<int>(curve->p0.y * k0 + curve->p1.y * k1 +
                                        curve->p2.y * k2 + curve->p3.y * k3);
      draw.gourandShading(frame.getData(), frame.getDepthBuffer(),
                          input.resolution, model, interpolated);
      // Guardamos frame
      sprintf(name, "%06d", i);
      frame.save(std::string(name) + ".png");
      frame.restart();
      memset(name, 0, 255);
    }
  } else if (model.info.phong) {
    struct bezier_curve *curve = &model.info.cbezier;

    for (int i = 0; i <= frames; ++i) {
      // Rotamos
      rotate += 0.01;
      model.rotate(TVector3D(toRad(rotate), toRad(rotate), 0));
      // model.scale(TVector3D(rotate, rotate, rotate));
      t = i / static_cast<float>(frames);
      k0 = (1 - t) * (1 - t) * (1 - t);
      k1 = 3 * (1 - t) * (1 - t) * t;
      k2 = 3 * (1 - t) * t * t;
      k3 = t * t * t;
      interpolated.x = static_cast<int>(curve->p0.x * k0 + curve->p1.x * k1 +
                                        curve->p2.x * k2 + curve->p3.x * k3);

      interpolated.y = static_cast<int>(curve->p0.y * k0 + curve->p1.y * k1 +
                                        curve->p2.y * k2 + curve->p3.y * k3);

      draw.phongShading(frame.getData(), frame.getDepthBuffer(),
                        input.resolution, model, interpolated);
      // Guardamos frame
      sprintf(name, "%06d", i);
      frame.save(std::string(name) + ".png");
      frame.restart();
      memset(name, 0, 255);
    }
  } else if (model.info.curvaDeBezier) {
    struct bezier_curve curve = model.info.cbezier;

    for (int i = 0; i <= frames; ++i) {
      // Rotamos
      rotate += 0.01;
      // Rotamos los cuatro puntos
      model.rotate(TVector3D(toRad(rotate), toRad(rotate), 0), curve.p0);
      model.rotate(TVector3D(toRad(rotate), toRad(rotate), 0), curve.p1);
      model.rotate(TVector3D(toRad(rotate), toRad(rotate), 0), curve.p2);
      model.rotate(TVector3D(toRad(rotate), toRad(rotate), 0), curve.p3);
      // model.scale(TVector3D(rotate, rotate, rotate));
      t = i / static_cast<float>(frames);
      k0 = (1 - t) * (1 - t) * (1 - t);
      k1 = 3 * (1 - t) * (1 - t) * t;
      k2 = 3 * (1 - t) * t * t;
      k3 = t * t * t;
      interpolated.x = static_cast<int>(curve.p0.x * k0 + curve.p1.x * k1 +
                                        curve.p2.x * k2 + curve.p3.x * k3);

      interpolated.y = static_cast<int>(curve.p0.y * k0 + curve.p1.y * k1 +
                                        curve.p2.y * k2 + curve.p3.y * k3);
      draw.bezierCurve(frame, frame.getDepthBuffer(), input.resolution, model,
                       &curve);
      // Guardamos frame
      sprintf(name, "%06d", i);
      frame.save(std::string(name) + ".png");
      frame.restart();
      memset(name, 0, 255);
    }
  }
}
