#include "tdraw.h"
#include "timage.h"
#include "tinput.h"
#include "tmatrix4x4.h"
#include "tmodel.h"
#include <iostream>

int main(int argc, char *argv[]) {
  // Obtenemos datos de entrada
  TInput input;

  input.getInput(argc, argv);

  // Obtenemos información del modelo 3D
  TModel model(input.in_filename);

  /* Realizamos transformaciones*/
  // Si hay rotación
  if (input.rotate_given)
    model.rotate(input.rotate_vector);

  // Si hay multiplicación por escalar
  if (input.scale_given)
    model.scale(input.scale_vector);

  // Si hay traslación
  if (input.translate_given)
    model.translate(input.translate_vector);

  /* Rasterizamos el modelo 3D */

  // Si hay viewport
  if (input.viewport_given) {
  }

  // Creamos imagen
  TImage frame(input.resolution.x, input.resolution.y);

  // Dibujamos rasterizado wireframe
  TDraw draw;
  // draw.wireframe(frame.getData(), input.resolution, model);
  // draw.interpolateTriangle(frame.getData(), input.resolution, model);
  // draw.faceHiding(frame.getData(), input.resolution, model);
  // Salvamos imagen
  frame.save("salida2.png");
}
