
#ifndef _Array_2D_Fill_H_
#define _Array_2D_Fill_H_

#include "array/1d/size.h"
#include "array/1d/fill.h"

namespace mysimulator {

  template <typename T1,typename T2>
  void Fill(T1** p, const T2& d) { Fill(*p,d,size(*p)); }

  template <typename T>
  void BLASFill(T** p, const T& d) { BLASFill(*p,d,size(*p)); }

  template <typename T1, typename T2>
  void MemFill(T1** p, const T2& d) { MemFill(*p,d,size(*p)); }

}

#endif

