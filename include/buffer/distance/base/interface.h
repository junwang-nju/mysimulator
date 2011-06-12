
#ifndef _Buffer_Distance_Base_Interface_H_
#define _Buffer_Distance_Base_Interface_H_

#include "buffer/distance/base/data-name.h"
#include "vector/interface.h"
#include "unique-parameter/64bit/interface.h"

namespace mysimulator {

  template <typename T>
  struct DistanceBufferBase {

    typedef DistanceBufferBase<T> Type;

    Vector<UniqueParameter64Bit> data;
    Vector<T> DisplaceVector;

    DistanceBufferBase() : data(), DisplaceVector() {}
    DistanceBufferBase(const Type&) {
      Error("Copier of DistanceBufferBase Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for DistanceBufferBase Disabled!");
      return *this;
    }
    ~DistanceBufferBase() { clearData(); }

    void clearData() { data.clearData(); DisplaceVector.clearData(); }
    virtual void renew()=0;

    unsigned int& UnitNumber() {
      return data[DBBase_UnitNumber].value<unsigned int>();
    }
    T& DistanceSquare() { return data[DBBase_DistanceSQ].value<T>(); }
    const unsigned int& UnitNumber() const {
      return data[DBBase_UnitNumber].value<unsigned int>();
    }
    const T& DistanceSquare() const {
      return data[DBBase_DistanceSQ].value<T>();
    }
    const unsigned int Dimension() const { return DisplaceVector.size; }

  };

  template <typename T>
  bool IsValid(const DistanceBufferBase<T>& B) {
    return IsValid(B.data)&&IsValid(B.DisplaceVector);
  }

}

#endif

