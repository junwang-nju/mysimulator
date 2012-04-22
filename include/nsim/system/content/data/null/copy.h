
#ifndef _System_Content_Data_Null_Copy_H_
#define _System_Content_Data_Null_Copy_H_

#include "system/content/data/null/interface.h"

namespace mysimulator {

  template <typename T>
  void Copy(SystemContentDataNull<T>&,const SystemContentDataNull<T>&) {}

}

#endif

