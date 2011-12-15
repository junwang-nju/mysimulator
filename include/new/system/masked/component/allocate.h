
#ifndef _System_Masked_Component_Allocate_H_
#define _System_Masked_Component_Allocate_H_

#include  "system/masked/component/interface.h"

namespace mysimulator {

  template <typename T1, typename T2, template<typename> class SpaceType>
  void allocate(Mask4System<T1,SpaceType>& M, const SpaceType<T2>& v) {
    assert(IsValid(v));
    imprint(M.iMask,v);
    imprint(M.Mask,v);
    fill(M.iMask,uOne);
    fill(M.Mask,uOne);
  }

  template <typename T1, typename T2, template<typename> class SpaceType>
  void allocate(Mask4System<T1,SpaceType>& M, const Object<SpaceType<T2> >& v) {
    allocate(M,v());
  }

  template <typename T1, typename T2, template<typename> class SpaceType>
  void imprint(Mask4System<T1,SpaceType>& M,
               const Mask4System<T2,SpaceType>& cM) {
    assert(IsValid(cM));
    allocate(M,cM.iMask);
  }

}

#include "array/2d/fill.h"

namespace mysimulator {

  template <typename T>
  void allocate(Mask4System<T,Array2D>& M, const unsigned int& n,
                const unsigned int& dim, const unsigned int& fg=1U) {
    allocate(M.iMask,n,dim);
    allocate(M.Mask,n,dim);
    fill(M.iMask,fg);
    fill(M.Mask,fg);
  }

}

#endif

