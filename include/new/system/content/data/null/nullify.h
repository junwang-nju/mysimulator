
#ifndef _System_Content_Data_Null_Nullify_H_
#define _System_Content_Data_Null_Nullify_H_

#include "system/content/data/null/interface.h"
#include "io/error.h"

namespace mysimulator {

  template <typename T, template <typename> class VT>
  void nullifyEnergy(SysContentDataNull&) { Error("No action for this Data!"); }

  template <typename T, template <typename> class VT>
  void nullifyGradient(SysContentDataNull&) {Error("No action for this Data!");}

  template <typename T, template <typename> class VT>
  void nullifyBoth(SysContentDataNull&) { Error("No action for this Data!"); }

  template <typename T, template <typename> class VT>
  void nullify(SysContentDataNull&) { Error("No action for this Data!"); }

}

#endif

