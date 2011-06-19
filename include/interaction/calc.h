
#ifndef _Interaction_Calc_H_
#define _Interaction_Calc_H_

#include "interaction/kernel/interface.h"
#include "interaction/parameter/unit/interface.h"
#include "interaction/func/interface.h"

namespace mysimulator {

  template <typename T, InteractionFunctionName ItType,
            template<typename> class DBuffer,typename GeomType>
  void Calc(InteractionKernel<ItType,DBuffer,GeomType,T>& K,
            const Vector<T>* X, const InteractionParameterUnit& P,
            T& Energy) {
    InteractionFunc<ItType,DBuffer,GeomType,T>::Energy(X,P.idx.pdata,
        P.prm.pdata,K.DB,K.Geo,Energy,K.tmvec.infra.pdata);
  }

  template <typename T, InteractionFunctionName ItType,
            template<typename> class DBuffer,typename GeomType>
  void Calc(InteractionKernel<ItType,DBuffer,GeomType,T>& K,
            const Vector<T>* X, const InteractionParameterUnit& P,
            Vector<T>* Gradient) {
    InteractionFunc<ItType,DBuffer,GeomType,T>::Gradient(X,P.idx.pdata,
        P.prm.pdata,K.DB,K.Geo,Gradient,K.tmvec.infra.pdata);
  }

  template <typename T, InteractionFunctionName ItType,
            template<typename> class DBuffer,typename GeomType>
  void Calc(InteractionKernel<ItType,DBuffer,GeomType,T>& K,
            const Vector<T>* X, const InteractionParameterUnit& P,
            T& Energy, Vector<T>* Gradient) {
    InteractionFunc<ItType,DBuffer,GeomType,T>::Both(X,P.idx.pdata,
        P.prm.pdata,K.DB,K.Geo,Energy,Gradient,K.tmvec.infra.pdata);
  }

}

#endif

