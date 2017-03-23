#include "timage/timage.h"
#include "tinput/tinput.h"
#include "tmath/tmatrix4x4.h"
#include "tmodel/tmodel.h"
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

  TImage frame(1920,1080);
}