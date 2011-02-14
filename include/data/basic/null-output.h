
#ifndef _Null_Output_H_
#define _Null_Output_H_

#include "data/basic/output-base.h"

namespace std {
  
  struct NullOutput;
  void release(NullOutput&);
  
  struct NullOutput : public OutputBase {
    NullOutput() : OutputBase() {}
    NullOutput(const NullOutput&) { Error("Cannot create Null Output"); }
    NullOutput& operator=(const NullOutput&) {
      Error("Cannot copy Null Output");
      return *this;
    }
    ~NullOutput() { release(*this); }
    NullOutput& write(const bool&) { return *this; }
    NullOutput& write(const char&) { return *this; }
    NullOutput& write(const unsigned char&) { return *this; }
    NullOutput& write(const short&) { return *this; }
    NullOutput& write(const unsigned short&) { return *this; }
    NullOutput& write(const int&) { return *this; }
    NullOutput& write(const unsigned int&) { return *this; }
    NullOutput& write(const long&) { return *this; }
    NullOutput& write(const unsigned long&) { return *this; }
    NullOutput& write(const long long int&) { return *this; }
    NullOutput& write(const unsigned long long int&) { return *this; }
    NullOutput& write(const float&) { return *this; }
    NullOutput& write(const double&) { return *this; }
    NullOutput& write(const long double&) { return *this; }
    NullOutput& write(const void*) { return *this; }
    NullOutput& write(const char*) { return *this; }
  };

  bool IsAvailable(const NullOutput& O) {
    return IsAvailable(static_cast<const OutputBase&>(O));
  }
  void release(NullOutput& O) {
    release(static_cast<OutputBase&>(O));
  }
  void refer(NullOutput& O, const NullOutput& rO) {
    assert(IsAvailable(rO));
    release(O);
    refer(static_cast<OutputBase&>(O),static_cast<const OutputBase&>(rO));
  }
  void copy(NullOutput& O, const NullOutput& cO) {
    assert(IsAvailable(O));
    assert(IsAvailable(cO));
    copy(static_cast<OutputBase&>(O),static_cast<const OutputBase&>(cO));
  }
  void allocate(NullOutput& O) {
    release(O);
    allocate(static_cast<OutputBase&>(O));
  }

}

#endif
