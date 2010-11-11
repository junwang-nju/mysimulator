
#ifndef _Distance_Buffer_PairStorage_H_
#define _Distance_Buffer_PairStorage_H_

#include "data/geometry/distance-buffer-simple.h"
#include "data/derived/pair-information.h"

namespace std {

  template <typename T>
  struct DistanceBufferPairStorage : public DistanceBufferSimple<T> {
    typedef DistanceBufferPairStorage<T>  Type;
    typedef DistanceBufferSimple<T> ParentType;

    PairStorage<T> DsqMat;

    DistanceBufferPairStorage() : ParentType(), DsqMat() {}
    DistanceBufferPairStorage(const Type& B) {
      myError("Cannot create Distance Buffer with Pair Storage");
    }
    Type& operator=(const Type& B) {
      myError("Cannot copy Distance Buffer with Pair Storage");
      return *this;
    }
    ~DistanceBufferPairStorage() { release(*this); }

    void renew() { DsqMat.refresh(); }

  };

  template <typename T>
  bool IsAvailable(const DistanceBufferPairStorage<T>& B) {
    return IsAvailable(static_cast<const DistanceBufferSimple<T>&>(B));
  }

  template <typename T>
  bool IsDistanceBuffer(const DistanceBufferPairStorage<T>& B) { return true; }

  template <typename T>
  void release(DistanceBufferPairStorage<T>& B) {
    release(static_cast<DistanceBufferSimple<T>&>(B));
    release(B.DsqMat);
  }

  template <typename T, typename cT>
  void copy(DistanceBufferPairStorage<T>& B,
            const DistanceBufferPairStorage<cT>& cB) {
    assert(IsAvailable(B));
    assert(IsAvailable(cB));
    copy(static_cast<DistanceBufferSimple<T>&>(B),
         static_cast<const DistanceBufferSimple<cT>&>(cB));
    copy(B.DsqMat,cB.DsqMat);
  }

  template <typename T>
  void ecopy(DistanceBufferPairStorage<T>& B,
             const DistanceBufferPairStorage<T>& cB) {
    assert(IsAvailable(B));
    assert(IsAvailable(cB));
    copy(static_cast<DistanceBufferSimple<T>&>(B),
         static_cast<const DistanceBufferSimple<T>&>(cB));
    ecopy(B.DsqMat,cB.DsqMat);
  }

  template <typename T>
  void allocate(DistanceBufferPairStorage<T>& B,
                const unsigned int dim, const unsigned int nunit) {
    allocate(static_cast<DistanceBufferSimple<T>&>(B),dim,nunit);
    allocate(B.DsqMat,nunit);
  }

  template <typename T>
  void refer(DistanceBufferPairStorage<T>& B,
             const DistanceBufferPairStorage<T>& rB) {
    refer(static_cast<DistanceBufferSimple<T>&>(B),
          static_cast<const DistanceBufferSimple<T>&>(rB));
    refer(B.DsqMat,rB.DsqMat);
  }

}

#endif

