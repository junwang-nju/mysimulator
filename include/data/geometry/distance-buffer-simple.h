
#ifndef _Distance_Buffer_H_
#define _Distance_Buffer_H_

#include "data/basic/unique-parameter.h"
#include "data/name/distance-buffer-name.h"

namespace std {

  template <typename T>
  struct DistanceBufferSimple : public Vector<UniqueParameter> {
    typedef DistanceBufferSimple  Type;
    typedef Vector<UniqueParameter> ParentType;
    
    Vector<T> DisplaceVec;

    DistanceBufferSimple() : ParentType(), DisplaceVec() {}
    DistanceBufferSimple(const Type& B) {
      myError("Cannot create Simple Distance Buffer");
    }
    Type& operator=(const Type& B) {
      myError("Cannot copy Simple Distance Buffer");
      return *this;
    }
    ~DistanceBufferSimple() { release(*this); }

    unsigned int& NumberOfUnits() { return this->operator[](NumberUnit).u; }
    const unsigned int& NumberOfUnits() const {
      return this->operator[](NumberUnit).u;
    }
    T& DistanceSquare() { return this->operator[](DistanceSQ).value<T>(); }
    const T& DistanceSquare() const {
      return this->operator[](DistanceSQ).value<T>();
    }
    const unsigned int Dimension() const { return DisplaceVec.size; }

    void renew() {}

  };

  template <typename T>
  bool IsAvailable(const DistanceBufferSimple<T>& B) {
    return IsAvailable(static_cast<const Vector<UniqueParameter>&>(B));
  }

  template <typename T>
  bool IsDistanceBuffer(const DistanceBufferSimple<T>& B) { return true; }

  template <typename T>
  void release(DistanceBufferSimple<T>& B) {
    release(B.DisplaceVec);
    release(static_cast<Vector<UniqueParameter>&>(B));
  }

  template <typename T, typename cT>
  void copy(DistanceBufferSimple<T>& B, const DistanceBufferSimple<cT>& cB) {
    copy(B.DisplaceVec,cB.DisplaceVec);
    copy(static_cast<Vector<UniqueParameter>&>(B),
         static_cast<const Vector<UniqueParameter>&>(cB));
  }

  template <typename T>
  void allocate(DistanceBufferSimple<T>& B, const unsigned int dim,
                                            const unsigned int nunit) {
    allocate(B.DisplaceVec,dim);
    allocate(static_cast<Vector<UniqueParameter>&>(B),SimpleBufferSize);
    copy(B[NumberUnit],nunit);
  }

  template <typename T>
  void refer(DistanceBufferSimple<T>& B, const DistanceBufferSimple<T>& rB) {
    refer(B.DisplaceVec,rB.DisplaceVec);
    refer(static_cast<Vector<UniqueParameter>&>(B),
          static_cast<const Vector<UniqueParameter>&>(rB));
  }

}

#endif
