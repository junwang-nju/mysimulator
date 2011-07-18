
#ifndef _InputOutput_Output_Base_H_
#define _InputOutput_Output_Base_H_

#include "io/base/interface.h"
#include "io/output/feature-name.h"
#include <cstdio>

namespace mysimulator {

  struct OutputBase : public IOBase {

    public:

      static const unsigned int DefaultPrecision;
      static const unsigned int MaxSizePattern=8;

      typedef OutputBase    Type;
      typedef IOBase        ParentType;

      unsigned int feature[NumberOutputFeature];
      char FloatPat[MaxSizePattern];
      char DoublePat[MaxSizePattern];
      char LongDoublePat[MaxSizePattern];

      OutputBase() : ParentType(), feature(), FloatPat(), DoublePat(),
                     LongDoublePat() { precision(DefaultPrecision); }
      ~OutputBase() { clearData(); }

      void clearData() {
        release(*static_cast<ParentType*>(this));
        precision(DefaultPrecision);
      }
      bool isvalid() const {
        return static_cast<const ParentType* const&>(this)->isvalid();
      }

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
      virtual Type& write(const long long&)=0;
      virtual Type& write(const unsigned long long&)=0;
      virtual Type& write(const float&)=0;
      virtual Type& write(const double&)=0;
      virtual Type& write(const long double&)=0;
      virtual Type& write(const char* const&)=0;
      virtual Type& write(const void* const&)=0;

    protected:

      OutputBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  const unsigned int OutputBase::DefaultPrecision=8;
  const unsigned int OutputBase::MaxSizePattern;

  bool IsValid(const OutputBase& O) { return O.isvalid(); }
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
  OutputBase& operator<<(OutputBase& O, const long long& ll) {
    return O.write(ll);
  }
  OutputBase& operator<<(OutputBase& O, const unsigned long long& ull) {
    return O.write(ull);
  }
  OutputBase& operator<<(OutputBase& O, const float& f) { return O.write(f); }
  OutputBase& operator<<(OutputBase& O, const double& d) { return O.write(d); }
  OutputBase& operator<<(OutputBase& O, const long double& ld) {
    return O.write(ld);
  }
  OutputBase& operator<<(OutputBase& O, const void* const& p) {
    return O.write(p);
  }
  OutputBase& operator<<(OutputBase& O, const char* const& s) {
    return O.write(s);
  }

}

#endif

