
#ifndef _Buffer_Distance_Simple_Interface_H_
#define _Buffer_Distance_Simple_Interface_H_

#include "buffer/distance/base/interface.h"

namespace mysimulator {

  template <typename T>
  struct SimpleDistanceBuffer : public DistanceBufferBase<T> {

    typedef SimpleDistanceBuffer<T> Type;
    typedef DistanceBufferBase<T>   ParentType;

    SimpleDistanceBuffer() : ParentType() {}
    SimpleDistanceBuffer(const Type&) {
      Error("Copier of SimpleDistanceBuffer Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for SimpleDistanceBuffer Disabled!");
      return *this;
    }
    ~SimpleDistanceBuffer() { clearData(); }

    void clearData() { static_cast<ParentType*>(this)->clearData(); }
    virtual void renew() {}

  };

  template <typename T>
  bool IsValid(const SimpleDistanceBuffer<T>& B) {
    return IsValid(static_cast<const DistanceBufferBase<T>&>(B));
  }

  template <typename T>
  void release(SimpleDistanceBuffer<T>& B) { B.clearData(); }

}

#endif

