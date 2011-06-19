
#ifndef _Interaction_Kernel_Allocate_H_
#define _Interaction_Kernel_Allocate_H_

#include "interaction/kernel/interface.h"
#include "interaction/kernel/unit/allocate.h"
#include "vector/allocate.h"

namespace mysimulator {

  template <template<typename> class DBuffer, typename GeomType, typename T>
  void allocate(InteractionKernel<DBuffer,GeomType,T>& K,
                const InteractionFunctionName& itag, const unsigned int nunit,
                const unsigned int dim, ...) {
    release(K);
    allocate(K.iunit,1);
    allocate(K.iunit[0],itag);
    allocate(K.DB,dim,nunit);
    allocate(K.Geo,dim);
  }

  template <template<typename> class DBuffer, typename GeomType, typename T>
  void allocate(InteractionKernel<DBuffer,GeomType,T>& K,
                const Vector<InteractionFunctionName>& tagvec,
                const unsigned int nunit, const unsigned int dim,...) {
    release(K);
    allocate(K.iunit,tagvec.size);
    for(unsigned int i=0;i<K.iunit.size;++i)  allocate(K.iunit[i],tagvec[i]);
    allocate(K.DB,dim,nunit);
    allocate(K.Geo,dim);
  }

  template <template<typename> class DBuffer, typename GeomType, typename T>
  void imprint(InteractionKernel<DBuffer,GeomType,T>& K,
               const InteractionKernel<DBuffer,GeomType,T>& cK) {
    release(K);
    imprint(K.iunit,cK.iunit);
    allocate(K.DB,cK.Dimension(),cK.NumUnit());
    allocate(K.Geo,cK.Dimension());
  }

}

#endif

