
#ifndef _InputOutput_Output_Base_Copy_H_
#define _InputOutput_Output_Base_Copy_H_

#include "io/output/base/interface.h"
#include "io/base/copy.h"

namespace mysimulator {

  void copy(OutputBase& B, const OutputBase& cB) {
    assert(IsValid(cB));
    typedef OutputBase::ParentType Type;
    copy(static_cast<Type&>(B),static_cast<const Type&>(cB));
    for(unsigned int i=0;i<NumberOutputFeature;++i)
      B.feature[i]=cB.feature[i];
    for(unsigned int i=0;i<OutputBase::MaxSizePattern;++i) {
      B.FloatPat[i]=cB.FloatPat[i];
      B.DoublePat[i]=cB.DoublePat[i];
      B.LongDoublePat[i]=cB.LongDoublePat[i];
    }
  }

}

#endif

