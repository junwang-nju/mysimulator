
#ifndef _System_Propagate_Langevin_VelocityVerlet_Update_H_
#define _System_Propagate_Langevin_VelocityVerlet_Update_H_

#include "system/propagate/interface.h"
#include "system/propagate/vverlet/langevin/parameter-name.h"

namespace mysimulator {

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _UpdateLgVVerletFac(SysPropagate<T,VT,SCT>&) {
    Error("Improper Content Type!");
  }

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _UpdateLgVVerletNegHTIM(SysPropagate<T,VT,SCT>&) {
    Error("Improper Content Type!");
  }

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _UpdateLgVVerletRandSize(SysPropagate<T,VT,SCT>&) {
    Error("Improper Content Type!");
  }

}

#include "system/content/with-egv/interface.h"

namespace mysimulator {

  template <typename T,template<typename> class VT>
  void _UpdateLgVVerletFac(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef
    void (*_UpFunc)(const T&,const Unique64Bit&,const Unique64Bit&,
                    Unique64Bit&,Unique64Bit&,const unsigned int&);
    Unique64Bit* P=SE.Param.start;
    _UpFunc upfunc=
      reinterpret_cast<_UpFunc>(P[LgVVerletUpdateFacFunc].ptr[0]);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      upfunc(P[LgVVerletTimeStep].value<T>(),P[LgVVerletMass],
             P[LgVVerletFriction],P[LgVVerletFac1],P[LgVVerletFac2],i);
  }

  template <typename T,template<typename> class VT>
  void _UpdateLgVVerletNegHTIM(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef
    void (*_UpFunc)(const T&,const Unique64Bit&,Unique64Bit&,
                    const unsigned int&);
    Unique64Bit* P=SE.Param.start;
    _UpFunc upfunc=
      reinterpret_cast<_UpFunc>(P[LgVVerletUpdateHTIMFunc].ptr[0]);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      upfunc(P[LgVVerletTimeStep].value<T>(),P[LgVVerletMass],
             P[LgVVerletNegHTIM],i);
  }

  template <typename T,template<typename> class VT>
  void _UpdateLgVVerletRandSize(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef
    void (*_UpFunc)(const T&,const T&,const Unique64Bit&,const Unique64Bit&,
                    Unique64Bit&,const unsigned int&);
    Unique64Bit* P=SE.Param.start;
    _UpFunc upfunc=
      reinterpret_cast<_UpFunc>(P[LgVVerletUpdateRandSizeFunc].ptr[0]);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      upfunc(P[LgVVerletTimeStep].value<T>(),P[LgVVerletTemperature].value<T>(),
             P[LgVVerletMass],P[LgVVerletFriction],P[LgVVerletRandSize],i);
  }

}

namespace mysimulator {

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void UpdateLgVVerletFac(SysPropagate<T,VT,SCT>& SE) {
    _UpdateLgVVerletFac(SE);
  }

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void UpdateLgVVerletNegHTIM(SysPropagate<T,VT,SCT>& SE) {
    _UpdateLgVVerletNegHTIM(SE);
  }

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void UpdateLgVVerletRandSize(SysPropagate<T,VT,SCT>& SE) {
    _UpdateLgVVerletRandSize(SE);
  }

}

#endif

