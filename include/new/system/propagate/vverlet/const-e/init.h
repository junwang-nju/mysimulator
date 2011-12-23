
#ifndef _System_Propagate_VelocityVerlet_ConstE_Init_H_
#define _System_Propagate_VelocityVerlet_ConstE_Init_H_

#include "system/property/mass-method-name.h"
#include "system/propagate/interface.h"
#include "system/propagate/vverlet/const-e/parameter-name.h"
#include "system/propagate/vverlet/const-e/_update.h"
#include "system/propagate/vverlet/const-e/_move.h"
#include "array/1d/allocate.h"

#define _CreateArray(pv,pgv) \
  pgv=new Array1D<VT<T> >;\
  allocate(*pgv,SE.MerIDRange.size);\
  for(unsigned int i=0;i<pgv->size;++i) \
    refer((*pgv)[i],*pv,SE.MerIDRange[i].u[0],SE.MerIDRange[i].u[1]);

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void InitCEVVerlet(SysPropagate<T,VT,SCT>& SE) {
    typedef void (*UpFunc)(const T&,const Unique64Bit&,Unique64Bit&,
                           const unsigned int&);
    typedef void (*BMvFunc)(VT<T>&,VT<T>&,VT<T>&,const T&,const Unique64Bit&,
                            const unsigned int&);
    typedef void (*AMvFunc)(VT<T>&,VT<T>&,const T&,const Unique64Bit&,
                            const unsigned int&);
    MassMethodName MMN=
      static_cast<MassMethodName>(SE.Param[CEVVerletMassMode].u[0]);
    switch(MMN) {
      case GlobalMass:
        SE.Param[CEVVerletMassData].ptr[0]=reinterpret_cast<void*>(new T);
        SE.Param[CEVVerletMass].ptr[0]=SE.Param[CEVVerletMassData].ptr[0];
        SE.Param[CEVVerletNegHTimeIMassData].ptr[0]=
          reinterpret_cast<void*>(new T);
        SE.Param[CEVVerletNegHTimeIMass].ptr[0]=
          SE.Param[CEVVerletNegHTimeIMassData].ptr[0];
        SE.Param[CEVVerletUpdateHTIMFunc].ptr[0]=
          reinterpret_cast<void*>(
              static_cast<UpFunc>(_UpdateFuncCEVVerletHTIMGlobaleMass<T>));
        SE.Param[CEVVerletBfMoveFunc].ptr[0]=
          reinterpret_cast<void*>(
              static_cast<BMvFunc>(_BfMoveFuncCEVVerletGlobalMass<T,VT>));
        SE.Param[CEVVerletAfMoveFunc].ptr[0]=
          reinterpret_cast<void*>(
              static_cast<AMvFunc>(_AfMoveFuncCEVVerletGlobalMass<T,VT>));
        break;
      case ArrayMass:
        assert(IsValid(SE.Param[CEVVerletMassData].ptr[0]));
        assert(IsValid(SE.Param[CEVVerletNegHTimeIMassData].ptr[0]));
        VT<T> *pv;
        Array1D<VT<T> >* pgv;
        pv=reinterpret_cast<VT<T>*>(SE.Param[CEVVerletMassData].ptr[0]);
        _CreateArray(pv,pgv);
        SE.Param[CEVVerletMass].ptr[0]=reinterpret_cast<void*>(pgv);
        pv=reinterpret_cast<VT<T>*>(SE.Param[CEVVerletNegHTimeIMassData].ptr[0]);
        _CreateArray(pv,pgv);
        SE.Param[CEVVerletNegHTimeIMass].ptr[0]=reinterpret_cast<void*>(pgv);
        SE.Param[CEVVerletUpdateHTIMFunc].ptr[0]=
          reinterpret_cast<void*>(
              static_cast<UpFunc>(_UpdateFuncCEVVerletHTIMArrayMass<T,VT>));
        SE.Param[CEVVerletBfMoveFunc].ptr[0]=
          reinterpret_cast<void*>(
              static_cast<BMvFunc>(_BfMoveFuncCEVVerletArrayMass<T,VT>));
        SE.Param[CEVVerletAfMoveFunc].ptr[0]=
          reinterpret_cast<void*>(
              static_cast<AMvFunc>(_AfMoveFuncCEVVerletArrayMass<T,VT>));
        break;
      default:
        Error("Unknown method related Mass!");
    }
  }

}

#undef _CreateArray

#endif

