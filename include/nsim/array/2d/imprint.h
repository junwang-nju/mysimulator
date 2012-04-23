
#ifndef _Array_2d_Imprint_H_
#define _Array_2d_Imprint_H_

#include "array/2d/interface.h"
#include "array/1d/imprint.h"

namespace mysimulator {

  template <typename T1,typename T2>
  void ImprintStructure(Array2D<T1>& V,const Array2D<T2>& V2) {
    Clear(V);
    typedef typename Array2D<T1>::ParentType  Type;
    ImprintStructure(static_cast<Type&>(V),static_cast<const Type&>(V2));
    ImprintStructure(V._ldata,V2._ldata);
    for(unsigned int i=0,m=0;i<V.Size();m+=V2[i].Size(),++i)
      V[i].Refer(V._ldata,m,V2[i].Size());
  }

  template <typename T>
  void Imprint(Array2D<T>& V,const Array2D<T>& V2) {
    Clear(V);
    typedef typename Array2D<T>::ParentType  Type;
    ImprintStructure(static_cast<Type&>(V),static_cast<const Type&>(V2));
    Imprint(V._ldata,V2._ldata);
    for(unsigned int i=0,m=0;i<V.Size();m+=V2[i].Size(),++i)
      V[i].Refer(V._ldata,m,V2[i].Size());
  }

}

#endif

