
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

#define PName(U)    PtrCEVVerlet##U
#define FName(U)    FunCEVVerlet##U

#define _VALUE(name) (*reinterpret_cast<T*>(name.ptr[0]))

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void _UpdateCEVVerletHTIM(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef
    void (*_UpFunc)(const T&,const Unique64Bit&,Unique64Bit&,
                    const unsigned int&);
    Unique64Bit* P=SE.Param.start;
    _UpFunc updfunc=reinterpret_cast<_UpFunc>(P[FName(UpdateHTIM)].ptr[0]);
    T dt=_VALUE(P[PName(TimeStep)]);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      updfunc(dt,P[PName(Mass)],P[PName(NegHTIM)],i);
  }

  template <typename T, template<typename> class VT>
  void _UpdateCEVVerletVelocitySQ(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_UpFunc)(Unique64Bit&,const VT<T>&,const unsigned int&);
    typedef void (*_IUpFunc)(Unique64Bit&);
    Unique64Bit* P=SE.Param.start;
    assert(P[PName(VelocitySQ)].ptr[0]!=NULL);
    _UpFunc updfunc=reinterpret_cast<_UpFunc>(P[FName(UpdateVSQ)].ptr[0]);
    _IUpFunc inifunc=reinterpret_cast<_IUpFunc>(P[FName(UpdateVSQInit)].ptr[0]);
    inifunc(P[PName(VelocitySQ)]);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      updfunc(P[PName(VelocitySQ)],SE.grpContent[i].Velocity(),i);
  }

  template <typename T, template<typename> class VT>
  void _UpdateCEVVerletKEnergy(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_UpFunc)(T&,const Unique64Bit&,const Unique64Bit&);
    Unique64Bit* P=SE.Param.start;
    assert(P[PName(VelocitySQ)].ptr[0]!=NULL);
    _UpFunc updfunc=reinterpret_cast<_UpFunc>(P[FName(UpdateKE)].ptr[0]);
    updfunc(P[ValCEVVerletKineticEnergy].value<T>(),P[PName(Mass)],
            P[PName(VelocitySQ)]);
  }

}

#undef _VALUE

#undef FName
#undef PName

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

