
#ifndef _Propagator_Run_H_
#define _Propagator_Run_H_

#include "data/propagator/propagator.h"
#include "data/basic/console-output.h"

namespace std {

  template <typename T, typename ParameterType,
            template<typename,template<typename>class,typename> class IType,
            template <typename> class DBuffer, typename GeomType>
  void Run(Propagator<T>& P,
           IType<T,DBuffer,GeomType>& F, ParameterType& Pm,
           OutputBase& os=COut) {
    typedef void (*MoveFunc)(Propagator<T>&,IType<T,DBuffer,GeomType>&,
                             ParameterType&);
    typedef void (*OutputFunc)(Propagator<T>&,IType<T,DBuffer,GeomType>&,
                               ParameterType&,OutputBase&);
    reinterpret_cast<OutputFunc>(P[PgOutput].ptr)(P,F,Pm,os);
    for(unsigned int i=0;i<P[NumberOutput].u;++i) {
      for(unsigned int k=0;k<P[NumberStepInOneOutput].u;++k)
        reinterpret_cast<MoveFunc>(P[PgStep].ptr)(P,F,Pm);
      static_cast<UniqueParameter&>(P[NowTime]).value<T>()+=
        static_cast<UniqueParameter&>(P[OutputInterval]).value<T>();
      reinterpret_cast<OutputFunc>(P[PgOutput].ptr)(P,F,Pm,os);
    }
  }

}

#endif

