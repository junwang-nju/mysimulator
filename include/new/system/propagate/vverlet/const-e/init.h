
#ifndef _System_Propagate_VelocityVerlet_ConstE_Init_H_
#define _System_Propagate_VelocityVerlet_ConstE_Init_H_

#include "system/property/mass-method-name.h"
#include "system/propagate/interface.h"
#include "system/propagate/vverlet/const-e/parameter-name.h"
#include "system/propagate/vverlet/const-e/_update.h"
#include "system/propagate/vverlet/const-e/_move.h"
#include "array/1d/allocate.h"

#define PName(U)      PtrCEVVerlet##U
#define DName(U)      DatCEVVerlet##U
#define FName(U)      FunCEVVerlet##U

#define _CreateElement(U) \
  P[PName(U)].ptr[0]=reinterpret_cast<void*>(&(P[DName(U)].value<T>()));

#define _CreateArray(U) \
  assert(P[DName(U)].ptr[0]!=NULL);\
  pv=reinterpret_cast<VT<T>*>(P[DName(U)].ptr[0]);\
  pgv=new Array1D<VT<T> >;\
  allocate(*pgv,SE.MerIDRange.size);\
  for(unsigned int i=0;i<pgv->size;++i) \
    refer((*pgv)[i],*pv,SE.MerIDRange[i].u[0],SE.MerIDRange[i].u[1]);\
  P[PName(U)].ptr[0]=reinterpret_cast<void*>(pgv);

#define _AssignFunc(U,type,f) \
  P[FName(U)].ptr[0]=reinterpret_cast<void*>(static_cast<type>(f));

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void InitCEVVerlet(SysPropagate<T,VT,SCT>& SE) {
    typedef void (*UpFunc)(const T&,const Unique64Bit&,Unique64Bit&);
    typedef void (*UpVFunc)(Unique64Bit&,
                            const Array1DContent<SysContentWithEGV<T,VT> >&);
    typedef void (*UpKFunc)(T&,const Unique64Bit&,const Unique64Bit&);
    typedef void (*BMvFunc)(VT<T>&,VT<T>&,VT<T>&,const T&,const Unique64Bit&,
                            const unsigned int&);
    typedef void (*AMvFunc)(VT<T>&,VT<T>&,const Unique64Bit&,
                            const unsigned int&);
    Unique64Bit* P=SE.Param.start;
    VT<T> *pv=NULL;
    Array1D<VT<T> >* pgv=NULL;
    MassMethodName MMN=
      static_cast<MassMethodName>(P[ModCEVVerletMass].u[0]);
    switch(MMN) {
      case GlobalMass:
        _CreateElement(Mass)
        _CreateElement(NegHTIM)
        _AssignFunc(UpdateHTIM,UpFunc,_UpdateFuncCEVVerletHTIMGMass<T>)
        _AssignFunc(BfMove,BMvFunc,(_BfMoveFuncCEVVerletGMass<T,VT>))
        _AssignFunc(AfMove,AMvFunc,(_AfMoveFuncCEVVerletGMass<T,VT>))
        _CreateElement(VelocitySQ)
        _AssignFunc(UpdateVSQ,UpVFunc,(_UpdateFuncCEVVerletVSQGMass<T,VT>))
        _AssignFunc(UpdateKE,UpKFunc,_UpdateFuncCEVVerletKEnergyGMass<T>)
        break;
      case ArrayMass:
        _CreateArray(Mass)
        _CreateArray(NegHTIM)
        if(P[DatCEVVerletVelocitySQ].ptr[0]!=NULL) {
          _CreateArray(VelocitySQ)
          _AssignFunc(UpdateVSQ,UpVFunc,(_UpdateFuncCEVVerletVSQAMass<T,VT>))
          _AssignFunc(UpdateKE,UpKFunc,(_UpdateFuncCEVVerletKEnergyAMass<T,VT>))
        }
        _AssignFunc(UpdateHTIM,UpFunc,(_UpdateFuncCEVVerletHTIMAMass<T,VT>))
        _AssignFunc(BfMove,BMvFunc,(_BfMoveFuncCEVVerletAMass<T,VT>))
        _AssignFunc(AfMove,AMvFunc,(_AfMoveFuncCEVVerletAMass<T,VT>))
        break;
      default:
        Error("Unknown method related Mass!");
    }
  }

}

#undef _AssignFunc
#undef _CreateArray
#undef _CreateElement

#undef FName
#undef DName
#undef PName

#endif

