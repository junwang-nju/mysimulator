
#ifndef _Minimizer_Base_Import_H_
#define _Minimizer_Base_Import_H_

#include "minimizer/base/interface.h"
#include "vector/sum.h"
#include "referable-object/allocate.h"
#include "referable-object/copy.h"

namespace mysimulator {

  template <typename KT, template<typename> class VT,  typename PT, typename T>
  void import(MinimizerBase<KT,VT,PT,T>& M, const void* pFG, const void* pCoor, 
              const void* pP, const void* pmask) {
    if(pFG!=NULL) {
      const KT* FG=static_cast<const KT*>(pFG);
      assert(IsValid(*FG));
      imprint(M.MinFunc,*FG);
      copy(M.MinFunc,*FG);
    }
    if(pCoor!=NULL) {
      const VT<T>* Coor=static_cast<const VT<T>*>(pCoor);
      assert(IsValid(*Coor));
      imprint(M.MinX,*Coor);
      imprint(M.MinG,*Coor);
      copy(M.MinX,*Coor);
      imprint(M.MinMask,*Coor);
    }
    if(pP!=NULL) {
      const PT* P=static_cast<const PT*>(pP);
      assert(IsValid(*P));
      imprint(M.MinP,*P);
      copy(M.MinP,*P);
    }
    if(pmask!=NULL) {
      const VT<unsigned int>* umask=static_cast<const VT<unsigned int>*>(pmask);
      assert(IsValid(*umask));
      imprint(M.MinUMask,*umask);
      copy(M.MinUMask,*umask);
      M.DOF=asum(M.MinUMask);
      if(IsValid(M.MinMask))  copy(M.MinMask,*umask);
    }
  }

}

#endif

