
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

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _UpdateLgVVerletVelocitySQ(SysPropagate<T,VT,SCT>& SE) {
    Error("Improper Content Type!");
  }

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _UpdateLgVVerletKEnergy(SysPropagate<T,VT,SCT>& SE) {
    Error("Improper Content Type!");
  }

}

#include "system/content/with-egv/interface.h"

#define PName(U)  PtrLgVVerlet##U
#define FName(U)  FunLgVVerlet##U

#define _VALUE(name) (*reinterpret_cast<T*>(name.ptr[0]))

namespace mysimulator {

  template <typename T,template<typename> class VT>
  void _UpdateLgVVerletFac(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef
    void (*_UpFunc)(const T&,const Unique64Bit&,const Unique64Bit&,
                    Unique64Bit&,Unique64Bit&,const unsigned int&);
    Unique64Bit* P=SE.Param.start;
    _UpFunc upfunc=reinterpret_cast<_UpFunc>(P[FName(UpdateFac)].ptr[0]);
    T dt=_VALUE(P[PName(TimeStep)]);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      upfunc(dt,P[PName(Mass)],P[PName(Friction)],P[PName(Fac1)],
             P[PName(Fac2)],i);
  }

  template <typename T,template<typename> class VT>
  void _UpdateLgVVerletNegHTIM(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_UpFunc)(const T&,const Unique64Bit&,Unique64Bit&,
                            const unsigned int&);
    Unique64Bit* P=SE.Param.start;
    _UpFunc upfunc=
      reinterpret_cast<_UpFunc>(P[FName(UpdateHTIM)].ptr[0]);
    T dt=_VALUE(P[PName(TimeStep)]);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      upfunc(dt,P[PName(Mass)],P[PName(NegHTIM)],i);
  }

  template <typename T,template<typename> class VT>
  void _UpdateLgVVerletRandSize(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_UpFunc)(const T&,const T&,const Unique64Bit&,
                            const Unique64Bit&,Unique64Bit&,
                            const unsigned int&);
    Unique64Bit* P=SE.Param.start;
    _UpFunc upfunc=reinterpret_cast<_UpFunc>(P[FName(UpdateRandSize)].ptr[0]);
    T dt=_VALUE(P[PName(TimeStep)]);
    T Temp=_VALUE(P[PName(Temperature)]);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      upfunc(dt,Temp,P[PName(Mass)],P[PName(Friction)],P[PName(RandSize)],i);
  }

  template <typename T,template<typename> class VT>
  void _UpdateLgVVerletVelocitySQ(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_UpdFunc)(Unique64Bit&,const VT<T>&,const unsigned int&);
    typedef void (*_IniFunc)(Unique64Bit&);
    Unique64Bit* P=SE.Param.start;
    assert(P[PName(VelocitySQ)].ptr[0]!=NULL);
    _UpdFunc updfunc=reinterpret_cast<_UpdFunc>(P[FName(UpdateVSQ)].ptr[0]);
    _IniFunc inifunc=reinterpret_cast<_IniFunc>(P[FName(UpdateVSQInit)].ptr[0]);
    inifunc(P[PName(VelocitySQ)]);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      updfunc(P[PName(VelocitySQ)],SE.grpContent[i].Velocity(),i);
  }

  template <typename T,template<typename> class VT>
  void _UpdateLgVVerletKEnergy(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_UpFunc)(T&,const Unique64Bit&,const Unique64Bit&);
    Unique64Bit* P=SE.Param.start;
    assert(P[PName(VelocitySQ)].ptr[0]!=NULL);
    _UpFunc updfunc=reinterpret_cast<_UpFunc>(P[FName(UpdateKE)].ptr[0]);
    updfunc(P[ValLgVVerletKineticEnergy].value<T>(),P[PName(Mass)],
            P[PName(VelocitySQ)]);
  }

}

#undef _VALUE

#undef FName
#undef PName

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

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void UpdateLgVVerletVelocitySQ(SysPropagate<T,VT,SCT>& SE) {
    _UpdateLgVVerletVelocitySQ(SE);
  }

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void UpdateLgVVerletKEnergy(SysPropagate<T,VT,SCT>& SE) {
    _UpdateLgVVerletKEnergy(SE);
  }

}

#endif

