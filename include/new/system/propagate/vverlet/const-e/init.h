
#ifndef _System_Propagate_VelocityVerlet_ConstE_Init_H_
#define _System_Propagate_VelocityVerlet_ConstE_Init_H_

#include "system/property/mass-method-name.h"
#include "system/propagate/interface.h"
#include "system/propagate/vverlet/const-e/parameter-name.h"
#include "system/propagate/vverlet/const-e/_update.h"
#include "system/propagate/vverlet/const-e/_move.h"
#include "array/1d/allocate.h"

#define _CreateElement(name) \
  P[name].ptr[0]=P[name##Data].ptr[0];

#define _CreateArray(name,pv,pgv) \
  assert(P[name##Data].ptr[0]!=NULL);\
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
    typedef void (*UpVFunc)(Unique64Bit&,const VT<T>&,const unsigned int&);
    typedef void (*UpKFunc)(T&,const Unique64Bit&,const Unique64Bit&);
    typedef void (*UpIFunc)(Unique64Bit&);
    typedef void (*BMvFunc)(VT<T>&,VT<T>&,VT<T>&,const T&,const Unique64Bit&,
                            const unsigned int&);
    typedef void (*AMvFunc)(VT<T>&,VT<T>&,const Unique64Bit&,
                            const unsigned int&);
    Unique64Bit* P=SE.Param.start;
    VT<T> *pv=NULL;
    Array1D<VT<T> >* pgv=NULL;
    MassMethodName MMN=
      static_cast<MassMethodName>(P[CEVVerletMassMode].u[0]);
    switch(MMN) {
      case GlobalMass:
        _CreateElement(CEVVerletMass)
        _CreateElement(CEVVerletNegHTimeIMass)
        if(P[CEVVerletVelocitySQData].ptr[0]!=NULL) {
          _CreateElement(CEVVerletVelocitySQ)
          P[CEVVerletUpdateVSQFunc].ptr[0]=
            _Func(UpVFunc,(_UpdateFuncCEVVerletVSQGlobalMass<T,VT>));
          P[CEVVerletUpdateKEFunc].ptr[0]=
            _Func(UpKFunc,_UpdateFuncCEVVerletKEnergyGlobalMass<T>);
          P[CEVVerletUpdateVSQInitFunc].ptr[0]=
            _Func(UpIFunc,_UpdateFuncCEVVerletVSQInitGlobalMass<T>);
        }
        P[CEVVerletUpdateHTIMFunc].ptr[0]=
          _Func(UpFunc,_UpdateFuncCEVVerletHTIMGlobaleMass<T>);
        P[CEVVerletBfMoveFunc].ptr[0]=
          _Func(BMvFunc,(_BfMoveFuncCEVVerletGlobalMass<T,VT>));
        P[CEVVerletAfMoveFunc].ptr[0]=
          _Func(AMvFunc,(_AfMoveFuncCEVVerletGlobalMass<T,VT>));
        break;
      case ArrayMass:
        _CreateArray(CEVVerletMass,pv,pgv)
        _CreateArray(CEVVerletNegHTimeIMass,pv,pgv)
        if(P[CEVVerletVelocitySQData].ptr[0]!=NULL) {
          _CreateArray(CEVVerletVelocitySQ,pv,pgv)
          P[CEVVerletUpdateVSQFunc].ptr[0]=
            _Func(UpVFunc,(_UpdateFuncCEVVerletVSQArrayMass<T,VT>));
          P[CEVVerletUpdateKEFunc].ptr[0]=
            _Func(UpKFunc,(_UpdateFuncCEVVerletKEnergyArrayMass<T,VT>));
          P[CEVVerletUpdateVSQInitFunc].ptr[0]=
            _Func(UpIFunc,(_UpdateFuncCEVVerletVSQInitArrayMass<T,VT>));
        }
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

