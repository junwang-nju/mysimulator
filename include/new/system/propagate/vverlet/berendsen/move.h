
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

#define _PVALUE(name) (*reinterpret_cast<T*>(name.ptr[0]))
#define _VVALUE(name) (name.value<T>())

namespace mysimulator {

  template <typename T,template<typename> class VT>
  void _BfMoveBsVVerlet(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_MvFunc)(VT<T>&,VT<T>&,VT<T>&,const T&,const Unique64Bit&,
                            const unsigned int&);
    Unique64Bit *P=SE.Param.start;
    _MvFunc mvfunc=reinterpret_cast<_MvFunc>(P[FName(BfMove)].ptr[0]);
    T dt=_VALUE(P[PNamme(TimeStep)]);
    T fac;
    fac=_VVALUE(P[VName(VFacA1)])+
        _VVALUE(P[VName(VFacA2)])/_VVALUE(P[VName(DualKineticEnergy)]);
    fac=sqroot(fac);
    for(unsigned int i=0;i<SE.grpContent.size;++i) {
      scale(SE.grpContent[i].Velocity(),fac);
      mvfunc(SE.grpContent[i].X(),SE.grpContent[i].Velocity(),
             SE.grpContent[i].EGData.Gradient(),dt,P[PName(NegHTIM)],i);
    }
  }

}

#include "system/propagate/vverlet/berendsen/update-name.h"

namespace mysimulator {

  template <typename T,template<typename> class VT>
  void _AfMoveBsVVerlet(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef
    void (*_MvFunc)(VT<T>&,VT<T>&,const Unique64Bit&,const unsigned int&);
    Unique64Bit *P=SE.Param.start;
    _MvFunc mvfunc=reinterpret_cast<_MvFunc>(P[FName(AfMove)].ptr[0]);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      mvfunc(SE.grpContent[i].Velocity(),SE.grpContent[i].EGData.Gradient(),
             P[PName(NegHTIM)],i);
    SE.update(CalcBsVVerletVSQ);
    SE.update(CalcBsVVerletDualKE);
    T fac;
    fac=_VVALUE(P[VName(VFacB1)])+
        _VVALUE(P[VName(VFacB2)])/_VVALUE(P[VName(DualKineticEnergy)]);
    _VVALUE(P[VName(DualKineticEnergy)])*=fac;
    fac=sqroot(fac);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      scale(SE.grpContent[i].Velocity(),fac);
  }

}

#undef _VVALUE
#undef _PVALUE

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

