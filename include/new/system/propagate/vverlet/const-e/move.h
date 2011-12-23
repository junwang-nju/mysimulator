
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

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void _BfMoveCEVVerlet(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_RunMoveFunc)(VT<T>&,VT<T>&,VT<T>&,const T&,
                                 const Unique64Bit&,const unsigned int&);
    Unique64Bit* P=SE.Param.start;
    _RunMoveFunc mvFunc=
      reinterpret_cast<_RunMoveFunc>(P[CEVVerletBfMoveFunc].ptr[0]);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      mvFunc(SE.grpContent[i].X(),SE.grpContent[i].Velocity(),
             SE.grpContent[i].EGData.Gradient(),
             P[CEVVerletTimeStep].value<T>(),
             P[CEVVerletNegHTimeIMass],i);
  }

  template <typename T, template<typename> class VT>
  void _AfMoveCEVVerlet(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_RunMoveFunc)(VT<T>&,VT<T>&,const T&,
                                 const Unique64Bit&,const unsigned int&);
    Unique64Bit* P=SE.Param.start;
    _RunMoveFunc mvFunc=
      reinterpret_cast<_RunMoveFunc>(P[CEVVerletAfMoveFunc].ptr[0]);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      mvFunc(SE.grpContent[i].Velocity(),SE.grpContent[i].EGData.Gradient(),
             P[CEVVerletTimeStep].value<T>(),
             P[CEVVerletNegHTimeIMass],i);
  }

}

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

