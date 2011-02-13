
#ifndef _Random_Generator_MT_Standard_Input_Output_H_
#define _Random_Generator_MT_Standard_Input_Output_H_

#include "data/random/random-generator-mt-standard.h"
#include "operation/basic/vector-io.h"

namespace std {

  OutputBase& operator<<(OutputBase& os, const MT_Standard& G) {
    assert(IsAvailable(G));
    os<<static_cast<const Vector<unsigned int>&>(G)<<"\t"<<*(G.mti);
    return os;
  }

  InputBase& operator>>(InputBase& is, MT_Standard& G) {
    assert(IsAvailable(G));
    is>>static_cast<Vector<unsigned int>&>(G)>>*(G.mti);
    return is;
  }

}

#endif
