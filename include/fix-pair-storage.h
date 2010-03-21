
#ifndef _Fixed_Pair_Storage_H_
#define _Fixed_Pair_Storage_H_

#include "pair-storage.h"
#include "fix-matrix-triangle.h"

namespace std {

  template <typename T, unsigned int NUnits>
  class fixPairStorage :public PairStorage<T,refMatrixTriangle,refVector> {

    public:

      typedef fixPairStorage<T,NUnits>   Type;

      typedef PairStorage<T,refMatrixTriangle,refVector>  ParentType;

    protected:

      fixVector<unsigned int,1> inGStatus;

      fixMatrixTriangle<PairItem<T>,NUnits,false> inData;
      
      void initStatic() {
        this->GStatusVec().refer(inGStatus);
        this->DataMat().refer(inData);
        this->GStatusVec()[0]=1;
      }

    public:
    
      fixPairStorage() : ParentType(), inGStatus(),inData() {
        inData.initAs();
        initStatic();
      }
      
      fixPairStorage(const Type&) {
        myError("Cannot create from fixed Pair Storage");
      }
      
      ~fixPairStorage() {}
      
      void clear() { this->Inc(); }

      Type& operator=(const Type& fPS) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(fPS));
        return *this;
      }

  };

}

#endif

