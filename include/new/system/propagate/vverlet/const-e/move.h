
#ifndef _System_Propagate_VelocityVerlet_ConstE_Move_H_
#define _System_Propagate_VelocityVerlet_ConstE_Move_H_

#include "system/propagate/interface.h"
#include "system/propagate/vverlet/const-e/parameter-name.h"

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _BfMoveCEVVerlet(SysPropagate<T,VT,SCT>&) {
    Error("Improper Content Type!");
  }

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _AfMoveCEVVerlet(SysPropagate<T,VT,SCT>&) {
    Error("Improper Content Type!");
  }

}

#include "system/content/with-egv/interface.h"

#define PName(U)    PtrCEVVerlet##U
#define FName(U)    FunCEVVerlet##U

#define _UPRM(U)   P[PName(U)]
#define _PVALUE(U) (*reinterpret_cast<T*>(_UPRM(U).ptr[0]))

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void _BfMoveCEVVerlet(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_MvFunc)(Array1DContent<SysContentWithEGV<T,VT> >&,
                            const T&,const Unique64Bit&);
    Unique64Bit* P=SE.Param.start;
    _MvFunc mvfunc=reinterpret_cast<_MvFunc>(P[FName(BfMove)].ptr[0]);
    mvfunc(SE.grpContent,_PVALUE(TimeStep),_UPRM(NegHTIM));
  }

  template <typename T, template<typename> class VT>
  void _AfMoveCEVVerlet(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_MvFunc)(Array1DContent<SysContentWithEGV<T,VT> >&,
                            const Unique64Bit&);
    Unique64Bit* P=SE.Param.start;
    _MvFunc mvfunc=reinterpret_cast<_MvFunc>(P[FName(AfMove)].ptr[0]);
    mvfunc(SE.grpContent,_UPRM(NegHTIM));
  }

}

#undef _PVALUE
#undef _UPRM

#undef FName
#undef PName

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void MoveCEVVerletBeforeG(SysPropagate<T,VT,SCT>& SE) {
    _BfMoveCEVVerlet(SE);
  }

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void MoveCEVVerletAfterG(SysPropagate<T,VT,SCT>& SE) {
    _AfMoveCEVVerlet(SE);
  }

}

#endif

