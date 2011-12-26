
#ifndef _System_Propagate_ConstE_VelocityVerlet_Update_H_
#define _System_Propagate_ConstE_VelocityVerlet_Update_H_

#include "system/propagate/interface.h"
#include "system/propagate/vverlet/const-e/parameter-name.h"

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _UpdateCEVVerletHTIM(SysPropagate<T,VT,SCT>& SE) {
    Error("Improper Content Type!");
  }

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _UpdateCEVVerletVelocitySQ(SysPropagate<T,VT,SCT>& SE) {
    Error("Improper Content Type!");
  }

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _UpdateCEVVerletKEnergy(SysPropagate<T,VT,SCT>& SE) {
    Error("Improper Content Type!");
  }

}

#include "system/content/with-egv/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void _UpdateCEVVerletHTIM(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef
    void (*_RunUpdateFunc)(const T&,const Unique64Bit&,Unique64Bit&,
                           const unsigned int&);
    Unique64Bit* P=SE.Param.start;
    _RunUpdateFunc updfunc=
      reinterpret_cast<_RunUpdateFunc>(P[CEVVerletUpdateHTIMFunc].ptr[0]);
    T dt=*reinterpret_cast<T*>(P[CEVVerletTimeStep].ptr[0]);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      updfunc(dt,P[CEVVerletMass],P[CEVVerletNegHTimeIMass],i);
  }

  template <typename T, template<typename> class VT>
  void _UpdateCEVVerletVelocitySQ(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef
    void (*_RunUpdateFunc)(Unique64Bit&,const VT<T>&,const unsigned int&);
    typedef
    void (*_IniUpdateFunc)(Unique64Bit&);
    Unique64Bit* P=SE.Param.start;
    assert(P[CEVVerletVelocitySQ].ptr[0]!=NULL);
    _RunUpdateFunc updfunc=
      reinterpret_cast<_RunUpdateFunc>(P[CEVVerletUpdateVSQFunc].ptr[0]);
    _IniUpdateFunc inifunc=
      reinterpret_cast<_IniUpdateFunc>(P[CEVVerletUpdateVSQInitFunc].ptr[0]);
    inifunc(P[CEVVerletVelocitySQ]);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      updfunc(P[CEVVerletVelocitySQ],SE.grpContent[i].Velocity(),i);
  }

  template <typename T, template<typename> class VT>
  void _UpdateCEVVerletKEnergy(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef
    void (*_RunUpdateFunc)(T&,const Unique64Bit&,const Unique64Bit&);
    Unique64Bit* P=SE.Param.start;
    assert(P[CEVVerletVelocitySQ].ptr[0]!=NULL);
    _RunUpdateFunc updfunc=
      reinterpret_cast<_RunUpdateFunc>(P[CEVVerletUpdateKEFunc].ptr[0]);
    updfunc(P[CEVVerletKineticEnergy].value<T>(),P[CEVVerletMass],
            P[CEVVerletVelocitySQ]);
  }

}

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void UpdateCEVVerletHTIM(SysPropagate<T,VT,SCT>& SE) {
    _UpdateCEVVerletHTIM(SE);
  }

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void UpdateCEVVerletVelocitySQ(SysPropagate<T,VT,SCT>& SE) {
    _UpdateCEVVerletVelocitySQ(SE);
  }

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void UpdateCEVVerletKEnergy(SysPropagate<T,VT,SCT>& SE) {
    _UpdateCEVVerletKEnergy(SE);
  }

}

#endif

