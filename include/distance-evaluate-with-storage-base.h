
#ifndef _Distance_Evaluate_With_Storage_Base_H_
#define _Distance_Evaluate_With_Storage_Base_H_

#include "distance-evaluate-base.h"
#include "distance-displacement-calc.h"
#include "pair-storage-item.h"

namespace std {

  template <template <typename> class VecType,
            template <typename> class PairStoreType>
  class DistanceEvalWStorageBase : public DistanceEvalBase<VecType> {

    public:

      typedef DistanceEvalWStorageBase<VecType,PairStoreType>   Type;

      typedef DistanceEvalBase<VecType>   ParentType;

    protected:

      PairStoreType<double>   DistSQPack;

    public:

      DistanceEvalWStorageBase() : ParentType(), DistSQPack() {}

      DistanceEvalWStorageBase(const Type&) {
        myError("Cannot create from Distance Evaluate Base With Storage");
      }

      ~DistanceEvalWStorageBase() { clear(); }

      Type& operator=(const Type& DEWS) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(DEWS));
        DistSQPack=DEWS.DistSQPack;
        return *this;
      }

      template <template <typename> class iVecType,
                template <typename> class iPSType>
      Type& operator=(const DistanceEvalWStorageBase<iVecType,iPSType>& DEWS) {
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

      PairStoreType<double>& DistanceSQStorage() { return DistSQPack; }

      const PairStoreType<double>& DistanceSQStorage() const {
        return DistSQPack;
      }

  };

}

#endif
