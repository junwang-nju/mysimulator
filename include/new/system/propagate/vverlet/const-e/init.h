
#ifndef _System_Propagate_VelocityVerlet_ConstE_Init_H_
#define _System_Propagate_VelocityVerlet_ConstE_Init_H_

#include "system/property/mass-method-name.h"
#include "system/propagate/interface.h"
#include "system/propagate/vverlet/const-e/parameter-name.h"
#include "system/propagate/vverlet/const-e/_update.h"
#include "system/propagate/vverlet/const-e/_move.h"
#include "array/1d/allocate.h"

#define _CreateElement(name) \
  P[name##Data].ptr[0]=reinterpret_cast<void*>(new T);\
  P[name].ptr[0]=P[name##Data].ptr[0];

#define _CreateArray(name,pv,pgv) \
  assert(IsValid(P[name##Data].ptr[0]));\
  pv=reinterpret_cast<VT<T>*>(P[name##Data].ptr[0]);\
  pgv=new Array1D<VT<T> >;\
  allocate(*pgv,SE.MerIDRange.size);\
  for(unsigned int i=0;i<pgv->size;++i) \
    refer((*pgv)[i],*pv,SE.MerIDRange[i].u[0],SE.MerIDRange[i].u[1]);\
  P[name].ptr[0]=reinterpret_cast<void*>(pgv);

#define _Func(type,name) \
  reinterpret_cast<void*>(static_cast<type>(name))

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void InitCEVVerlet(SysPropagate<T,VT,SCT>& SE) {
    typedef void (*UpFunc)(const T&,const Unique64Bit&,Unique64Bit&,
                           const unsigned int&);
    typedef void (*BMvFunc)(VT<T>&,VT<T>&,VT<T>&,const T&,const Unique64Bit&,
                            const unsigned int&);
    typedef void (*AMvFunc)(VT<T>&,VT<T>&,const Unique64Bit&,
                            const unsigned int&);
    Unique64Bit* P=SE.Param.start;
    MassMethodName MMN=
      static_cast<MassMethodName>(P[CEVVerletMassMode].u[0]);
    switch(MMN) {
      case GlobalMass:
        _CreateElement(CEVVerletMass)
        _CreateElement(CEVVerletNegHTimeIMass)
        P[CEVVerletUpdateHTIMFunc].ptr[0]=
          _Func(UpFunc,_UpdateFuncCEVVerletHTIMGlobaleMass<T>);
        P[CEVVerletBfMoveFunc].ptr[0]=
          _Func(BMvFunc,(_BfMoveFuncCEVVerletGlobalMass<T,VT>));
        P[CEVVerletAfMoveFunc].ptr[0]=
          _Func(AMvFunc,(_AfMoveFuncCEVVerletGlobalMass<T,VT>));
        break;
      case ArrayMass:
        VT<T> *pv;
        Array1D<VT<T> >* pgv;
        _CreateArray(CEVVerletMass,pv,pgv)
        _CreateArray(CEVVerletNegHTimeIMass,pv,pgv)
        P[CEVVerletUpdateHTIMFunc].ptr[0]=
          _Func(UpFunc,(_UpdateFuncCEVVerletHTIMArrayMass<T,VT>));
        P[CEVVerletBfMoveFunc].ptr[0]=
          _Func(BMvFunc,(_BfMoveFuncCEVVerletArrayMass<T,VT>));
        P[CEVVerletAfMoveFunc].ptr[0]=
          _Func(AMvFunc,(_AfMoveFuncCEVVerletArrayMass<T,VT>));
        break;
      default:
        Error("Unknown method related Mass!");
    }
  }

}

#undef _Func
#undef _CreateArray
#undef _CreateElement

#endif

