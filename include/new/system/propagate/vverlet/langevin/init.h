
#ifndef _System_Propagate_VelocityVerlet_Langevin_Init_H_
#define _System_Propagate_VelocityVerlet_Langevin_Init_H_

#include "system/property/mass-method-name.h"
#include "system/property/friction-method-name.h"
#include "system/propagate/interface.h"
#include "system/propagate/vverlet/langevin/parameter-name.h"
#include "system/propagate/vverlet/langevin/_update.h"
#include "system/propagate/vverlet/langevin/_move.h"
#include "array/1d/allocate.h"

#define _CreateElement(name) \
  assert(P[name##Data].ptr[0]!=NULL);\
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
  void InitLgVVerlet(SysPropagate<T,VT,SCT>& SE) {
    VT<T>* pv;
    Array1D<VT<T> >* pgv;
    Unique64Bit* P=SE.Param.start;
    MassMethodName MMN=
      static_cast<MassMethodName>(P[LgVVerletMassMode].u[0]);
    FrictionMethodName FMN=
      static_cast<FrictionMethodName>(P[LgVVerletFrictionMode].u[0]);

    assert(P[LgVVerletGaussRNG].ptr[0]!=NULL);
    _CreateArray(LgVVerletRandVector,pv,pgv)
  COut<<"==============1==========="<<Endl;
    if(MMN==GlobalMass) {
      _CreateElement(LgVVerletMass)
      _CreateElement(LgVVerletNegHTIM)
  COut<<"==========Q===1==========="<<Endl;
      if(P[LgVVerletVelocitySQData].ptr[0]!=NULL) {
        _CreateElement(LgVVerletVelocitySQ)
      }
  COut<<"==========Q===2==========="<<Endl;
    } else {
      _CreateArray(LgVVerletMass,pv,pgv)
      _CreateArray(LgVVerletNegHTIM,pv,pgv)
  COut<<"==========W===1==========="<<Endl;
      if(P[LgVVerletVelocitySQData].ptr[0]!=NULL) {
        _CreateArray(LgVVerletVelocitySQ,pv,pgv)
      }
  COut<<"==========W===2==========="<<Endl;
    }
  COut<<"=====A========1==========="<<Endl;
    if((MMN==GlobalMass)&&(FMN==GlobalFriction)) {
      _CreateElement(LgVVerletFriction)
      _CreateElement(LgVVerletRandSize)
      _CreateElement(LgVVerletFac1)
      _CreateElement(LgVVerletFac2)
    } else {
      _CreateArray(LgVVerletFriction,pv,pgv)
      _CreateArray(LgVVerletRandSize,pv,pgv)
      _CreateArray(LgVVerletFac1,pv,pgv)
      _CreateArray(LgVVerletFac2,pv,pgv)
    }

    typedef
    void (*FUpFunc)(const T&,const Unique64Bit&,const Unique64Bit&,Unique64Bit&,
                    Unique64Bit&,const unsigned int&);
    typedef
    void (*MUpFunc)(const T&,const Unique64Bit&,Unique64Bit&,
                    const unsigned int&);
    typedef
    void (*RUpFunc)(const T&,const T&,const Unique64Bit&,const Unique64Bit&,
                    Unique64Bit&,const unsigned int&);
    typedef
    void (*VUpFunc)(Unique64Bit&,const VT<T>&,const unsigned int&);
    typedef
    void (*IUpFunc)(Unique64Bit&);
    typedef
    void (*KUpFunc)(T&,const Unique64Bit&,const Unique64Bit&);
    typedef
    void (*BMvFunc)(VT<T>&,VT<T>&,VT<T>&,const T&,const Unique64Bit&,
                    const Unique64Bit&,const VT<T>&,const Unique64Bit&,
                    const unsigned int&);
    typedef
    void (*AMvFunc)(VT<T>&,VT<T>&,const Unique64Bit&,const Unique64Bit&,
                    const VT<T>&,const Unique64Bit&,const unsigned int&);
    if(MMN==GlobalMass) {
      P[LgVVerletUpdateHTIMFunc].ptr[0]=
        _Func(MUpFunc,_UpdateFuncLgVVerletHTIMGMass<T>);
      if(P[LgVVerletVelocitySQData].ptr[0]!=NULL) {
        P[LgVVerletUpdateVSQFunc].ptr[0]=
          _Func(VUpFunc,(_UpdateFuncLgVVerletVSQGMass<T,VT>));
        P[LgVVerletUpdateVSQInitFunc].ptr[0]=
          _Func(IUpFunc,_UpdateFuncLgVVerletVSQInitGMass<T>);
        P[LgVVerletUpdateKEFunc].ptr[0]=
          _Func(KUpFunc,_UpdateFuncLgVVerletKEnergyGMass<T>);
      }
      if(FMN==GlobalFriction) {
        P[LgVVerletUpdateRandSizeFunc].ptr[0]=
          _Func(RUpFunc,_UpdateFuncLgVVerletRSizeGMassGFric<T>);
        P[LgVVerletUpdateFacFunc].ptr[0]=
          _Func(FUpFunc,_UpdateFuncLgVVerletFacGMassGFric<T>);
        P[LgVVerletBfMoveFunc].ptr[0]=
          _Func(BMvFunc,(_BfMoveFuncLgVVerletGMassGFric<T,VT>));
        P[LgVVerletAfMoveFunc].ptr[0]=
          _Func(AMvFunc,(_AfMoveFuncLgVVerletGMassGFric<T,VT>));
      } else {
        P[LgVVerletUpdateRandSizeFunc].ptr[0]=
          _Func(RUpFunc,(_UpdateFuncLgVVerletRSizeGMassAFric<T,VT>));
        P[LgVVerletUpdateFacFunc].ptr[0]=
          _Func(FUpFunc,(_UpdateFuncLgVVerletFacGMassAFric<T,VT>));
        P[LgVVerletBfMoveFunc].ptr[0]=
          _Func(BMvFunc,(_BfMoveFuncLgVVerletGMassAFric<T,VT>));
        P[LgVVerletAfMoveFunc].ptr[0]=
          _Func(AMvFunc,(_AfMoveFuncLgVVerletGMassAFric<T,VT>));
      }
    } else {
      P[LgVVerletUpdateHTIMFunc].ptr[0]=
        _Func(MUpFunc,(_UpdateFuncLgVVerletHTIMAMass<T,VT>));
      if(P[LgVVerletVelocitySQData].ptr[0]!=NULL) {
        P[LgVVerletUpdateVSQFunc].ptr[0]=
          _Func(VUpFunc,(_UpdateFuncLgVVerletVSQAMass<T,VT>));
        P[LgVVerletUpdateVSQInitFunc].ptr[0]=
          _Func(IUpFunc,(_UpdateFuncLgVVerletVSQInitAMass<T,VT>));
        P[LgVVerletUpdateKEFunc].ptr[0]=
          _Func(KUpFunc,(_UpdateFuncLgVVerletKEnergyAMass<T,VT>));
      }
      if(FMN==GlobalFriction) {
        P[LgVVerletUpdateRandSizeFunc].ptr[0]=
          _Func(RUpFunc,(_UpdateFuncLgVVerletRSizeAMassGFric<T,VT>));
        P[LgVVerletUpdateFacFunc].ptr[0]=
          _Func(FUpFunc,(_UpdateFuncLgVVerletFacAMassGFric<T,VT>));
        P[LgVVerletBfMoveFunc].ptr[0]=
          _Func(BMvFunc,(_BfMoveFuncLgVVerletAMassGFric<T,VT>));
        P[LgVVerletAfMoveFunc].ptr[0]=
          _Func(AMvFunc,(_AfMoveFuncLgVVerletAMassGFric<T,VT>));
      } else {
        P[LgVVerletUpdateRandSizeFunc].ptr[0]=
          _Func(RUpFunc,(_UpdateFuncLgVVerletRSizeAMassAFric<T,VT>));
        P[LgVVerletUpdateFacFunc].ptr[0]=
          _Func(FUpFunc,(_UpdateFuncLgVVerletFacAMassAFric<T,VT>));
        P[LgVVerletBfMoveFunc].ptr[0]=
          _Func(BMvFunc,(_BfMoveFuncLgVVerletAMassAFric<T,VT>));
        P[LgVVerletAfMoveFunc].ptr[0]=
          _Func(AMvFunc,(_AfMoveFuncLgVVerletAMassAFric<T,VT>));
      }
    }
  }

}

#undef _Func
#undef _CreateArray
#undef _CreateElement

#endif

