
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
  void _UpdateLgVVerletKEnergySimple(SysPropagate<T,VT,SCT>& SE) {
    Error("Improper Content Type!");
  }

}

#include "system/content/with-egv/interface.h"

#define PName(U)  PtrLgVVerlet##U
#define FName(U)  FunLgVVerlet##U
#define VName(U)  ValLgVVerlet##U

#define _PVALUE(U)  (*reinterpret_cast<T*>(P[PName(U)].ptr[0]))
#define _VVALUE(U)  (P[VName(U)].value<T>())

namespace mysimulator {

  template <typename T,template<typename> class VT>
  void _UpdateLgVVerletFac(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_UpFunc)(const T&,const Unique64Bit&,const Unique64Bit&,
                            Unique64Bit&,Unique64Bit&);
    Unique64Bit* P=SE.Param.start;
    _UpFunc upfunc=reinterpret_cast<_UpFunc>(P[FName(UpdateFac)].ptr[0]);
    upfunc(_PVALUE(TimeStep),P[PName(Mass)],P[PName(Friction)],P[PName(Fac1)],
           P[PName(Fac2)]);
  }

  template <typename T,template<typename> class VT>
  void _UpdateLgVVerletNegHTIM(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_UpFunc)(const T&,const Unique64Bit&,Unique64Bit&);
    Unique64Bit* P=SE.Param.start;
    _UpFunc upfunc=reinterpret_cast<_UpFunc>(P[FName(UpdateHTIM)].ptr[0]);
    upfunc(_PVALUE(TimeStep),P[PName(Mass)],P[PName(NegHTIM)]);
  }

  template <typename T,template<typename> class VT>
  void _UpdateLgVVerletRandSize(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_UpFunc)(const T&,const T&,const Unique64Bit&,
                            const Unique64Bit&,Unique64Bit&);
    Unique64Bit* P=SE.Param.start;
    _UpFunc upfunc=reinterpret_cast<_UpFunc>(P[FName(UpdateRandSize)].ptr[0]);
    upfunc(_PVALUE(TimeStep),_PVALUE(Temperature),P[PName(Mass)],
           P[PName(Friction)],P[PName(RandSize)]);
  }

  template <typename T,template<typename> class VT>
  void _UpdateLgVVerletVelocitySQ(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_UpdFunc)(Unique64Bit&,
                             const Array1DContent<SysContentWithEGV<T,VT> >&);
    Unique64Bit* P=SE.Param.start;
    assert(P[PName(VelocitySQ)].ptr[0]!=NULL);
    _UpdFunc updfunc=reinterpret_cast<_UpdFunc>(P[FName(UpdateVSQ)].ptr[0]);
    updfunc(P[PName(VelocitySQ)],SE.grpContent);
  }

  template <typename T,template<typename> class VT>
  void _UpdateLgVVerletKEnergySimple(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_UpFunc)(T&,const Unique64Bit&,const Unique64Bit&);
    Unique64Bit* P=SE.Param.start;
    assert(P[PName(VelocitySQ)].ptr[0]!=NULL);
    _UpFunc updfunc=reinterpret_cast<_UpFunc>(P[FName(UpdateKESimple)].ptr[0]);
    updfunc(_VVALUE(KineticEnergy),P[PName(Mass)],P[PName(VelocitySQ)]);
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
  void UpdateLgVVerletKEnergySimple(SysPropagate<T,VT,SCT>& SE) {
    _UpdateLgVVerletKEnergySimple(SE);
  }

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void UpdateLgVVerletKEnergy(SysPropagate<T,VT,SCT>& SE) {
    UpdateLgVVerletVelocitySQ(SE);
    UpdateLgVVerletKEnergySimple(SE);
  }

}

#endif

