
#ifndef _InputOutput_Console_H_
#define _InputOutput_Console_H_

#include "IO/file-output.h"
#include "IO/file-input.h"

namespace mysimulator {

  static const char* Endl="\n";

  static FileOutput COut(stdout);
  static FileOutput CErr(stderr);
  static FileInput  CIn(stdin);

}

#endif

