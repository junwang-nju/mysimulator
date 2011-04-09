
#ifndef _Matrix_Property_Compare_H_
#define _Matrix_Property_Compare_H_

#include "vector/interface.h"

namespace mysimulator {

    bool IsPropertySame(const Vector<unsigned int>& pa,
                        const Vector<unsigned int>& pb) {
      assert(IsValid(pa)&&IsValid(pb));
      if(pa.size!=pb.size)  return false;
      for(unsigned int i=0;i<pa.size;++i)
        if(pa[i]!=pb[i])  return false;
      return true;
    }

}

#endif

