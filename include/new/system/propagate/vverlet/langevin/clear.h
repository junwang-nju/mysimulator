
#ifndef _System_Propagate_VelocityVerlet_Langevin_Clear_H_
#define _System_Propagate_VelocityVerlet_Langevin_Clear_H_

#include "system/property/mass-method-name.h"
#include "system/property/friction-method-name.h"
#include "system/propagate/interface.h"
#include "system/propagate/vverlet/langevin/parameter-name.h"
#include "intrinsic-type/release.h"
#include "intrinsic-type/valid.h"

#define _DeleteElement(name) \
  P[name].ptr[0]=NULL;

#define _DeleteArray(name,p) \
  if(P[name].ptr[0]!=NULL) {\
    p=reinterpret_cast<Array1D<VT<T> >*>(P[name].ptr[0]);\
    release(*p);\
    delete_pointer(p);\
    P[name].ptr[0]=NULL;\
  }

namespace mysimulator {
  
  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void ClearLgVVerlet(SysPropagate<T,VT,SCT>& SE) {
    Array1D<VT<T> > *p=NULL;
    Unique64Bit* P=SE.Param.start;
    _DeleteArray(LgVVerletRandVector,p)
    MassMethodName MMN=
      static_cast<MassMethodName>(P[LgVVerletMassMode].u[0]);
    FrictionMethodName FMN=
      static_cast<FrictionMethodName>(P[LgVVerletFrictionMode].u[0]);
    if(MMN==GlobalMass) {
      _DeleteElement(LgVVerletMass)
      _DeleteElement(LgVVerletNegHTIM)
      _DeleteElement(LgVVerletVelocitySQ)
    } else if(MMN==ArrayMass) {
      _DeleteArray(LgVVerletMass,p)
      _DeleteArray(LgVVerletNegHTIM,p)
      _DeleteArray(LgVVerletVelocitySQ,p)
    } else Error("Unknown Mass Mode!");
    if((MMN==GlobalMass)&&(FMN==GlobalFriction)) {
      _DeleteElement(LgVVerletFriction)
      _DeleteElement(LgVVerletRandSize)
      _DeleteElement(LgVVerletFac1)
      _DeleteElement(LgVVerletFac2)
      _DeleteElement(LgVVerletVelocitySQ);
    } else {
      _DeleteArray(LgVVerletFriction,p)
      _DeleteArray(LgVVerletRandSize,p)
      _DeleteArray(LgVVerletFac1,p)
      _DeleteArray(LgVVerletFac2,p)
      _DeleteArray(LgVVerletVelocitySQ,p)
    }
    P[LgVVerletUpdateHTIMFunc].ptr[0]=NULL;
    P[LgVVerletUpdateFacFunc].ptr[0]=NULL;
    P[LgVVerletUpdateRandSizeFunc].ptr[0]=NULL;
    P[LgVVerletUpdateVSQFunc].ptr[0]=NULL;
    P[LgVVerletUpdateVSQInitFunc].ptr[0]=NULL;
    P[LgVVerletUpdateKEFunc].ptr[0]=NULL;
    P[LgVVerletBfMoveFunc].ptr[0]=NULL;
    P[LgVVerletAfMoveFunc].ptr[0]=NULL;
  }

}

#undef _DeleteArray
#undef _DeleteElement

#endif
