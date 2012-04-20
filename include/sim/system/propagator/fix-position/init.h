
#ifndef _System_Propagate_FixPosition_Init_H_
#define _System_Propagate_FixPosition_Init_H_

#include "system/propagator/interface.h"
#include "system/propagator/fix-position/parameter-name.h"

namespace mysimulator {

  template <typename T,template<typename> class CT>
  void _InitFixPosition(SystemPropagator<T,CT>&) {}

}

#include "array/1d/fill.h"
#include "array/2d/size.h"

// assuming array size is larger than 30

#ifndef _InitFunc
#define _InitFunc(CType) \
  template <typename T> \
  void _InitFixPosition(SystemPropagator<T,CType>& P, CType<T>& C) { \
    unsigned int n=size(P.MerIDRange); \
    unsigned int u,v,m; \
    T *ptr; \
    T tz=0; \
    for(unsigned int i=0;i<n;++i) { \
      u=P.MerIDRange.uv[0]; \
      v=P.MerIDRange.uv[1]; \
      ptr=C.Velocity[u]; \
      m=static_cast<unsigned int>(C.Velocity[v]-ptr)+linesize(C.Velocity,v); \
      BLASFill(C.Velocity[P.MerIDRange.uv[0]],tz,m); \
    } \
  }
#else
#error "Duplicate Definition for _InitFunc"
#endif

#include "system/content/with-v/interface.h"
#include "system/content/with-ev/interface.h"
#include "system/content/with-gv/interface.h"
#include "system/content/with-egv/interface.h"

namespace mysimulator {

  _InitFunc(SystemContentWithV)
  _InitFunc(SystemContentWithEV)
  _InitFunc(SystemContentWithGV)
  _InitFunc(SystemContentWithEGV)

}

#ifdef _InitFunc
#undef _InitFunc
#endif

namespace mysimulator {

  template <typename T, template<typename> class CT>
  void InitFixPosition(SystemPropagator<T,CT>& P,CT<T>& C) {
    _InitFixPosition(P,C);
  }

}

#endif

