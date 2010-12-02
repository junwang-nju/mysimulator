
#ifndef _Build_Parameter_Propagator_Base_H_
#define _Build_Parameter_Propagator_Base_H_

#include "data/basic/unique-parameter.h"
#include "data/name/parameter-propagator-base.h"

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

}

#endif

