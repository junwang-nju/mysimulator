
#ifndef _Boundary_PeriodicBox_Interface_H_
#define _Boundary_PeriodicBox_Interface_H_

#include "vector/interface.h"

namespace mysimulator {

  template <typename T>
  struct PeriodicBox {

    typedef PeriodicBox<T>    Type;

    Vector<T> box;
    Vector<T> hbox;
    Vector<bool>  edgeFlag;

    PeriodicBox() : box(), hbox(), edgeFlag() {}
    PeriodicBox(const Type&) { Error("Copier of PeriodicBox Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for PeriodicBox Disabled!");
      return *this;
    }
    ~PeriodicBox() { clearData(); }

  };

}

#endif

