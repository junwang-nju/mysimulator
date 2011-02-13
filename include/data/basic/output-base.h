
#ifndef _Output_Base_H_
#define _Output_Base_H_

#include "data/basic/input-output-base.h"
#include "data/name/output-feature-name.h"
#include "data/name/output-pattern-name.h"
#include "data/basic/property-list.h"

namespace std {
  
  struct OutputBase;
  void release(OutputBase&);

  static const unsigned int DefaultPrecision=8;

  struct OutputBase : public InputOutputBase {
    Vector<unsigned int> feature;
    PropertyList<char> patString; 
    OutputBase() : InputOutputBase(), feature(), patString() {}
    OutputBase(const OutputBase&) { Error("Cannot create Output Base"); }
    OutputBase& operator=(const OutputBase&) {
      Error("Cannot copy Output Base");
      return *this;
    }
    ~OutputBase() { release(*this); }
    const unsigned int precision() const { return feature[OutputPrecision]; }
    unsigned int precision(const unsigned int& pcs) {
      feature[OutputPrecision]=pcs;
      sprintf(patString[FloatOutput].data,"%%.%ug",pcs);
      sprintf(patString[DoubleOutput].data,"%%.%ug",pcs);
      sprintf(patString[LongDoubleOutput].data,"%%.%uLg",pcs);
      return pcs;
    }

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
    return IsAvailable(static_cast<const InputOutputBase&>(OB))&&
           IsAvailable(OB.feature)&&IsAvailable(OB.patString);
  }
  void release(OutputBase& OB) {
    release(OB.feature);
    release(OB.patString);
    release(static_cast<InputOutputBase&>(OB));
  }
  void copy(OutputBase& O, const OutputBase& cO) {
    assert(IsAvailable(O));
    assert(IsAvailable(cO));
    copy(O.feature,cO.feature);
    copy(O.patString,cO.patString);
    copy(static_cast<InputOutputBase&>(O),
         static_cast<const InputOutputBase&>(cO));
  }
  void refer(OutputBase& O, const OutputBase& rO) {
    assert(IsAvailable(rO));
    release(O);
    refer(O.feature,rO.feature);
    refer(O.patString,rO.patString);
    refer(static_cast<InputOutputBase&>(O),
          static_cast<const InputOutputBase&>(rO));
  }
  void allocate(OutputBase& O) {
    release(O);
    allocate(static_cast<InputOutputBase&>(O));
    allocate(O.feature,OutputNumberFeature);
    Vector<unsigned int> sz(OutputNumberPattern);
    copy(sz,OutputPatternMaxSize);
    allocate(O.patString,sz);
    O.precision(DefaultPrecision);
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

