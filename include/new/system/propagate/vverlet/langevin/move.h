
#ifndef _System_Propagate_VelocityVerlet_Langevin_Move_H_
#define _System_Propagate_VelocityVerlet_Langevin_Move_H_

#include "system/propagate/interface.h"
#include "system/propagate/vverlet/langevin/parameter-name.h"

namespace mysimulator {

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _BfMoveLgVVerlet(SysPropagate<T,VT,SCT>&) {
  	Error("Improper Content Type!");
  }

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _AfMoveLgVVerlet(SysPropagate<T,VT,SCT>&) {
  	Error("Improper Content Type!");
  }

}

#include "system/content/with-egv/interface.h"
#include "random/base/interface.h"

#define PName(U)  PtrLgVVerlet##U
#define DName(U)  DatLgVVerlet##U
#define FName(U)  FunLgVVerlet##U

#define _RNG(name) (*reinterpret_cast<RandomBase*>(name.ptr[0]))
#define _UPRM(U)   P[PName(U)]
#define _PVALUE(U) (*reinterpret_cast<T*>(_UPRM(U).ptr[0]))
#define _PARRAY(U) (*reinterpret_cast<Array1D<VT<T> >*>(_UPRM(U).ptr[0]))
#define _CARRAY(U) (*reinterpret_cast<const Array1D<VT<T> >*>(_UPRM(U).ptr[0]))

namespace mysimulator {

  template <typename T,template<typename> class VT>
  void _BfMoveLgVVerlet(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_MvFunc)(Array1DContent<SysContentWithEGV<T,VT> >&,
                            const T&,const Unique64Bit&,const Unique64Bit&,
                            const Unique64Bit&,const Unique64Bit&);
    Unique64Bit* P=SE.Param.start;
    _MvFunc mvfunc=reinterpret_cast<_MvFunc>(P[FName(BfMove)].ptr[0]);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      fillArray(_RNG(P[DName(GaussRNG)]),_PARRAY(RandVector)[i]);
    mvfunc(SE.grpContent,_PVALUE(TimeStep),_UPRM(NegHTIM),_UPRM(Fac1),
           _UPRM(RandVector),_UPRM(RandSize));
  }

  template <typename T,template<typename> class VT>
  void _AfMoveLgVVerlet(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_MvFunc)(Array1DContent<SysContentWithEGV<T,VT> >&,
                            const Unique64Bit&,const Unique64Bit&,
                            const Unique64Bit&,const Unique64Bit&);
    Unique64Bit* P=SE.Param.start;
    _MvFunc mvfunc=reinterpret_cast<_MvFunc>(P[FName(AfMove)].ptr[0]);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      fillArray(_RNG(P[DName(GaussRNG)]),_PARRAY(RandVector)[i]);
    mvfunc(SE.grpContent,_UPRM(NegHTIM),_UPRM(Fac2),_UPRM(RandVector),
           _UPRM(RandSize));
  }

}

#undef _CARRAY
#undef _PARRAY
#undef _PVALUE
#undef _UPRM
#undef _RNG

#undef FName
#undef DName
#undef PName

namespace mysimulator {

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void MoveLgVVerletBeforeG(SysPropagate<T,VT,SCT>& SE) {
    _BfMoveLgVVerlet(SE);
  }

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void MoveLgVVerletAfterG(SysPropagate<T,VT,SCT>& SE) {
    _AfMoveLgVVerlet(SE);
  }

}

#endif
