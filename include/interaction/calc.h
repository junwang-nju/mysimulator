
#ifndef _Interaction_Calc_H_
#define _Interaction_Calc_H_

#include "interaction/kernel/interface.h"
#include "interaction/parameter/unit/interface.h"
#include "interaction/func/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class DBuffer,typename GeomType>
  void Calc(InteractionKernel<DBuffer,GeomType,T>& K, const Vector<T>* X,
            const InteractionParameterUnit& P, T& Energy) {
    for(unsigned int i=0;i<K.iunit.size;++i)
      K.iunit[i].EFunc(X,P.idx.pdata,P.prm.pdata,K.DB,K.Geo,Energy,
                       K.iunit[i].tmvec.infra.pdata);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType>
  void Calc(InteractionKernel<DBuffer,GeomType,T>& K, const Vector<T>* X,
            const InteractionParameterUnit& P, Vector<T>* Gradient) {
    for(unsigned int i=0;i<K.iunit.size;++i)
      K.iunit[i].GFunc(X,P.idx.pdata,P.prm.pdata,K.DB,K.Geo,Gradient,
                       K.iunit[i].tmvec.infra.pdata);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType>
  void Calc(InteractionKernel<DBuffer,GeomType,T>& K, const Vector<T>* X,
            const InteractionParameterUnit& P, T& Energy,Vector<T>* Gradient) {
    for(unsigned int i=0;i<K.iunit.size;++i)
      K.iunit[i].BFunc(X,P.idx.pdata,P.prm.pdata,K.DB,K.Geo,Energy,Gradient,
                       K.iunit[i].tmvec.infra.pdata);
  }

}

#endif

