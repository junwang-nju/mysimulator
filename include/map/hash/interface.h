
#ifndef _Map_Element_Hash_Interface_H_
#define _Map_Element_Hash_Interface_H_

#include "io/error.h"
#include "intrinsic-type/constant.h"
#include "intrinsic-type/copy.h"

namespace mysimulator {

  template <unsigned int NumHashValue>
  struct MapHash {

    typedef MapHash<NumHashValue>   Type;

    unsigned int value[NumHashValue];

    MapHash() : value() { clearData(); }
    MapHash(const Type&) { Error("Copier of MapHash Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for MapHash Disabled!");
      return *this;
    }
    ~MapHash() { clearData(); }

    void clearData() {
      unsigned int *p=value;
      unsigned int *pend=p+NumHashValue;
      for(;p!=pend;)  copy(*(p++),uZero);
    }
    unsigned int& operator()(const unsigned int I) { return value[I]; }
    const unsigned int& operator()(const unsigned int I)const{return value[I];}

  };

  template <unsigned int NumHashValue>
  bool IsValid(const MapHash<NumHashValue>&) { return true; }

  template <unsigned int NumHashValue>
  void release(MapHash<NumHashValue>& H) { H.clearData(); }

}

#endif

