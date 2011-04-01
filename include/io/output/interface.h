
#ifndef _InputOutput_Output_Base_Interface_H_
#define _InputOutput_Output_Base_Interface_H_

#include "io/base/interface.h"
#include "io/output/feature-name.h"

namespace mysimulator {

  static const unsigned int DefaultPrecision=8;
  static const unsigned int MaxSizePatternWPrecision=8;

  struct OutputBase : public IOBase {

    typedef OutputBase  Type;
    typedef IOBase  ParentType;

    unsigned int feature[NumberOutputFeature];
    char FloatPat[MaxSizePatternWPrecision];
    char DoublePat[MaxSizePatternWPrecision];
    char LongDoublePat[MaxSizePatternWPrecision];

    OutputBase() : ParentType(), feature(),
                   FloatPat(), DoublePat(), LongDoublePat() {
      precision(DefaultPrecision);
    }
    OutputBase(const Type&) {
      fprintf(stderr,"Copier of OutputBase Disabled!\n");
    }
    Type& operator=(const Type&) {
      fprintf(stderr,"Operator= for OutputBase Disabled!\n");
      return *this;
    }
    ~OutputBase() { clearData(); }

    void clearData() { release(static_cast<IOBase&>(*this)); }
    const unsigned int& precision() const { return feature[OutputPrecision]; }
    const unsigned int& precision(const unsigned int& prec) {
      feature[OutputPrecision]=prec;
      sprintf(FloatPat,"%%.%ug",prec);
      sprintf(DoublePat,"%%.%ug",prec);
      sprintf(LongDoublePat,"%%.%uLg",prec);
      return feature[OutputPrecision];
    }

    virtual Type& write(const bool&)=0;
    virtual Type& write(const char&)=0;
    virtual Type& write(const unsigned char&)=0;
    virtual Type& write(const short&)=0;
    virtual Type& write(const unsigned short&)=0;
    virtual Type& write(const int&)=0;
    virtual Type& write(const unsigned int&)=0;
    virtual Type& write(const long&)=0;
    virtual Type& write(const unsigned long&)=0;
    virtual Type& write(const long long int&)=0;
    virtual Type& write(const unsigned long long int&)=0;
    virtual Type& write(const float&)=0;
    virtual Type& write(const double&)=0;
    virtual Type& write(const long double&)=0;
    virtual Type& write(const void*)=0;
    virtual Type& write(const char*)=0;

  };

  bool IsValid(const OutputBase&) { return true; }
  void release(OutputBase& O) { O.clearData(); }

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
  OutputBase& operator<<(OutputBase& O, const unsigned int& u) {
    return O.write(u);
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
  OutputBase& operator<<(OutputBase& O, const double& d) {
    return O.write(d);
  }
  OutputBase& operator<<(OutputBase& O, const long double& ld) {
    return O.write(ld);
  }
  OutputBase& operator<<(OutputBase& O, const void* ptr) {
    return O.write(ptr);
  }
  OutputBase& operator<<(OutputBase& O, const char* s) { return O.write(s); }

}

#endif

