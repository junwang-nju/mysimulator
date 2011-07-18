
#ifndef _InputOutput_Base_Interface_H_
#define _InputOutput_Base_Interface_H_

#include "io/state-name.h"

namespace mysimulator {

  struct IOBase {

    public:

      typedef IOBase    Type;

      bool state[NumberIOState];

      IOBase() : state() { clearState(); }
      ~IOBase() { clearData(); }

      void clearData() { clearState(); }
      bool isvalid() const { return true; }

      void set(const IOStateName& bit, const bool& fg=true) { state[bit]=fg; }
      void clearState() { set(FailBit,false); }
      bool isfail() const { return state[FailBit]; }

    protected:

      IOBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  bool IsValid(const IOBase& IO) { return IO.isvalid(); }
  void release(IOBase& O) { O.clearData(); }
  bool IsFailed(const IOBase& B) { return B.isfail(); }

}

#endif

