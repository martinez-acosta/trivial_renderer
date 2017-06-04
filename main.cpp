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
  if (input.rotate_given)
    model.rotate(input.rotate_vector);
  // model.rotate(TVector3D(toRad(0), toRad(20), 0));

  // Si hay multiplicación por escalar
  if (input.scale_given)
    // model.scale(TVector3D(100, 100, 100));
    model.scale(input.scale_vector);

  // Si hay traslación
  if (input.translate_given)
    model.translate(TVector3D(100, 100, -100));

  /* Rasterizamos el modelo 3D */

  // Creamos imagen
  TImage frame(input.resolution.x, input.resolution.y);

  // Dibujamos rasterizado wireframe
  TDraw draw;
  if (model.info.wireframe)
    draw.wireframe(frame.getData(), input.resolution, model);
  else if (model.info.faceHiding)
    draw.faceHiding(frame.getData(), input.resolution, model);
  else if (model.info.zBuffer)
    draw.zBuffer(frame.getData(), frame.getDepthBuffer(), input.resolution,
                 model);
  else if (model.info.flatShading)
    draw.flatShading(frame.getData(), frame.getDepthBuffer(), input.resolution,
                     model);
  else if (model.info.gourand)
    draw.gourandShading(frame.getData(), frame.getDepthBuffer(),
                        input.resolution, model);

  // Salvamos imagen
  frame.save("salida2.png");
}
