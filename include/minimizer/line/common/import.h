
#ifndef _Minimizer_Line_Common_Import_H_
#define _Minimizer_Line_Common_Import_H_

#include "minimizer/line/common/interface.h"
#include "minimizer/base/import.h"

namespace mysimulator {

  template <typename KT, template<typename> class VT,  typename PT, typename T>
  void import(LineMinimizerCommon<KT,VT,PT,T>& L,const KT* FG,const VT<T>* Coor,
              const PT* P, const VT<unsigned int>* umask) {
    typedef MinimizerBase<KT,VT,PT,T>   Type;
    import(static_cast<Type&>(L),FG,Coor,P,umask);
    if(Coor!=NULL) {
      assert(IsValid(*Coor));
      imprint(L.RunX,*Coor);
      imprint(L.RunG,*Coor);
      imprint(L.LineDirc,*Coor);
    }
  }

}

#endif

