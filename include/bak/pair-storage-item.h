
#ifndef _Pair_Storage_Item_H_
#define _Pair_Storage_Item_H_

#include "error-proc.h"

namespace std {

  template <typename T>
  struct PairItem {
    typedef PairItem<T>   Type;
    T Element;
    unsigned int Status;
    PairItem() : Status(0U) {}
    PairItem(const Type& Im) { myError("Cannot create from Item"); }
    PairItem& operator=(const Type& Im) {
      Element=Im.Element;
      Status=Im.Status;
      return *this;
    }
    template <typename iType>
    PairItem& operator=(const iType& Value) {
      Element=Value;
      return *this;
    }
  };

  template <typename T>
  ostream& operator<<(ostream& os, const PairItem<T>& OItem) {
    os<<"["<<OItem.Element<<"]\t"<<OItem.Status;
    return os;
  }

}

#endif

