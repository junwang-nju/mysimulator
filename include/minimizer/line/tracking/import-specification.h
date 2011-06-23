
#ifndef _Minimizer_Line_Tracking_Import_Specification_H_
#define _Minimizer_Line_Tracking_Import_Specification_H_

#include "minimizer/line/tracking/specification.h"
#include "minimizer/line/common/import.h"

namespace mysimulator {

  template <typename KT, template<typename> class VT,  typename PT, typename T>
  void import(LineMinimizer<TrackingMethod,KT,VT,PT,T>& L,const KT* FG,
              const VT<T>* Coor,const PT* P, const VT<unsigned int>* umask) {
    typedef LineMinimizerCommon<KT,VT,PT,T> Type;
    import(static_cast<Type&>(L),FG,Coor,P,umask);
  }

}

#endif

