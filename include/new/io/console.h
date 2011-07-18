
#ifndef _InputOutput_Console_H_
#define _InputOutput_Console_H_

namespace mysimulator {

  static const char* Endl="\n";

}

#include "io/output/file/interface.h"

namespace mysimulator {

  static FileOutput COut(stdout);
  static FileOutput CErr(stderr);

}

#include "io/input/file/interface.h"

namespace mysimulator {

  static FileInput CIn(stdin);

}

#endif

