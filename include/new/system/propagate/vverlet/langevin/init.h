
#ifndef _System_Propagate_VelocityVerlet_Langevin_Init_H_
#define _System_Propagate_VelocityVerlet_Langevin_Init_H_

#include "system/property/mass-method-name.h"
#include "system/property/friction-method-name.h"
#include "system/propagate/interface.h"
#include "system/propagate/vverlet/langevin/parameter-name.h"
#include "system/propagate/vverlet/langevin/_update.h"
#include "system/propagate/vverlet/langevin/_move.h"
#include "array/1d/allocate.h"

#define PName(U)      PtrLgVVerlet##U
#define DName(U)      DatLgVVerlet##U
#define FName(U)      FunLgVVerlet##U

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
  void InitLgVVerlet(SysPropagate<T,VT,SCT>& SE) {
    VT<T>* pv;
    Array1D<VT<T> >* pgv;
    Unique64Bit* P=SE.Param.start;
    MassMethodName MMN=static_cast<MassMethodName>(P[ModLgVVerletMass].u[0]);
    FrictionMethodName FMN=
      static_cast<FrictionMethodName>(P[ModLgVVerletFriction].u[0]);

    assert((MMN!=UnknownMassFormat)&&(FMN!=UnknownFrictionFormat));
    assert(P[DName(GaussRNG)].ptr[0]!=NULL);
    _CreateArray(RandVector)
    if(MMN==GlobalMass) {
      _CreateElement(Mass)
      _CreateElement(NegHTIM)
      _CreateElement(VelocitySQ)
    } else {
      _CreateArray(Mass)
      _CreateArray(NegHTIM)
      if(P[DName(VelocitySQ)].ptr[0]!=NULL) { _CreateArray(VelocitySQ) }
    }
    if(FMN==GlobalFriction) { _CreateElement(Friction) }
    else { _CreateArray(Friction) }
    if((MMN==GlobalMass)&&(FMN==GlobalFriction)) {
      _CreateElement(RandSize)
      _CreateElement(Fac1)
      _CreateElement(Fac2)
    } else {
      _CreateArray(RandSize)
      _CreateArray(Fac1)
      _CreateArray(Fac2)
    }

    typedef void (*FUpFunc)(const T&,const Unique64Bit&,const Unique64Bit&,
                            Unique64Bit&,Unique64Bit&);
    typedef void (*MUpFunc)(const T&,const Unique64Bit&,Unique64Bit&);
    typedef void (*RUpFunc)(const T&,const T&,const Unique64Bit&,
                            const Unique64Bit&,Unique64Bit&);
    typedef void (*VUpFunc)(Unique64Bit&,
                            const Array1DContent<SysContentWithEGV<T,VT> >&);
    typedef void (*KUpFunc)(T&,const Unique64Bit&,const Unique64Bit&);
    typedef void (*BMvFunc)(Array1DContent<SysContentWithEGV<T,VT> >&,
                            const T&,const Unique64Bit&,const Unique64Bit&,
                            const Unique64Bit&,const Unique64Bit&);
    typedef void (*AMvFunc)(Array1DContent<SysContentWithEGV<T,VT> >&,
                            const Unique64Bit&,const Unique64Bit&,
                            const Unique64Bit&,const Unique64Bit&);
    if(MMN==GlobalMass) {
      _AssignFunc(UpdateHTIM,MUpFunc,_UpdateFuncLgVVerletHTIMGMass<T>)
      _AssignFunc(UpdateVSQ,VUpFunc,(_UpdateFuncLgVVerletVSQGMass<T,VT>))
      _AssignFunc(UpdateKE,KUpFunc,_UpdateFuncLgVVerletKEnergyGMass<T>)
      if(FMN==GlobalFriction) {
        _AssignFunc(UpdateRandSize,RUpFunc,
                    _UpdateFuncLgVVerletRSizeGMassGFric<T>)
        _AssignFunc(UpdateFac,FUpFunc,_UpdateFuncLgVVerletFacGMassGFric<T>)
        _AssignFunc(BfMove,BMvFunc,(_BfMoveFuncLgVVerletGMassGFric<T,VT>))
        _AssignFunc(AfMove,AMvFunc,(_AfMoveFuncLgVVerletGMassGFric<T,VT>));
      } else {
        _AssignFunc(UpdateRandSize,RUpFunc,
                    (_UpdateFuncLgVVerletRSizeGMassAFric<T,VT>))
        _AssignFunc(UpdateFac,FUpFunc,(_UpdateFuncLgVVerletFacGMassAFric<T,VT>))
        _AssignFunc(BfMove,BMvFunc,(_BfMoveFuncLgVVerletGMassAFric<T,VT>))
        _AssignFunc(AfMove,AMvFunc,(_AfMoveFuncLgVVerletGMassAFric<T,VT>))
      }
    } else {
      _AssignFunc(UpdateHTIM,MUpFunc,(_UpdateFuncLgVVerletHTIMAMass<T,VT>))
      if(P[DName(VelocitySQ)].ptr[0]!=NULL) {
        _AssignFunc(UpdateVSQ,VUpFunc,(_UpdateFuncLgVVerletVSQAMass<T,VT>))
        _AssignFunc(UpdateKE,KUpFunc,(_UpdateFuncLgVVerletKEnergyAMass<T,VT>))
      }
      if(FMN==GlobalFriction) {
        _AssignFunc(UpdateRandSize,RUpFunc,
                    (_UpdateFuncLgVVerletRSizeAMassGFric<T,VT>))
        _AssignFunc(UpdateFac,FUpFunc,(_UpdateFuncLgVVerletFacAMassGFric<T,VT>))
        _AssignFunc(BfMove,BMvFunc,(_BfMoveFuncLgVVerletAMassGFric<T,VT>))
        _AssignFunc(AfMove,AMvFunc,(_AfMoveFuncLgVVerletAMassGFric<T,VT>))
      } else {
        _AssignFunc(UpdateRandSize,RUpFunc,
                    (_UpdateFuncLgVVerletRSizeAMassAFric<T,VT>))
        _AssignFunc(UpdateFac,FUpFunc,(_UpdateFuncLgVVerletFacAMassAFric<T,VT>))
        _AssignFunc(BfMove,BMvFunc,(_BfMoveFuncLgVVerletAMassAFric<T,VT>))
        _AssignFunc(AfMove,AMvFunc,(_AfMoveFuncLgVVerletAMassAFric<T,VT>))
      }
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

