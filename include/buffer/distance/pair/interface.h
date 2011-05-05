
#ifndef _Buffer_Distance_Pair_Interface_H_
#define _Buffer_Distance_Pair_Interface_H_

#include "buffer/distance/base/interface.h"
#include "matrix/storage/interface.h"

namespace mysimulator {

  template <typename T>
  struct PairDistanceBuffer : public DistanceBufferBase<T> {

    typedef PairDistanceBuffer<T>   Type;
    typedef DistanceBufferBase<T>   ParentType;

    MatrixStorage<T> DSqMat;

    PairDistanceBuffer() : ParentType(), DSqMat() {}
    PairDistanceBuffer(const Type&) {
      Error("Copier of PairDistanceBuffer Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for PairDistanceBuffer Disabled!");
    }
    ~PairDistanceBuffer() { clearData(); }

    void clearData() {
      DSqMat.clearData();
      static_cast<ParentType*>(this)->clearData();
    }

    virtual void renew() { DSqMat.unlock(); }

  };

  template <typename T>
  bool IsValid(const PairDistanceBuffer<T>& B) {
    return IsValid(B.DSqMat)&&
           IsValid(static_cast<const DistanceBufferBase<T>&>(B));
  }

  template <typename T>
  void release(PairDistanceBuffer<T>& B) { B.clearData(); }

}

#endif

