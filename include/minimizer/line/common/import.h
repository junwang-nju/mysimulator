
#ifndef _Minimizer_Line_Common_Import_H_
#define _Minimizer_Line_Common_Import_H_

#include "minimizer/line/common/interface.h"
#include "minimizer/base/import.h"

namespace mysimulator {

  template <typename KT, template<typename> class VT,  typename PT, typename T>
  void import(LineMinimizerCommon<KT,VT,PT,T>& L, const void* FG,
              const void* Coor, const void* P, const void* umask) {
    typedef MinimizerBase<KT,VT,PT,T>   Type;
    import(static_cast<Type&>(L),FG,Coor,P,umask);
    if(Coor!=NULL) {
      const VT<T>* pCoor=static_cast<const VT<T>*>(Coor);
      assert(IsValid(*pCoor));
      imprint(L.RunX,*pCoor);
      imprint(L.RunG,*pCoor);
      imprint(L.LineDirc,*pCoor);
    }
  }

}

#endif

