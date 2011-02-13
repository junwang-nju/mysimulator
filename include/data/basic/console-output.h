
#ifndef _Console_Output_H_
#define _Console_Output_H_

#include "data/basic/file-output.h"

namespace std {

  static FileOutput COut(stdout);
  static FileOutput CErr(stderr);

}


#endif

