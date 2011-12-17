
#ifndef _Minimizer_Base_Load_H_
#define _Minimizer_Base_Load_H_

#include "minimizer/base/interface.h"
#include "object/refer.h"
#include "system/get-degree-of-freedom.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void load(MinimizerBase<T,IDT,PT,GT,VT,SCT>& M,
            System<T,IDT,PT,GT,VT,SCT>& S) {
    assert(IsValid(S));
    release(M);
    refer(M.Sys,S);
    M.DOF=DegreeOfFreedom(M.Sys());
  }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void import(MinimizerBase<T,IDT,PT,GT,VT,SCT>& M,
              Object<System<T,IDT,PT,GT,VT,SCT> >& S) {
    assert(IsValid(S));
    release(M);
    refer(M.Sys,S);
    M.DOF=DegreeOfFreedom(M.Sys());
  }

}

#endif

