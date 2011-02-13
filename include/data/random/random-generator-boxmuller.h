
#ifndef _Random_Generator_BoxMuller_H_
#define _Random_Generator_BoxMuller_H_

#include "data/basic/vector.h"

namespace std {

  template <typename UniformRNG>
  struct BoxMuller : public Vector<double> {
    UniformRNG  *urng;
    bool *isSecond;
    double output;

    typedef BoxMuller<UniformRNG> Type;
    typedef Vector<double>  ParentType;

    BoxMuller() : ParentType(), urng(NULL), isSecond(NULL), output(0) {}
    BoxMuller(const Type& G) { Error("Cannot create BoxMuller Generator"); }
    Type& operator=(const Type& G) {
      Error("Cannot copy BoxMuller Generator");
      return *this;
    }
    ~BoxMuller() { release(*this); }

  };

  template <typename UniformRNG>
  bool IsAvailable(const BoxMuller<UniformRNG>& G) {
    return IsAvailable(static_cast<const Vector<double>&>(G));
  }
  template <typename UniformRNG>
  bool IsRandomGenerator(const BoxMuller<UniformRNG>& G) { return true; }

  template <typename UniformRNG>
  void release(BoxMuller<UniformRNG>& G) {
    if(G.state==Allocated) {
      safe_delete(G.urng);
      safe_delete(G.isSecond);
    } else {
      G.urng=NULL;
      G.isSecond=NULL;
    }
    release(static_cast<Vector<double>&>(G));
  }
  template <typename UniformRNG>
  void copy(BoxMuller<UniformRNG>& G,const BoxMuller<UniformRNG>& cG) {
    assert(IsAvailable(G));
    assert(IsAvailable(cG));
    copy(*(G.urng),*(cG.urng));
    *(G.isSecond)=*(cG.isSecond);
    copy(static_cast<Vector<double>&>(G),
         static_cast<const Vector<double>&>(cG));
  }
  template <typename UniformRNG>
  void allocate(BoxMuller<UniformRNG>& G) {
    release(G);
    G.urng=new UniformRNG;
    allocate(*(G.urng));
    G.isSecond=new bool;
    allocate(static_cast<Vector<double>&>(G),3);
    *(G.isSecond)=true;
  }
  template <typename UniformRNG>
  void refer(BoxMuller<UniformRNG>& G, const BoxMuller<UniformRNG>& rG) {
    assert(IsAvailable(rG));
    G.urng=rG.urng;
    G.isSecond=rG.isSecond;
    refer(static_cast<Vector<double>&>(G),
          static_cast<const Vector<double>&>(rG));
  }

}

#endif

