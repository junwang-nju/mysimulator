
#ifndef _Interaction_Kernel_Allocate_H_
#define _Interaction_Kernel_Allocate_H_

#include "interaction/kernel/interface.h"
#include "interaction/func/generic/allocate.h"
#include "interaction/geometry/allocate.h"

namespace mysimulator {

  template <template<typename> class DB, typename GT, typename T>
  void allocate(InteractionKernel<InteractionFuncGeneric<DB,GT,T>,DB,GT,T>& K,
                const InteractionFunctionName& itag, const unsigned int nunit,
                const unsigned int dim) {
    release(K);
    allocate(K.IF,itag);
    allocate(K.IG,nunit,dim);
  }

  template <template<typename> class DB, typename GT, typename T>
  void allocate(
      InteractionKernel<Vector<InteractionFuncGeneric<DB,GT,T> >,DB,GT,T>& K,
      const Vector<InteractionFunctionName>& tags, const unsigned int nunit,
      const unsigned int dim) {
    release(K);
    allocate(K.IF,tags.size);
    for(unsigned int i=0;i<tags.size;++i) allocate(K.IF[i],tags[i]);
    allocate(K.IG,nunit,dim);
  }

  template <typename IT, template<typename> class DB, typename GT, typename T>
  void imprint(InteractionKernel<IT,DB,GT,T>& K,
               const InteractionKernel<IT,DB,GT,T>& cK) {
    imprint(K.IF,cK.IF);
    imprint(K.IG,cK.IG);
  }

}

#endif

