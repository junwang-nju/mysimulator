
#ifndef _InputOutput_Console_H_
#define _InputOutput_Console_H_

#include "io/output/file/interface.h"
#include "io/input/file/interface.h"

namespace mysimulator {

  static const char* Endl="\n";

  static FileOutput COut(stdout);
  static FileOutput CErr(stderr);
  static FileInput  CIn(stdin);

}

#endif

