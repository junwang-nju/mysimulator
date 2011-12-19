
#ifndef _System_Propagate_VelocityVerlet_ConstE_Clear_H_
#define _System_Propagate_VelocityVerlet_ConstE_Clear_H_

#include "system/property/mass-method-name.h"
#include "system/propagate/interface.h"
#include "system/propagate/vverlet/const-e/parameter-name.h"
#include "intrinsic-type/release.h"

#define PName(U)  PtrCEVVerlet##U
#define FName(U)  FunCEVVerlet##U

#define _DeleteElement(U) P[PName(U)].ptr[0]=NULL;

#define _DeleteArray(U) \
  if(P[PName(U)].ptr[0]!=NULL) {\
    p=reinterpret_cast<Array1D<VT<T> >*>(P[PName(U)].ptr[0]);\
    release(*p);\
    delete_pointer(p);\
    P[PName(U)].ptr[0]=NULL;\
  }

#define _DeleteFunc(U) P[FName(U)].ptr[0]=NULL;

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void ClearCEVVerlet(SysPropagate<T,VT,SCT>& SE) {
    Array1D<VT<T> >* p=NULL;
    Unique64Bit* P=SE.Param.start;
    _DeleteElement(TimeStep)
    MassMethodName MMN=
      static_cast<MassMethodName>(P[ModCEVVerletMass].u[0]);
    switch(MMN) {
      case GlobalMass:
        _DeleteElement(Mass)
        _DeleteElement(NegHTIM)
        _DeleteElement(VelocitySQ)
        break;
      case ArrayMass:
        _DeleteArray(NegHTIM)
        _DeleteArray(Mass)
        _DeleteArray(VelocitySQ)
        break;
      default:
        Error("Unknown Method related to Mass!");
    }
    _DeleteFunc(UpdateHTIM)
    _DeleteFunc(UpdateVSQ)
    _DeleteFunc(UpdateKE)
    _DeleteFunc(BfMove)
    _DeleteFunc(AfMove)
  }

}

#undef _DeleteFunc
#undef _DeleteArray
#undef _DeleteElement

#undef FName
#undef PName

#endif

