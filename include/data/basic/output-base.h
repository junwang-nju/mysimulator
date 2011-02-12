
#ifndef _Output_Base_H_
#define _Output_Base_H_

#include "data/basic/input-output-base.h"

namespace std {
  
  struct OutputBase;
  void release(OutputBase&);
  
  struct OutputBase : public InputOutputBase {
    OutputBase() : InputOutputBase() {}
    OutputBase(const OutputBase&) { Error("Cannot create Output Base"); }
    OutputBase& operator=(const OutputBase&) {
      Error("Cannot copy Output Base");
      return *this;
    }
    ~OutputBase() { release(*this); }
    virtual OutputBase& write(const bool&)=0;
    virtual OutputBase& write(const char&)=0;
    virtual OutputBase& write(const unsigned char&)=0;
    virtual OutputBase& write(const short&)=0;
    virtual OutputBase& write(const unsigned short&)=0;
    virtual OutputBase& write(const int&)=0;
    virtual OutputBase& write(const unsigned int&)=0;
    virtual OutputBase& write(const long&)=0;
    virtual OutputBase& write(const unsigned long&)=0;
    virtual OutputBase& write(const long long int&)=0;
    virtual OutputBase& write(const unsigned long long int&)=0;
    virtual OutputBase& write(const float&)=0;
    virtual OutputBase& write(const double&)=0; 
    virtual OutputBase& write(const long double&)=0;
    virtual OutputBase& write(const void*)=0;
    virtual OutputBase& write(const char*)=0;
  };

  bool IsAvailable(const OutputBase& OB) {
    return static_cast<const InputOutputBase&>(OB);
  }
  void release(OutputBase& OB) { release(static_cast<InputOutputBase&>(OB)); }
  void copy(OutputBase& O, const OutputBase& cO) {
    assert(IsAvailable(O));
    assert(IsAvailable(cO));
    copy(static_cast<InputOutputBase&>(O),
         static_cast<const InputOutputBase&>(cO));
  }
  void refer(OutputBase& O, const OutputBase& rO) {
    assert(IsAvailable(rO));
    release(O);
    refer(static_cast<InputOutputBase&>(O),
          static_cast<const InputOutputBase&>(rO));
  }

  OutputBase& operator<<(OutputBase& O, const bool& b) { return O.write(b); }
  OutputBase& operator<<(OutputBase& O, const char& c) { return O.write(c); }
  OutputBase& operator<<(OutputBase& O, const unsigned char& uc) {
    return O.write(uc);
  }
  OutputBase& operator<<(OutputBase& O, const short& s) { return O.write(s); }
  OutputBase& operator<<(OutputBase& O, const unsigned short& us) {
    return O.write(us);
  }
  OutputBase& operator<<(OutputBase& O, const int& i) { return O.write(i); }
  OutputBase& operator<<(OutputBase& O, const unsigned int& ui) {
    return O.write(ui);
  }
  OutputBase& operator<<(OutputBase& O, const long& l) { return O.write(l); }
  OutputBase& operator<<(OutputBase& O, const unsigned long& ul) {
    return O.write(ul);
  }
  OutputBase& operator<<(OutputBase& O, const long long int& ll) {
    return O.write(ll);
  }
  OutputBase& operator<<(OutputBase& O, const unsigned long long int& ull) {
    return O.write(ull);
  }
  OutputBase& operator<<(OutputBase& O, const float& f) { return O.write(f); }
  OutputBase& operator<<(OutputBase& O, const double& d) { return O.write(d); }
  OutputBase& operator<<(OutputBase& O, const long double& ld) {
    return O.write(ld);
  }
  OutputBase& operator<<(OutputBase& O, const void* ptr) {
    return O.write(ptr);
  }
  OutputBase& operator<<(OutputBase& O, const char* s) { return O.write(s); }

}

#endif

