
#ifndef _InputOutput_Base_Interface_H_
#define _InputOutput_Base_Interface_H_

#include <cstdio>
#include "io/state-name.h"

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
    ~IOBase() { clearData(); }

    void clearData() {}
    void SetState(const IOStateName& Bit, const bool flag=true) {
      state[Bit]=flag;
    }
    void ClearState() { SetState(FailBit,false); }

  };

  bool IsValid(const IOBase&) { return true; }
  void release(IOBase& O) { O.clearData(); }

  bool IsFailed(const IOBase& B) { return B.state[FailBit]; }

}

#endif

