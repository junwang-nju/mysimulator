
#ifndef _Pair_Information_Item_H_
#define _Pair_Information_Item_H_

#include "operation/basic/util.h"
#include "operation/basic/memory.h"
#include "operation/basic/error-proc.h"
#include "data/name/storage-state-name.h"
#include <cassert>

namespace std {

  template <typename T>
  struct PairItem {
    typedef PairItem<T>   Type;
    
    T* content;
    unsigned int *status;
    unsigned int state;
    
    PairItem() : content(NULL), status(NULL), state(Unused) {}
    PairItem(const Type& P) { myError("Cannot create Pair Item"); }
    Type& operator=(const Type& P) {
      myError("Cannot copy Pair Item");
      return *this;
    }
    ~PairItem() { release(*this); }

    T& operator()() { return *content; }
    const T& operator()() const { return *content; }

  };

  template <typename T>
  bool IsAvailable(const PairItem<T>& P) { return IsAvailable(P.content); }

  template <typename T>
  void release(PairItem<T>& P) {
    if(P.state==Allocated) { safe_delete(P.content); safe_delete(P.status); }
    else { P.content=NULL; P.status=NULL; }
    P.state=Unused;
  }

  template <typename T>
  void copy(PairItem<T>& P, const PairItem<T>& cP) {
    assert(IsAvailable(P));
    assert(IsAvailable(cP));
    *(P.content)=*(cP.content);
    *(P.status)=*(cP.status);
  }

  template <typename T>
  void allocate(PairItem<T>& P) {
    release(P);
    P.content=new T;
    P.status=new unsigned int;
    P.state=Allocated;
  }

  template <typename T>
  void refer(PairItem<T>& P, const PairItem<T>& cP) {
    assert(IsAvailable(cP));
    release(P);
    P.content=cP.content;
    P.status=cP.status;
    P.state=Reference;
  }

  template <typename T>
  ostream& operator<<(ostream& os, const PairItem<T>& P) {
    os<<"[ "<<P()<<"\t("<<*(P.status)<<" )]";
    return os;
  }

}

#endif
