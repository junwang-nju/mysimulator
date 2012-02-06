
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

#define _VALUE(name) (*reinterpret_cast<T*>(name.ptr[0]))
#define _RNG(name) (*reinterpret_cast<RandomBase*>(name.ptr[0]))
#define _ARRAY(name) (*reinterpret_cast<Array1D<VT<T> >*>(name.ptr[0]))
#define _CARRAY(name) (*reinterpret_cast<const Array1D<VT<T> >*>(name.ptr[0]))

namespace mysimulator {

  template <typename T,template<typename> class VT>
  void _BfMoveLgVVerlet(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef
    void (*_MvFunc)(VT<T>&,VT<T>&,VT<T>&,const T&,const Unique64Bit&,
                    const Unique64Bit&,const VT<T>&,const Unique64Bit&,
                    const unsigned int&);
    Unique64Bit* P=SE.Param.start;
    _MvFunc mvfunc=reinterpret_cast<_MvFunc>(P[FName(BfMove)].ptr[0]);
    T dt=_VALUE(P[PName(TimeStep)]);
    for(unsigned int i=0;i<SE.grpContent.size;++i) {
      fillArray(_RNG(P[DName(GaussRNG)]),_ARRAY(P[PName(RandVector)])[i]);
      mvfunc(
          SE.grpContent[i].X(),SE.grpContent[i].Velocity(),
          SE.grpContent[i].EGData.Gradient(),dt,P[PName(NegHTIM)],
          P[PName(Fac1)],_CARRAY(P[PName(RandVector)])[i],P[PName(RandSize)],i);
    }
  }

  template <typename T,template<typename> class VT>
  void _AfMoveLgVVerlet(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef
    void (*_MvFunc)(VT<T>&,VT<T>&,const Unique64Bit&,const Unique64Bit&,
                    const VT<T>&,const Unique64Bit&,const unsigned int&);
    Unique64Bit* P=SE.Param.start;
    _MvFunc mvfunc=reinterpret_cast<_MvFunc>(P[FName(AfMove)].ptr[0]);
    for(unsigned int i=0;i<SE.grpContent.size;++i) {
      fillArray(_RNG(P[DName(GaussRNG)]),_ARRAY(P[PName(RandVector)])[i]);
      mvfunc(
          SE.grpContent[i].Velocity(),SE.grpContent[i].EGData.Gradient(),
          P[PName(NegHTIM)],P[PName(Fac2)],_CARRAY(P[PName(RandVector)])[i],
          P[PName(RandSize)],i);
    }
  }

}

#undef _CARRAY
#undef _ARRAY
#undef _RNG
#undef _VALUE

#undef FName
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
