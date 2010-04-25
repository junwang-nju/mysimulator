
#ifndef _Distance_Evaluate_With_Storage_H_
#define _Distance_Evaluate_With_Storage_H_

#include "distance-evaluate-base.h"
#include "distance-displacement-calc.h"
#include "var-pair-storage.h"
#include "ref-pair-storage.h"

namespace std {

  template <template <typename> class VecType,
            template <typename> class PairStoreType>
  class DistanceEvalWStorage : public DistanceEvalBase<VecType> {

    public:

      typedef DistanceEvalWStorage<VecType,PairStoreType>   Type;

      typedef DistanceEvalBase<VecType>   ParentType;

      static const unsigned int DistanceEvalMethod;

    protected:

      typename PairStoreType<double>::Type   DistSQPack;

    public:

      DistanceEvalWStorage() : ParentType(), DistSQPack() {}

      DistanceEvalWStorage(const unsigned int Dim, const unsigned int NU)
        : ParentType(), DistSQPack() {
        allocate(Dim,NU);
      }

      DistanceEvalWStorage(const Type&) {
        myError("Cannot create from Distance Evaluate With Storage");
      }

      ~DistanceEvalWStorage() { clear(); }

      Type& operator=(const Type& DEWS) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(DEWS));
        DistSQPack=DEWS.DistSQPack;
        return *this;
      }

      template <template <typename> class iVecType,
                template <typename> class iPSType>
      Type& operator=(const DistanceEvalWStorage<iVecType,iPSType>& DEWS) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(DEWS));
        DistSQPack=DEWS.DistSQPack;
        return *this;
      }

      void clear() {
        static_cast<ParentType*>(this)->clear();
        DistSQPack.clear();
      }

      template <typename GeomType>
      void Evaluate(const VectorBase<double>& va, const VectorBase<double>& vb,
                    const unsigned int aIdx, const unsigned int bIdx,
                    const GeomType& Geo) {
        if(DistSQPack.IsUpdated(aIdx,bIdx)) {
          this->DistanceSQVec()[0]=DistSQPack(aIdx,bIdx).Element;
          DisplacementFunc(va,vb,this->Displacement(),Geo);
        } else {
          DistanceDisplacementFunc(va,vb,this->Displacement(),
                                   this->DistanceSQVec()[0],Geo);
          DistSQPack.Update(aIdx,bIdx,this->DistanceSQ());
        }
      }

      virtual void update() { DistSQPack.Inc(); }

      typename PairStoreType<double>::Type& DistanceSQStorage() {
        return DistSQPack;
      }

      const typename PairStoreType<double>::Type& DistanceSQStorage() const {
        return DistSQPack;
      }

      void allocate(const unsigned int Dim, const unsigned int NUnit) {
        myError("Not Available");
      }

      template <template <typename> class iVecType,
                template <typename> class iPairStorageType>
      void refer(const DistanceEvalWStorage<iVecType,iPairStorageType>& DEWS) {
        myError("Not Available");
      }

      Type& CanonicalForm() { return *this; }

      const Type& CanonicalForm() const { return *this; }

  };

  template <template <typename> class VecType,
            template <typename> class PairStoreType>
  const unsigned int
  DistanceEvalWStorage<VecType,PairStoreType>::DistanceEvalMethod=2;

  template <>
  void DistanceEvalWStorage<varVector,varPairStorage>::allocate(
      const unsigned int Dim, const unsigned int NUnit) {
    static_cast<ParentType*>(this)->DistanceSQVec().allocate(1);
    static_cast<ParentType*>(this)->Displacement().allocate(Dim);
    DistanceSQStorage().allocate(NUnit);
  }

  template <>
  template <template <typename> class iVecType,
            template <typename> class iPairStorageType>
  void DistanceEvalWStorage<refVector,refPairStorage>::refer(
      const DistanceEvalWStorage<iVecType,iPairStorageType>& DEWS) {
    static_cast<ParentType*>(this)->DistanceSQVec().refer(
        DEWS.DistanceSQVec());
    static_cast<ParentType*>(this)->Displacement().refer(
        DEWS.Displacement());
    DistanceSQStorage().refer(DEWS.DistanceSQStorage());
  }

}

#endif
