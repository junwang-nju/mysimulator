
#ifndef _System_Propagate_VelocityVerlet_Berendsen_Update_H_
#define _System_Propagate_VelocityVerlet_Berendsen_Update_H_

#include "system/propagate/interface.h"
#include "system/propagate/vverlet/berendsen/parameter-name.h"

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _UpdateBsVVerletHTIM(SysPropagate<T,VT,SCT>& SE) {
    Error("Improper Content Type");
  }

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _UpdateBsVVerletFac(SysPropagate<T,VT,SCT>& SE) {
    Error("Improper Content Type");
  }

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _UpdateBsVVerletVSQ(SysPropagate<T,VT,SCT>& SE) {
    Error("Improper Content Type");
  }

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _UpdateBsVVerletDualKEnergy(SysPropagate<T,VT,SCT>& SE) {
    Error("Improper Content Type");
  }

  template<typename,template<typename>class> class SCT>
  void _UpdateBsVVerletKEnergy(SysPropagate<T,VT,SCT>& SE) {
    Error("Improper Content Type");
  }

}

#include "system/content/with-egv/interface.h"

#define PName(U)    PtrBsVVerlet##U
#define FName(U)    FunBsVVerlet##U
#define VName(U)    ValBsVVerlet##U

#define _PVALUE(U)   (*reinterpret_cast<T*>(P[PName(U)].ptr[0]))
#define _VVALUE(U)   (P[VName(U)].value<T>())

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void _UpdateBsVVerletHTIM(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_UpFunc)(const T&,const Unique64Bit&,Unique64Bit&);
    Unique64Bit *P=SE.Param.start;
    _UpFunc upfunc=reinterpret_cast<_UpFunc>(P[FName(UpdateHTIM)].ptr[0]);
    upfunc(_PVALUE(TimeStep),P[PName(Mass)],P[PName(NegHTIM)]);
  }

  template <typename T, template<typename> class VT>
  void _UpdateBsVVerletVSQ(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_UpFunc)(Unique64Bit&,const VT<T>&,const unsigned int&);
    Unique64Bit *P=SE.Param.start;
    assert(P[PName(VelocitySQ)].ptr[0]!=NULL);
    _UpFunc upfunc=reinterpret_cast<_UpFunc>(P[FName(UpdateVSQ)].ptr[0]);
    upfunc(P[PName(VelocitySQ)],SE.grpContent);
  }

  template <typename T, template<typename> class VT>
  void _UpdateBsVVerletDualKEnergy(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_UpFunc)(const Unique64Bit&,const Unique64Bit&,T&);
    Unique64Bit *P=SE.Param.start;
    assert(P[PName(VelocitySQ)].ptr[0]!=NULL);
    _UpFunc upfunc=reinterpret_cast<_UpFunc>(P[FName(UpdateDKE)].ptr[0]);
    upfunc(P[PName(VelocitySQ)],P[PName(Mass)],_VVALUE(DualKineticEnergy));
  }

  template <typename T, template<typename> class VT>
  void _UpdateBsVVerletKEnergy(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    assert(P[PName(VelocitySQ)].ptr[0]!=NULL);
    _VVALUE(KineticEnergy)=0.5*_VVALUE(DualKineticEnergy);
  }

  template <typename T, template<typename> class VT>
  void _UpdateBsVVerletFac(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    T q=0.5*_PVALUE(TimeStep)/_PVALUE(RelaxTime);
    _VVALUE(VFacA1)=1-q;
    _VVALUE(VFacA2)=q*_PVALUE(Temperature)*_VVALUE(DOF);
    q+=1;
    _VVALUE(VFacB1)=1./q;
    _VVALUE(VFacB2)=_VVALUE(VFacA2)/q;
  }

}

#endif

