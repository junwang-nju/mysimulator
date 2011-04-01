
#ifndef _InputOutput_Output_Base_Copy_H_
#define _InputOutput_Output_Base_Copy_H_

#include "io/output/interface.h"
#include "io/base/copy.h"

namespace mysimulator {

  void copy(OutputBase& B, const OutputBase& cB) {
    for(unsigned int i=0;i<NumberOutputFeature;++i) B.feature[i]=cB.feature[i];
    sprintf(B.FloatPat,"%s",cB.FloatPat);
    sprintf(B.DoublePat,"%s",cB.DoublePat);
    sprintf(B.LongDoublePat,"%s",cB.LongDoublePat);
    copy(static_cast<IOBase&>(B),static_cast<const IOBase&>(cB));
  }

}

#endif

