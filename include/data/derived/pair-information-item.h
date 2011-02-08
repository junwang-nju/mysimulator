
#ifndef _Pair_Information_Item_H_
#define _Pair_Information_Item_H_

#include "operation/basic/util.h"
#include "operation/basic/memory.h"
#include "operation/basic/error-proc.h"
#include "data/name/storage-state.h"
#include <cassert>

namespace std {

  template <typename T>
  struct PairItem {
    typedef PairItem<T>   Type;
    
    T content;
    unsigned int status;
    
    PairItem() : content(), status(0) {}
    PairItem(const Type& P) { myError("Cannot create Pair Item"); }
    Type& operator=(const Type& P) {
      myError("Cannot copy Pair Item");
      return *this;
    }

    T& operator()() { return content; }
    const T& operator()() const { return content; }

  };

  template <typename T>
  void copy(PairItem<T>& P, const PairItem<T>& cP) {
    P.content=cP.content;
    P.status=cP.status;
  }

  template <typename T>
  OutputBase& operator<<(OutputBase& os, const PairItem<T>& P) {
    os<<"[ "<<P()<<"\t("<<P.status<<" )]";
    return os;
  }

}

#endif
