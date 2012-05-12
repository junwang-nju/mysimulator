
#ifndef _System_Degree_Of_Freedom_H_
#define _System_Degree_Of_Freedom_H_

#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  unsigned int DegreeOfFreedom(const Array1D<T>& X) { return X.Size(); }

}

#include "array/2d/interface.h"

namespace mysimulator {

  template <typename T>
  unsigned int DegreeOfFreedom(const Array2D<T>& X) {
    return DegreeOfFreedom(X._ldata);
  }

}

#include "system/propagator/interface.h"

namespace mysimulator {

  template <typename T,template<typename> class CT>
  unsigned int _DegreeOfFreedom(const Array1D<SystemPropagator<T,CT> >& P) {
    unsigned int dof=0;
    for(unsigned int i=0;i<P.Size();++i) {
      switch(P[i].Method) {
        case SystemFixPosition: break;
        case SystemToBeDetermined:
        case SystemMinimizerLineRegular:
          for(unsigned int k=0;k<P[i].GrpContent.Size();++k)
            dof+=DegreeOfFreedom(P[i].GrpContent[k].X);
          break;
        default:
          fprintf(stderr,"Unknown Method to Get Degree-Of-Freedom!\n");
      }
    }
    return dof;
  }

}

#include "system/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT>
  unsigned int DegreeOfFreedom(const System<T,IDT,PT,GT,BT,CT>& S) {
    return _DegreeOfFreedom(S.Propagtors);
  }

}

#endif

