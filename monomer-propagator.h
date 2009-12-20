
#ifndef _Monomer_Propagator_H_
#define _Monomer_Propagator_H_

#include "property-list.h"

namespace std {

  typedef PropertyList<>   FuncParamType;

  class MonomerPropagator {

    public:
    
      typedef void (*MoveFuncType)(VectorBase<double>&, VectorBase<double>&,
                                   const VectorBase<double>&, FuncParamType&,
                                   const FuncParamType&,const FuncParamType&);
      
      typedef void (*SetFuncType)(FuncParamType&,const double*,const uint&);
      
      typedef void (*AllocFuncType)(FuncParamType&,const VectorBase<uint>&);
      
      typedef void (*SyncFuncType)(const VectorBase<double>&,
                                   const FuncParamType&,const FuncParamType&,
                                   FuncParamType&);
      
      varVector<MoveFuncType> MvFunc;
      
      varVector<SetFuncType> SetFunc;
      
      AllocFuncType Alloc;
      
      SyncFuncType Sync;
      
      FuncParamType runParam;
      
      MonomerPropagator() : runParam() {}

  };

}

#endif
