
#ifndef _List_Compare_H_
#define _List_Compare_H_

#include "list/interface.h"
#include "vector/compare.h"

namespace mysimulator {

  template <typename Ta, typename Tb>
  bool IsSameStructure(const List<Ta>& La, const List<Tb>& Lb) {
    if(!IsSameStructure(La.infra,Lb.infra))   return false;
    for(unsigned int i=0;i<La.ListSize();++i)
      if(!IsSameStructure(La.infra[i],Lb.infra[i]))   return false;
    return true;
  }

}

#endif

