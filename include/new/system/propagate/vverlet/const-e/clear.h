
#ifndef _System_Propagate_VelocityVerlet_ConstE_Clear_H_
#define _System_Propagate_VelocityVerlet_ConstE_Clear_H_

#include "system/property/mass-method-name.h"
#include "system/propagate/interface.h"
#include "system/propagate/vverlet/const-e/parameter-name.h"
#include "intrinsic-type/release.h"

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
  void ClearCEVVerlet(SysPropagate<T,VT,SCT>& SE) {
    Array1D<VT<T> >* p=NULL;
    Unique64Bit* P=SE.Param.start;
    MassMethodName MMN=
      static_cast<MassMethodName>(P[CEVVerletMassMode].u[0]);
    switch(MMN) {
      case GlobalMass:
        _DeleteElement(CEVVerletMass)
        _DeleteElement(CEVVerletNegHTimeIMass)
        _DeleteElement(CEVVerletVelocitySQ)
        break;
      case ArrayMass:
        _DeleteArray(CEVVerletNegHTimeIMass,p)
        _DeleteArray(CEVVerletMass,p)
        _DeleteArray(CEVVerletVelocitySQ,p)
        break;
      default:
        Error("Unknown Method related to Mass!");
    }
    _DeleteArray(CEVVerletVelocitySQ,p)
    P[CEVVerletUpdateHTIMFunc].ptr[0]=NULL;
    P[CEVVerletUpdateVSQFunc].ptr[0]=NULL;
    P[CEVVerletUpdateKEFunc].ptr[0]=NULL;
    P[CEVVerletBfMoveFunc].ptr[0]=NULL;
    P[CEVVerletAfMoveFunc].ptr[0]=NULL;
  }

}

#undef _DeleteArray
#undef _DeleteElement

#endif

