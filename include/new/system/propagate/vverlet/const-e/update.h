
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
  void _UpdateCEVVerletKEnergySimple(SysPropagate<T,VT,SCT>& SE) {
    Error("Improper Content Type!");
  }

}

#include "system/content/with-egv/interface.h"

#define PName(U)    PtrCEVVerlet##U
#define FName(U)    FunCEVVerlet##U
#define VName(U)    ValCEVVerlet##U

#define _UPRM(U)     P[PName(U)]
#define _PVALUE(U)   (*reinterpret_cast<T*>(_UPRM(U).ptr[0]))
#define _VVALUE(U)   (P[VName(U)].value<T>())

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void _UpdateCEVVerletHTIM(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef
    void (*_UpFunc)(const T&,const Unique64Bit&,Unique64Bit&);
    Unique64Bit* P=SE.Param.start;
    _UpFunc updfunc=reinterpret_cast<_UpFunc>(P[FName(UpdateHTIM)].ptr[0]);
    updfunc(_PVALUE(TimeStep),_UPRM(Mass),_UPRM(NegHTIM));
  }

  template <typename T, template<typename> class VT>
  void _UpdateCEVVerletVelocitySQ(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_UpFunc)(Unique64Bit&,
                            const Array1DContent<SysContentWithEGV<T,VT> >&);
    Unique64Bit* P=SE.Param.start;
    assert(_UPRM(VelocitySQ).ptr[0]!=NULL);
    _UpFunc updfunc=reinterpret_cast<_UpFunc>(P[FName(UpdateVSQ)].ptr[0]);
    updfunc(_UPRM(VelocitySQ),SE.grpContent);
  }

  template <typename T, template<typename> class VT>
  void _UpdateCEVVerletKEnergySimple(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_UpFunc)(T&,const Unique64Bit&,const Unique64Bit&);
    Unique64Bit* P=SE.Param.start;
    assert(_UPRM(VelocitySQ).ptr[0]!=NULL);
    _UpFunc updfunc=reinterpret_cast<_UpFunc>(P[FName(UpdateKE)].ptr[0]);
    updfunc(_VVALUE(KineticEnergy),_UPRM(Mass),_UPRM(VelocitySQ));
  }

}

#undef _VVALUE
#undef _PVALUE
#undef _UPRM

#undef VName
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
  void UpdateCEVVerletKEnergySimple(SysPropagate<T,VT,SCT>& SE) {
    _UpdateCEVVerletKEnergySimple(SE);
  }

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void UpdateCEVVerletKEnergy(SysPropagate<T,VT,SCT>& SE) {
    UpdateCEVVerletVelocitySQ(SE);
    UpdateCEVVerletKEnergySimple(SE);
  }

}

#endif

