
#ifndef _InputOutput_Base_H_
#define _InputOutput_Base_H_

#include <cstdio>
#include "IO/state-name.h"

namespace mysimulator {

  struct IOBase {

    typedef IOBase  Type;

    bool state[NumberIOState];

    IOBase() : state() { ClearState(); }
    IOBase(const Type&) { fprintf(stderr,"Copier of IOBase Disabled!\n"); }
    Type& operator=(const Type&) {
      fprintf(stderr,"Operator= for IOBase Disabled!\n");
      return *this;
    }
    ~IOBase() { release(); }

    void release() {}
    void SetState(const IOStateName& Bit, const bool flag=true) {
      state[Bit]=flag;
    }
    void ClearState() { SetState(FailBit,false); }

  };

  bool IsValid(const IOBase&) { return true; }
  void copy(IOBase& B, const IOBase& cB) {
    for(unsigned int i=0;i<NumberIOState;++i) B.state[i]=cB.state[i];
  }

  bool IsFailed(const IOBase& B) { return B.state[FailBit]; }

}

#endif

