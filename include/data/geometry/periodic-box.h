
#ifndef _Periodic_Box_H_
#define _Periodic_Box_H_

#include "data/name/geometry-name.h"
#include "vector.h"

namespace std {

  template <typename T>
  struct PeriodicBox : public Vector<T> {
    typedef PeriodicBox<T>  Type;
    typedef Vector<T>       ParentType;
    
    static const unsigned int Name;
    
    T* halfBox;
    bool* edgeFlag
    
    PeriodicBox() : ParentType(), halfBox(NULL), edgeFlag(NULL) {}
    PeriodicBox(const Type& G) { myError("Cannot create Periodic Box"); }
    Type& operator=(const Type& G) {
      myError("Cannot copy Periodic Box");
      return *this;
    }
    ~PeriodicBox() { release(*this); }
  };

  template <typename T>
  const unsigned int PeriodicBox<T>::Name=PeriodicBoxGeometry;

  template <typename T>
  bool IsAvailable(const PeriodicBox<T>& G) {
    return IsAvailable(static_cast<const Vector<T>&>(G));
  }

  template <typename T>
  bool IsGeometry(const PeriodicBox<T>& G) { return true; }

  template <typename T>
  void release(PeriodicBox<T>& G) {
    if(G.state==Allocated) {
      safe_delete_array(halfBox);
      safe_delete_array(edgeFlag);
    } else {
      halfBox=NULL;
      edgeFlag=NULL;
    }
    release(static_cast<Vector<T>&>(G));
  }

}

#endif
