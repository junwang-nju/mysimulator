
#ifndef _Input_Output_Base_H_
#define _Input_Output_Base_H_

#include "data/basic/vector.h"
#include "data/name/input-output-state.h"

namespace std {

  struct InputOutputBase;
  void release(InputOutputBase&);

  struct InputOutputBase {
    Vector<bool>  state;
    InputOutputBase() : state() {}
    InputOutputBase(const InputOutputBase&) {
      Error("Cannot create Input-Output Base");
    }
    InputOutputBase& operator=(const InputOutputBase&) {
      Error("Cannot copy Input-Output Base");
      return *this;
    }
    ~InputOutputBase() { release(*this); }
    void SetState(const InputOutputStateName Bit, const bool Flag=true) {
      state[Bit]=Flag;
    }
  };

  bool IsAvailable(const InputOutputBase& B) { return IsAvailable(B.state); }
  void release(InputOutputBase& B) { release(B.state); }
  void copy(InputOutputBase& B, const InputOutputBase& cB) {
    assert(IsAvailable(B));
    assert(IsAvailable(cB));
    copy(B.state,cB.state);
  }
  void refer(InputOutputBase& B, const InputOutputBase& rB) {
    assert(IsAvailable(rB));
    release(B);
    refer(B.state,rB.state);
  }

  bool IsFail(InputOutputBase& B) { return B.state[FailBit]; }
  void allocate(InputOutputBase& B) {
    allocate(B.state,InputOutputNumberState);
    B.SetState(FailBit,false);
  }

}

#endif

