#ifndef MINPUT_H
#define MINPUT_H
#include "cmdline.h"

class MInput {
public:
  explicit MInput(int argc, char *argv[]);

private:
  struct gengetopt_args_info args_info;
};

#endif // MINPUT_H
