
#ifndef _System_Propagate_VelocityVerlet_Berendsen_Init_H_
#define _System_Propagate_VelocityVerlet_Berendsen_Init_H_

#include "system/propagate/vverlet/berendsen/parameter-name.h"
#include "system/propagate/vverlet/berendsen/_move.h"
#include "system/propagate/vverlet/berendsen/_update.h"
#include "system/propagate/interface.h"
#include "system/property/mass-method-name.h"
#include "array/1d/allocate.h"

#define PName(U)    PtrBsVVerlet##U
#define FName(U)    FunBsVVerlet##U
#define DName(U)    DatBsVVerlet##U

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
  void InitBsVVerlet(SysPropagate<T,VT,SCT>& SE) {
    typedef void (*UpMFunc)(const T&,const Unique64Bit&,const Unique64Bit&);
    typedef void (*UpVFunc)(Unique64Bit&,
                            const Array1DContent<SysContentWithEGV<T,VT> >&);
    typedef void (*UpKFunc)(const Unique64Bit&,const Unique64Bit&,T&);
    typedef void (*BMvFunc)(Array1DContent<SysContentWithEGV<T,VT> >&,
                            const T&,const Unique64Bit&);
    typedef void (*AMvFunc)(Array1DContent<SysContentWithEGV<T,VT> >&,
                            const Unique64Bit&);
    Unique64Bit *P=SE.Param.start;
    VT<T> *pv=NULL;
    Array1D<VT<T> > *pgv=NULL;
    MassMethodName MMN=static_cast<MassMethodName>(P[ModBsVVerletMass].u[0]);
    assert(MMN!=UnknownMassFormat);
    if(MMN==GlobalMass) {
      _CreateElement(Mass)
      _CreateElement(NegHTIM)
      _AssignFunc(UpdateHTIM,UpMFunc,_UpdateFuncBsVVerletNegHTIMGMass<T>)
      _AssignFunc(BfMove,BMvFunc,(_BfMoveFuncBsVVerletGMass<T,VT>))
      _AssignFunc(AfMove,AMvFunc,(_AfMoveFuncBsVVerletGMass<T,VT>))
      _CreateElement(VelocitySQ)
      _AssignFunc(UpdateVSQ,UpVFunc,(_UpdateFuncBsVVerletVSQGMass<T,VT>))
      _AssignFunc(UpdateDKE,UpKFunc,_UpdateFuncBsVVerletDualKEGMass<T>)
    } else {
      _CreateArray(Mass)
      _CreateArray(NegHTIM)
      _AssignFunc(UpdateHTIM,UpMFunc,(_UpdateFuncBsVVerletNegHTIMAMass<T,VT>))
      _AssignFunc(BfMove,BMvFunc,(_BfMoveFuncBsVVerletAMass<T,VT>))
      _AssignFunc(AfMove,AMvFunc,(_AfMoveFuncBsVVerletAMass<T,VT>))
      if(P[DName(VelocitySQ)].ptr[0]!=NULL) {
        _CreateArray(VelocitySQ)
        _AssignFunc(UpdateVSQ,UpVFunc,(_UpdateFuncBsVVerletVSQAMass<T,VT>))
        _AssignFunc(UpdateDKE,UpKFunc,(_UpdateFuncBsVVerletDualKEAMass<T,VT>))
      }
    }
  }

}

#undef _AssignFunc
#undef _CreateArray
#undef _CreateElement

#undef PName
#undef DName
#undef FName

#endif

