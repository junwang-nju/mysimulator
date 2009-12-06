
#ifndef _Monomer_Propagator_H_
#define _Monomer_Propagator_H_

#include "property-frame.h"

namespace std {

  typedef varVector<varVector<double> >   ParamPackType;

  class MonomerPropagator {

    public:
    
      typedef void (*MoveFuncType)(Property&, ParamPackType&,
                                   const ParamPackType&,const ParamPackType&);
      
      typedef void (*SetFuncType)(ParamPackType&,const double*,const uint&);
      
      typedef void (*AllocFuncType)(ParamPackType&,const Property&);
      
      typedef void (*SyncFuncType)(const Property&,const ParamPackType&,
                                   const ParamPackType&, ParamPackType&);
      
      varVector<MoveFuncType> MvFunc;
      
      varVector<SetFuncType> SetFunc;
      
      AllocFuncType Alloc;
      
      SyncFuncType Sync;
      
      ParamPackType runParam;
      
      MonomerPropagator() : runParam() {}

  };

}

#endif
