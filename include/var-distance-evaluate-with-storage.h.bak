
#ifndef _Variable_Distance_Evaluate_With_Storage_H_
#define _Variable_Distance_Evaluate_With_Storage_H_

#include "distance-evaluate-with-storage-base.h"
#include "var-pair-storage.h"

namespace std {

  class varDistanceEvalWStorage
    : public DistanceEvalWStorageBase<varVector,varPairStorage> {

    public:

      typedef varDistanceEvalWStorage   Type;

      typedef DistanceEvalWStorageBase<varVector,varPairStorage>  ParentType;

      varDistanceEvalWStorage() : ParentType() {}

      varDistanceEvalWStorage(const unsigned int Dim, const unsigned int NU)
        : ParentType() {
        allocate(Dim,NU);
      }

      varDistanceEvalWStorage(const Type&) {
        myError("Cannot create from variable Distance Evaluate With Storage");
      }

      ~varDistanceEvalWStorage() {}

      Type& operator=(const Type& vDEWS) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(vDEWS));
        return *this;
      }

      template <template <typename> class VecType,
                template <typename> class PSType>
      Type& operator=(const DistanceEvalWStorageBase<VecType,PSType>& DEWS) {
        static_cast<ParentType*>(this)->operator=(DEWS);
        return *this;
      }

      void allocate(const unsigned int Dim, const unsigned int NUnits) {
        this->DistanceSQVec().allocate(1);
        this->Displacement().allocate(Dim);
        this->DistanceSQStorage().allocate(NUnits);
      }

  };

}

#endif
 
