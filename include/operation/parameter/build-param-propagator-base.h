
#ifndef _Build_Parameter_Propagator_Base_H_
#define _Build_Parameter_Propagator_Base_H_

#include "data/basic/unique-parameter.h"
#include "data/name/propagator-base.h"
#include <iostream>

namespace std {

  template <typename T>
  void BuildParameterPropagatorBase(UniqueParameter* GP) {
    copy(GP[HalfDeltaTime],0.5*GP[DeltaTime].value<T>());
    GP[CountOutput].u=
      static_cast<unsigned int>(
          GP[TotalTime].value<T>()/GP[OutputInterval].value<T>()+0.5);
    if(GP[CountOutput].u==0)  GP[CountOutput].u=1U;
    GP[CountStepsInOutput].u=
      static_cast<unsigned int>(
          GP[OutputInterval].value<T>()/GP[DeltaTime].value<T>()+0.5);
    if(GP[CountStepsInOutput].u==0) GP[CountStepsInOutput].u=1U;
  }

  template <template<typename,template<typename>class,typename> class IType,
            typename IdType, typename T, template<typename> class DBuffer,
            typename GeomType>
  void SetOutput(
      Vector<UniqueParameter>& P,
      void (*OFunc)(IType<T,DBuffer,GeomType>&,Vector<T>*,Vector<T>*,
                    Vector<T>*,const Vector<T>*,const IdType&,
                    Vector<UniqueParameter>&,Vector<UniqueParameter>*,
                    const unsigned int&,ostream&)) {
    P[OutputFunc].ptr=reinterpret_cast<void*>(OFunc);
  }

}

#include "data/basic/vector.h"

namespace std {

  template <typename T>
  void BuildParameterPropagatorBase(Vector<UniqueParameter>& GP) {
    assert(GP.size>=PropagatorBaseNumberParameter);
    BuildParameterPropagatorBase<T>(GP.data);
  }

}

#endif

