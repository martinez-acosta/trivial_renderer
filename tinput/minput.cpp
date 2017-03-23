#include "minput.h"

MInput::MInput(int argc, char *argv[]) {
  // Inicializamos función para obtener datos de entrada
  if (cmdline_parser(argc, argv, &args_info))
    fatal("Error from cmdline_parse() in main()", strerror(errno));
}
