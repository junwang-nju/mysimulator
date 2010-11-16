
#ifndef _Periodic_Box_H_
#define _Periodic_Box_H_

#include "data/name/geometry-name.h"
#include "operation/basic/vector-op.h"

namespace std {

  template <typename T>
  struct PeriodicBox : public Vector<T> {
    typedef PeriodicBox<T>  Type;
    typedef Vector<T>       ParentType;
    
    static const unsigned int Name;
    
    Vector<T> halfBox;
    Vector<bool> edgeFlag;
    
    PeriodicBox() : ParentType(), halfBox(), edgeFlag() {}
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
    release(G.halfBox);
    release(G.edgeFlag);
    release(static_cast<Vector<T>&>(G));
  }

  template <typename T>
  void copy(PeriodicBox<T>& G, const PeriodicBox<T>& cG) {
    assert(IsAvailable(G));
    assert(IsAvailable(cG));
    copy(static_cast<Vector<T>&>(G),static_cast<const Vector<T>&>(cG));
    copy(G.halfBox,cG.halfBox);
    copy(G.edgeFlag,cG.edgeFlag);
  }

  template <typename T>
  void allocate(PeriodicBox<T>& G, const unsigned int dim) {
    allocate(static_cast<Vector<T>&>(G),dim);
    allocate(G.halfBox,dim);
    allocate(G.edgeFlag,dim);
  }
  
  template <typename T>
  void refer(PeriodicBox<T>& G, const PeriodicBox<T>& rG) {
    assert(IsAvailable(rG));
    refer(static_cast<Vector<T>&>(G),static_cast<const Vector<T>&>(rG));
    refer(G.halfBox,rG.halfBox);
    refer(G.edgeFlag,rG.edgeFlag);
  }

  void synchronize(PeriodicBox<double>& G) {
    assert(IsAvailable(G));
    copy(G.halfBox,static_cast<Vector<double>&>(G));
    scale(G.halfBox,0.5);
  } 

  void synchronize(PeriodicBox<float>& G) {
    assert(IsAvailable(G));
    copy(G.halfBox,static_cast<Vector<float>&>(G));
    scale(G.halfBox,0.5);
  }

}

#endif
