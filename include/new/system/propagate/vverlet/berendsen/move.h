
#ifndef _System_Propagate_VelocityVerlet_Berendsen_Move_H_
#define _System_Propagate_VelocityVerlet_Berendsen_Move_H_

#include "system/propagate/interface.h"
#include "system/propagate/vverlet/berendsen/parameter-name.h"

namespace mysimulator {

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _BfMoveBsVVerlet(SysPropagate<T,VT,SCT>&) {
    Error("Improper Content Type!");
  }

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _AfMoveBsVVerlet(SysPropagate<T,VT,SCT>&) {
    Error("Improper Content Type!");
  }

}

#include "system/content/with-egv/interface.h"
#include "intrinsic-type/square-root.h"

#define PName(U)  PtrBsVVerlet##U
#define FName(U)  FunBsVVerlet##U
#define VName(U)  ValBsVVerlet##U

#define _UPRM(U)    P[PName(U)]
#define _PVALUE(U)  (*reinterpret_cast<T*>(_UPRM(U).ptr[0]))
#define _VVALUE(U)  (P[VName(U)].value<T>())

namespace mysimulator {

  template <typename T,template<typename> class VT>
  void _BfMoveBsVVerlet(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_MvFunc)(Array1DContent<SysContentWithEGV<T,VT> >&,
                            const T&,const Unique64Bit&);
    Unique64Bit *P=SE.Param.start;
    _MvFunc mvfunc=reinterpret_cast<_MvFunc>(P[FName(BfMove)].ptr[0]);
    T dt=_PVALUE(TimeStep);
    T fac;
    fac=_VVALUE(VFacA1)+_VVALUE(VFacA2)/_VVALUE(DualKineticEnergy);
    fac=sqroot(fac);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      scale(SE.grpContent[i].Velocity(),fac);
    mvfunc(SE.grpContent,_PVALUE(TimeStep),_UPRM(NegHTIM),i);
  }

}

#include "system/propagate/vverlet/berendsen/update-name.h"

namespace mysimulator {

  template <typename T,template<typename> class VT>
  void _AfMoveBsVVerlet(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_MvFunc)(Array1DContent<SysContentWithEGV<T,VT> >&,
                            const Unique64Bit&);
    Unique64Bit *P=SE.Param.start;
    _MvFunc mvfunc=reinterpret_cast<_MvFunc>(P[FName(AfMove)].ptr[0]);
    mvfunc(SE.grpContent,_UPRM(NegHTIM),i);
    SE.update(CalcBsVVerletVSQ);
    SE.update(CalcBsVVerletDualKE);
    T fac;
    fac=_VVALUE(VFacB1)+_VVALUE(VFacB2)/_VVALUE(DualKineticEnergy);
    _VVALUE(DualKineticEnergy)*=fac;
    fac=sqroot(fac);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      scale(SE.grpContent[i].Velocity(),fac);
  }

}

#undef _VVALUE
#undef _PVALUE
#undef _UPRM

#undef VName
#undef FName
#undef PName

namespace mysimulator {

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void MoveBsVVerletBeforeG(SysPropagate<T,VT,SCT>& SE) {
    _BfMoveBsVVerlet(SE);
  }

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void MoveBsVVerletAfterG(SysPropagate<T,VT,SCT>& SE) {
    _AfMoveBsVVerlet(SE);
  }

}

#endif

