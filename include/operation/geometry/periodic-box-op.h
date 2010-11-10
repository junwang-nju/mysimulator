
#ifndef _Operation_for_Periodic_Box_H_
#define _Operation_for_Periodic_Box_H_

#include "data/geometry/periodic-box.h"

namespace std {

  template <typename T, typename TB, typename TF>
  void set(PeriodicBox<T>& G, const Vector<TB>& box, const TF& flag){
    assert(IsAvailable(G));
    assert(IsAvailable(box)&&IsAvailable(flag));
    copy(static_cast<Vector<T>&>(G),box);
    copy(G.edgeFlag,flag);
    synchronize(G);
  }

  template <typename TV, typename T>
  void relocateVector(TV* v, const unsigned int dim, const PeriodicBox<T>& G,
                      const int off=iZero, const long step=lOne) {
    assert(IsAvailable(v));
    assert(IsAvailable(G));
    unsigned int n=(G.size<dim?G.size:dim);
    T* pv=v+off;
    for(unsigned int i=0;i<n;++i,pv+=step) {
      while(*pv<-G.halfBox[i]) shift(*pv,iOne,G[i]);
      while(*pv>=G.halfBox[i]) shift(*pv,-iOne,G[i]);
    }
  }

  template <typename TV, typename T>
  void relocateVector(Vector<TV>& v, const PeriodicBox<T>& G) {
    assert(IsAvailable(v));
    assert(IsAvailable(G));
    unsigned int n=(G.size<v.size?G.size:v.size);
    for(unsigned int i=0;i<n;++i) {
      while(v[i]<-G.halfBox[i]) shift(v[i],iOne,G[i]);
      while(v[i]>=G.halfBox[i]) shift(v[i],-iOne,G[i]);
    }
  }

}

#endif

