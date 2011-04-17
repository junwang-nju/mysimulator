
#ifndef _InputOutput_Output_String_Interface_H_
#define _InputOutput_Output_String_Interface_H_

#include "io/output/interface.h"
#include "vector/allocate.h"
#include "io/output/string/property-name.h"

namespace mysimulator {

  struct StringOutput : public OutputBase {

    typedef StringOutput  Type;
    typedef OutputBase    ParentType;

    Vector<char> buffer;
    Vector<unsigned int> property;

    StringOutput() : ParentType(), buffer(), property() {}
    StringOutput(const Type&) { Error("Copier of StringOutput Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for StringOutput Disabled!");
      return *this;
    }
    StringOutput(const unsigned int n) : ParentType(), buffer(n), property() {
      _init();
    }
    StringOutput(const Vector<char>& bf) : ParentType(), buffer(), property() {
      buffer.getSubvec(bf);
      _init();
    }
    StringOutput(const char* p, const unsigned int n)
      : ParentType(), buffer(), property() {
      buffer.getSubvec(p,n);
      _init();
    }
    ~StringOutput() { clearData(); }

    void clearData() {
      release(property);
      release(buffer);
      release(static_cast<ParentType&>(*this));
    }
    void _init() {
      buffer[buffer.size-1]='\0';
      allocate(property,StringOutputNumberProperty);
      property[InStringLocation]=0;
      property[InStringCapacity]=buffer.size;
    }
    void open(const unsigned int n) {
      clearData();
      allocate(buffer,n);
      _init();
    }
    void load(const Vector<char>& bf) {
      close();
      buffer.getSubvec(bf);
      _init();
    }
    void load(const char* p, const unsigned int n) {
      close();
      buffer.getSubvec(p,n);
      _init();
    }
    void close() { clearData(); clearState(); }
    template <typename T>
    StringOutput& _write(const char* pat, const T& value) {
      assert(IsValid(buffer)&&IsValid(property));
      if(property[InStringCapacity]==0) {
        SetState(FailBit);
        Warn("No free space for output buffer in StringOutput!");
      } else {
        int n=snprintf(buffer.pdata+property[InStringLocation],
                       property[InStringCapacity],pat,value);
        if(n<0) SetState(FailBit);
        else if(static_cast<unsigned int>(n)>property[InStringCapacity]) {
          SetState(FailBit);
          Warn("Buffer Overflow in StringOutput!");
          n=property[InStringCapacity];
        }
        property[InStringLocation]+=n;
        property[InStringCapacity]-=n;
      }
      return *this;
    }

    Type& write(const bool& b) { return _write("%d",b?1:0); }
    Type& write(const char& c) { return _write("%c",c); }
    Type& write(const unsigned char& uc) { return _write("%c",uc); }
    Type& write(const short& s) { return _write("%hd",s); }
    Type& write(const unsigned short& us) { return _write("%hu",us); }
    Type& write(const int& i) { return _write("%d",i); }
    Type& write(const unsigned int& u) { return _write("%u",u); }
    Type& write(const long& i) { return _write("%d",i); }
    Type& write(const unsigned long& u) { return _write("%u",u); }
    Type& write(const long long& i) { return _write("%lld",i); }
    Type& write(const unsigned long long& u) { return _write("%llu",u); }
    Type& write(const float& f) { return _write(FloatPat,f); }
    Type& write(const double& d) { return _write(DoublePat,d); }
    Type& write(const long double& ld) { return _write(LongDoublePat,ld); }
    Type& write(const void* ptr) { return _write("%p",ptr); }
    Type& write(const char* s) { return _write("%s",s); }

  };

  bool IsValid(const StringOutput& O) {
    return IsValid(O.buffer)&&IsValid(O.property)&&
           IsValid(static_cast<const OutputBase&>(O));
  }
  void release(StringOutput& O) { O.clearData(); }

}

#endif

