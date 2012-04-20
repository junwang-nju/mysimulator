
#ifndef _System_Get_DegreeFreedom_H_
#define _System_Get_DegreeFreedom_H_

#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T>
  unsigned int DegreeOfFreedom(const Array1DContent<T>& X) { return X.size; }

}

#include "array/2d/content/interface.h"

namespace mysimulator {

  template <typename T>
  unsigned int DegreeOfFreedom(const Array2DContent<T>& X) {
    return DegreeOfFreedom(X.base);
  }

}

#include "system/propagate/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  unsigned int _DegreeOfFreeDom(
      const Array1DContent<SysPropagate<T,VT,SCT> >& SE) {
    assert(IsValid(SE));
    unsigned int dof=0;
    for(unsigned int i=0;i<SE.size;++i) {
      switch(SE[i].Method) {
        case SysFixPosition:
          break;
        case SysToBeDetermined:
        case SysMinimizerLineRegular:
          for(unsigned int j=0;j<SE[i].grpContent.size;++j)
            dof+=DegreeOfFreedom(SE[i].grpContent[j].X());
          break;
        default:
          Error("Unknown Method to Determine Degree of Freedom!");
      }
    }
    return dof;
  }

}

#include "system/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  unsigned int DegreeOfFreedom(const System<T,IDT,PT,GT,BT,VT,SCT>& S) {
    return _DegreeOfFreeDom(S.Propagates);
  }

}

#endif

