
#ifndef _Monomer_Propagator_H_
#define _Monomer_Propagator_H_

#include "var-vector.h"
#include "propagator-parameter-element.h"
#include "monomer-name.h"

namespace std {

  class MonomerPropagator;

  void SetUp(MonomerPropagator&, const unsigned int, const unsigned int);

  class MonomerPropagator {

    public:

      typedef void (*MoveFuncType)(
          VectorBase<double>&, VectorBase<double>&,const VectorBase<double>&,
          const VectorBase<PropagatorDataElementType>&,
          VectorBase<PropagatorDataElementType>&);

      typedef void (*SetFuncType)(
          VectorBase<PropagatorDataElementType>&, const void*);

      typedef void (*AllocFuncType)(varVector<PropagatorDataElementType>&);

      typedef void (*SyncFuncType)(
          const VectorBase<double>&,
          const VectorBase<PropagatorDataElementType>&,
          VectorBase<PropagatorDataElementType>&);

      typedef MonomerPropagator Type;

      unsigned int UnitMode;
      varVector<MoveFuncType>   Move;
      varVector<SetFuncType>    MSet;
      AllocFuncType Alloc;
      SyncFuncType  Sync;
      varVector<PropagatorDataElementType>  Param;

      MonomerPropagator()
        : UnitMode(UnknownUnitType),
          Move(), MSet(), Alloc(NULL), Sync(NULL), Param() {}

      MonomerPropagator(const Type& MP) {
        myError("Cannot create from Monomer Propagator");
      }

      Type& operator=(const Type& MP) {
        UnitMode=MP.UnitMode;
        Move.duplicate(MP.Move);
        MSet.duplicate(MP.MSet);
        Alloc=MP.Alloc;
        Sync=MP.Sync;
        Param.duplicate(MP.Param);
        return *this;
      }

      void synchronize(const VectorBase<double>& IvMass,
                       const VectorBase<PropagatorDataElementType>& GPrm) {
        assert(Sync!=NULL);
        Sync(IvMass,GPrm,Param);
      }

      void allocate(const unsigned int UnitType, const unsigned int MoveType) {
        SetUp(*this,UnitType,MoveType);
        Alloc(Param);
      }

      void Set(const unsigned int SComponent, const void* pd) {
        MSet[SComponent](Param,pd);
      }

  };

}

#include "monomer-propagator-op.h"

#endif

