
#ifndef _Monomer_Propagator_Base_H_
#define _Monomer_Propagator_Base_H_

#include "var-vector.h"

namespace std {

  union PropagatorDataElementType {
    double d;
    void*  ptr;
    PropagatorDataElementType() {}
    PropagatorDataElementType(const PropagatorDataElementType& P) {
      myError("Cannot create from Propagator Data Element");
    }
    PropagatorDataElementType& operator=(const PropagatorDataElementType& P) {
      d=P.d;
      return *this;
    }
  };

  class MonomerPropagatorBase {

    public:

      typedef void (*MoveFuncType)(
          VectorBase<double>&, VectorBase<double>&,const VectorBase<double>&,
          const VectorBase<PropagatorDataElementType>&,
          VectorBase<PropagatorDataElementType>&);

      typedef void (*SyncFuncType)(
          const VectorBase<double>&,
          const VectorBase<PropagatorDataElementType>&,
          VectorBase<PropagatorDataElementType>&);

      typedef MonomerPropagatorBase Type;

      MoveFuncType  Move;
      SyncFuncType  Sync;
      varVector<PropagatorDataElementType>  Param;

      MonomerPropagatorBase() : Move(NULL), Sync(NULL), Param() {}

      MonomerPropagatorBase(const Type& MP) {
        myError("Cannot create from Monomer Propagator Base");
      }

      Type& operator=(const Type& MP) {
        Move=MP.Move;
        Sync=MP.Sync;
        Param=MP.Param;
        return *this;
      }

  };

}

#endif

