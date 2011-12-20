
#ifndef _System_Content_Data_Null_Nullify_H_
#define _System_Content_Data_Null_Nullify_H_

#include "system/content/data/null/interface.h"
#include "io/error.h"

namespace mysimulator {

  template <typename T, template <typename> class VT>
  void nullify(SysContentDataNull&) { Warn("No action for this Data!"); }

}

#endif

