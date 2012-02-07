
#ifndef _System_Propagate_VelocityVerlet_Langevin_Clear_H_
#define _System_Propagate_VelocityVerlet_Langevin_Clear_H_

#include "system/property/mass-method-name.h"
#include "system/property/friction-method-name.h"
#include "system/propagate/interface.h"
#include "system/propagate/vverlet/langevin/parameter-name.h"
#include "intrinsic-type/release.h"
#include "intrinsic-type/valid.h"

#define PName(U)    PtrLgVVerlet##U
#define FName(U)    FunLgVVerlet##U

#define _DeleteElement(U)   P[PName(U)].ptr[0]=NULL;

#define _DeleteArray(U) \
  if(P[PName(U)].ptr[0]!=NULL) {\
    p=reinterpret_cast<Array1D<VT<T> >*>(P[PName(U)].ptr[0]);\
    release(*p);\
    delete_pointer(p);\
    P[PName(U)].ptr[0]=NULL;\
  }

#define _DeleteFunc(U)   P[FName(U)].ptr[0]=NULL;

namespace mysimulator {
  
  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void ClearLgVVerlet(SysPropagate<T,VT,SCT>& SE) {
    Array1D<VT<T> > *p=NULL;
    Unique64Bit* P=SE.Param.start;
    _DeleteElement(TimeStep)
    _DeleteElement(Temperature)
    _DeleteArray(RandVector)
    MassMethodName MMN=
      static_cast<MassMethodName>(P[ModLgVVerletMass].u[0]);
    FrictionMethodName FMN=
      static_cast<FrictionMethodName>(P[ModLgVVerletFriction].u[0]);
    assert((MMN!=UnknownMassFormat)&&(FMN!=UnknownFrictionFormat));
    if(MMN==GlobalMass) {
      _DeleteElement(Mass)
      _DeleteElement(NegHTIM)
      _DeleteElement(VelocitySQ)
    } else {
      _DeleteArray(Mass)
      _DeleteArray(NegHTIM)
      _DeleteArray(VelocitySQ)
    }
    if(FMN==GlobalFriction) { _DeleteElement(Friction) }
    else { _DeleteArray(Friction) }
    if((MMN==GlobalMass)&&(FMN==GlobalFriction)) {
      _DeleteElement(RandSize)
      _DeleteElement(Fac1)
      _DeleteElement(Fac2)
    } else {
      _DeleteArray(RandSize)
      _DeleteArray(Fac1)
      _DeleteArray(Fac2)
    }
    _DeleteFunc(UpdateHTIM)
    _DeleteFunc(UpdateFac)
    _DeleteFunc(UpdateRandSize)
    _DeleteFunc(UpdateVSQ)
    _DeleteFunc(UpdateKESimple)
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
