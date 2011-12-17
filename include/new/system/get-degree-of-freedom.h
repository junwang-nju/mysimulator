
#ifndef _System_Get_DegreeOfFreeDom_H_
#define _System_Get_DegreeOfFreeDom_H_

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

#include "system/grouping/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VecType,
            template<typename,template<typename>class> class SCT>
  unsigned int _DegreeOfFreedom(
      const Array1DContent<SysGrouping<T,IDT,PT,GT,VecType,SCT> >& SG) {
    assert(IsValid(SG));
    unsigned int dof=0;
    for(unsigned int i=0;i<SG.size;++i) {
      switch(SG[i].Method) {
        case SystemFixPosition:
          break;
        case SystemMinimizerLineRegular:
          for(unsigned int j=0;j<SG[i].grpContent.size;++j)
            dof+=DegreeOfFreedom(SG[i].grpContent[j].X());
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

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  unsigned int DegreeOfFreedom(const System<T,IDT,PT,GT,VT,SCT>& S) {
    return _DegreeOfFreedom(S.Groups);
  }

}

#endif

