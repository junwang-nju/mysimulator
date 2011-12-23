
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

namespace mysimulator {

  template <typename T,template<typename> class VT>
  void _BfMoveLgVVerlet(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef Array1D<VT<T> >   AVT;
    typedef
    void (*_MvFunc)(VT<T>&,VT<T>&,VT<T>&,const T&,const Unique64Bit&,
                    const Unique64Bit&,const VT<T>&,const Unique64Bit&,
                    const unsigned int&);
    Unique64Bit* P=SE.Param.start;
    _MvFunc mvfunc=
      reinterpret_cast<_MvFunc>(P[LgVVerletBfMoveFunc].ptr[0]);
    for(unsigned int i=0;i<SE.grpContent.size;++i) {
      fillArray(*reinterpret_cast<RandomBase*>(P[LgVVerletGaussRNG].ptr[0]),
                (*reinterpret_cast<AVT*>(P[LgVVerletRandVector].ptr[0]))[i]);
      mvfunc(SE.grpContent[i].X(),SE.grpContent[i].Velocity(),
             SE.grpContent[i].EGData.Gradient(),
             P[LgVVerletTimeStep].value<T>(),P[LgVVerletNegHTIM],
             P[LgVVerletFac1],
             (*reinterpret_cast<AVT*>(P[LgVVerletRandVector].ptr[0]))[i],
             P[LgVVerletRandSize],i);
    }
  }

  template <typename T,template<typename> class VT>
  void _AfMoveLgVVerlet(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef Array1D<VT<T> >   AVT;
    typedef
    void (*_MvFunc)(VT<T>&,VT<T>&,const Unique64Bit&,const Unique64Bit&,
                    const VT<T>&,const Unique64Bit&,const unsigned int&);
    Unique64Bit* P=SE.Param.start;
    _MvFunc mvfunc=
      reinterpret_cast<_MvFunc>(P[LgVVerletAfMoveFunc].ptr[0]);
    for(unsigned int i=0;i<SE.grpContent.size;++i) {
      fillArray(*reinterpret_cast<RandomBase*>(P[LgVVerletGaussRNG].ptr[0]),
                (*reinterpret_cast<AVT*>(P[LgVVerletRandVector].ptr[0]))[i]);
      mvfunc(SE.grpContent[i].Velocity(),SE.grpContent[i].EGData.Gradient(),
             P[LgVVerletNegHTIM],P[LgVVerletFac2],
             (*reinterpret_cast<AVT*>(P[LgVVerletRandVector].ptr[0]))[i],
             P[LgVVerletRandSize],i);
    }
  }

}

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
