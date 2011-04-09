
#ifndef _Matrix_Property_Compare_H_
#define _Matrix_Property_Compare_H_

#include "vector/interface.h"

namespace mysimulator {

    bool IsPropertySame(const vector<unsigned int>& pa,
                        const vector<unsigned int>& pb) {
      assert(IsValid(pa)&&IsValid(pb));
      if(pa.size!=pb.size)  return false;
      for(unsigned int i=0;i<pa.size;++i)
        if(pa[i]!=pb[i])  return false;
      return true;
    }

}

#endif

