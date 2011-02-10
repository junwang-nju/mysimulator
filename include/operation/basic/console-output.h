
#ifndef _Console_Output_H_
#define _Console_Output_H_

#include "operation/basic/file-output.h"

namespace std {

  static FileOutput COut(stdout);
  static FileOutput CErr(stderr);
  static const char* Endl="\n";

}


#endif

