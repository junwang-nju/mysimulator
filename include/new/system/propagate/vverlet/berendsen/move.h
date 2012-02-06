
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

namespace mysimulator {

  template <typename T,template<typename> class VT>
  void _BfMoveBsVVerlet(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef
    void (*_MvFunc)(VT<T>&,VT<T>&,VT<T>&,const T&,const Unique64Bit&,
                    const unsigned int&);
    Unique64Bit *P=SE.Param.start;
    _MvFunc mvfunc=reinterpret_cast<_MvFunc>(P[BsVVerletBfMoveFunc].ptr[0]);
    T dt=*reinterpret_cast<T*>(P[BsVVerletTimeStep].ptr[0]);
    T fac;
    fac=P[BsVVerletVFacA1].value<T>()+
        P[BsVVerletVFacA2].value<T>()/P[BsVVerletDualKineticEnergy].value<T>();
    fac=sqroot(fac);
    for(unsigned int i=0;i<SE.grpContent.size;++i) {
      scale(SE.grpContent[i].Velocity(),fac);
      mvfunc(SE.grpContent[i].X(),SE.grpContent[i].Velocity(),
             SE.grpContent[i].EGData.Gradient(),dt,P[BsVVerletNegHTIM],i);
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
    _MvFunc mvfunc=reinterpret_cast<_MvFunc>(P[BsVVerletAfMoveFunc].ptr[0]);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      mvfunc(SE.grpContent[i].Velocity(),SE.grpContent[i].EGData.Gradient(),
             P[BsVVerletNegHTIM],i);
    SE.update(BsVVerletVSQCalc);
    SE.update(BsVVerletDualKECalc);
    T fac;
    fac=P[BsVVerletVFacB1].value<T>()+
        P[BsVVerletVFacB2].value<T>()/P[BsVVerletDualKineticEnergy].value<T>();
    P[BsVVerletDualKineticEnergy].value<T>()*=fac;
    fac=sqroot(fac);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      scale(SE.grpContent[i].Velocity(),fac);
  }

}

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

