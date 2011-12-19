
#ifndef _System_Propagate_VelocityVerlet_Berendsen_Clear_H_
#define _System_Propagate_VelocityVerlet_Berendsen_Clear_H_

#include "system/propagate/vverlet/berendsen/parameter-name.h"
#include "system/propagate/interface.h"
#include "system/property/mass-method-name.h"
#include "intrinsic-type/release.h"

#define PName(U)    PtrBsVVerlet##U
#define FName(U)    FunBsVVerlet##U

#define _DeleteElement(U)   P[PName(U)].ptr[0]=NULL;
#define _DeleteArray(U) \
  if(P[PName(U)].ptr[0]!=NULL) {\
    p=reinterpret_cast<Array1D<VT<T> >*>(P[PName(U)].ptr[0]);\
    release(*p);\
    delete_pointer(p);\
    P[PName(U)].ptr[0]=NULL;\
  }
#define _DeleteFunc(U)  P[FName(U)].ptr[0]=NULL;

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void ClearBsVVerlet(SysPropagate<T,VT,SCT>& SE) {
    Array1D<VT<T> >* p=NULL;
    Unique64Bit *P=SE.Param.start;
    _DeleteElement(TimeStep);
    MassMethodName MMN=static_cast<MassMethodName>(P[ModBsVVerletMass].u[0]);
    assert(MMN!=UnknownMassFormat);
    if(MMN==GlobalMass) {
      _DeleteElement(Mass)
      _DeleteElement(NegHTIM)
      _DeleteElement(VelocitySQ)
    } else {
      _DeleteArray(Mass)
      _DeleteArray(NegHTIM)
      _DeleteArray(VelocitySQ)
    }
    _DeleteFunc(UpdateHTIM)
    _DeleteFunc(UpdateVSQ)
    _DeleteFunc(UpdateDKE)
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

