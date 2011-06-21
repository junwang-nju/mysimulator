
#ifndef _Minimizer_Base_Import_H_
#define _Minimizer_Base_Import_H_

#include "minimizer/base/interface.h"
#include "vector/sum.h"
#include "vector/allocate.h"

namespace mysimulator {

  template <typename KT, template<typename> class VT,  typename PT, typename T>
  void import(MinimizerBase<KT,VT,PT,T>& M,const KT* FG, const VT<T>* Coor, 
              const PT* P, const VT<unsigned int>* umask) {
    if(FG!=NULL) {
      assert(IsValid(*FG));
      imprint(M.MinFunc,*FG);
      copy(M.MinFunc,*FG);
    }
    if(Coor!=NULL) {
      assert(IsValid(*Coor));
      imprint(M.MinX,*Coor);
      imprint(M.MinG,*Coor);
      copy(M.MinX,*Coor);
      imprint(M.MinMask,*Coor);
    }
    if(P!=NULL) {
      assert(IsValid(*P));
      imprint(M.MinP,*P);
      copy(M.MinP,*P);
    }
    if(umask!=NULL) {
      assert(IsValid(*umask));
      imprint(M.MinUMask,*umask);
      copy(M.MinUMask,*umask);
      M.DOF=asum(M.MinUMask);
      if(IsValid(M.MinMask))  copy(M.MinMask,*umask);
    }
  }

}

#endif

