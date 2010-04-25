
#ifndef _Fixed_Distance_Evaluate_With_Storage_H_
#define _Fixed_Distance_Evaluate_With_Storage_H_

#include "distance-evaluate-with-storage.h"
#include "fix-pair-storage.h"

namespace std {

  template <unsigned int Dim, unsigned int NUnits>
  class fixDistanceEvalWStorage
    : public DistanceEvalWStorage<refVector,refPairStorage> {

    public:

      typedef fixDistanceEvalWStorage<Dim,NUnits>   Type;

      typedef DistanceEvalWStorage<refVector,refPairStorage>  ParentType;

    protected:

      fixVector<double,1> inDistData;

      fixVector<double,Dim> inDispData;

      fixPairStorage<double,NUnits> inStorageData;

    public:

      fixDistanceEvalWStorage() : ParentType() {
        this->DistanceSQVec().refer(inDistData);
        this->Displacement().refer(inDispData);
        this->DistanceSQStorage().refer(inStorageData);
      }

      fixDistanceEvalWStorage(const Type&) {
        myError("Cannot create from Fixed Distance Storage With Storage");
      }

      ~fixDistanceEvalWStorage() {}

      Type& operator=(const Type& fDEWS) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(fDEWS));
        return *this;
      }

      template <template <typename> class VecType,
                template <typename> class PSType>
      Type& operator=(const DistanceEvalWStorage<VecType,PSType>& DEWS) {
        static_cast<ParentType*>(this)->operator=(DEWS);
        return *this;
      }

      void clear() {}

  };

}

#endif
