
#ifndef _System_Propagate_VelocityVerlet_ConstE_Clear_H_
#define _System_Propagate_VelocityVerlet_ConstE_Clear_H_

#include "system/property/mass-method-name.h"
#include "system/propagate/interface.h"
#include "system/propagate/vverlet/const-e/parameter-name.h"
#include "intrinsic-type/release.h"

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void ClearCEVVerlet(SysPropagate<T,VT,SCT>& SE) {
    MassMethodName MMN=
      static_cast<MassMethodName>(SE.Param[CEVVerletMassMode].u[0]);
    switch(MMN) {
      case GlobalMass:
        delete_pointer(
            reinterpret_cast<T*&>(SE.Param[CEVVerletMassData].ptr[0]));
        delete_pointer(
            reinterpret_cast<T*&>(SE.Param[CEVVerletNegHTimeIMassData].ptr[0]));
        SE.Param[CEVVerletMass].ptr[0]=NULL;
        SE.Param[CEVVerletNegHTimeIMass].ptr[0]=NULL;
        break;
      case ArrayMass:
        release(*reinterpret_cast<Array1D<VT<T> >*>(SE.Param[CEVVerletNegHTimeIMass].ptr[0]));
        release(*reinterpret_cast<Array1D<VT<T> >*>(SE.Param[CEVVerletMass].ptr[0]));
        break;
      default:
        Error("Unknown Method related to Mass!");
    }
    SE.Param[CEVVerletUpdateHTIMFunc].ptr[0]=NULL;
    SE.Param[CEVVerletBfMoveFunc].ptr[0]=NULL;
    SE.Param[CEVVerletAfMoveFunc].ptr[0]=NULL;
  }

}

#endif

