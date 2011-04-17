
#ifndef _InputOutput_Input_String_Interface_H_
#define _InputOutput_Input_String_Interface_H_

#include "io/input/interface.h"
#include "vector/allocate.h"
#include "io/input/string/property-name.h"

namespace mysimulator {

  struct StringInput : public InputBase {

    typedef StringInput   Type;
    typedef InputBase     ParentType;

    Vector<char> buffer;
    Vector<unsigned int> property;

    StringInput() : ParentType(), buffer(), property() {}
    StringInput(const Type&) { Error("Copier of StringInput Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for StringInput Disabled!");
      return *this;
    }
    StringInput(const unsigned int n) : InputBase(), buffer(n), property() {
      _init();
    }
    ~StringInput() { clearData(); }

    void clearData() {
      release(buffer);
      release(property);
      release(static_cast<InputBase&>(*this));
    }
    void _init() {
      buffer[buffer.size-1]='\0';
      allocate(property,StringInputNumberProperty);
      property[InStringLocation]=0;
      property[InStringCapacity]=buffer.size-1;
    }
    void open(const unsigned int n) {
      close();
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
    void _read_part(char* inf, unsigned int len, const char* pat, T& value) {
      char nowc=inf[len];
      inf[len]='\0';
      sscanf(inf,pat,&value);
      inf[len]=nowc;
    }
    template <typename T>
    Type& _read(const char* pat, T& value) {
      assert(IsValid(buffer)&&IsValid(property));
      char* inf=buffer.pdata+property[InStringLocation];
      unsigned int n=0;
      unsigned int sc=property[InStringCapacity];
      while(isspace(inf[n])&&(n<=sc)) ++n;
      property[InStringLocation]+=n;
      property[InStringCapacity]-=n;
      inf=buffer.pdata+property[InStringLocation];
      sc=property[InStringCapacity];
      if(sc>0) {
        n=1;
        _read_part(inf,n,pat,value);
        ++n;
        while(n<=sc) {
          T tmvalue;
          _read_part(inf,n,pat,tmvalue);
          if(tmvalue==value)  break;
          value=tmvalue;
          ++n;
        }
        --n;
        property[InStringLocation]+=n;
        property[InStringCapacity]-=n;
      } else {
        Warn("Buffer Exhausted in StringInput!");
        SetState(FailBit);
      }
      return *this;
    }
    Type& read(char& c) { return _read("%c",c); }
    Type& read(unsigned char& uc) { return _read("%c",uc); }
    Type& read(bool& b) {
      char c;
      _read("%c",c);
      b=(c=='0'?false:true);
      return *this;
    }
    Type& read(short& s) { return _read("%hd",s); }
    Type& read(unsigned short& us) { return _read("%hu",us); }
    Type& read(int& i) { return _read("%d",i); }
    Type& read(unsigned int& u) { return _read("%u",u); }
    Type& read(long& l) { return _read("%d",l); }
    Type& read(unsigned long& l) { return _read("%u",l); }
    Type& read(long long& l) { return _read("%lld",l); }
    Type& read(unsigned long long& l) { return _read("%llu",l); }
    Type& read(float& f) { return _read("%f",f); }
    Type& read(double& d) { return _read("%d",d); }
    Type& read(long double& ld) { return _read("%Lf",ld); }
    Type& read(void*& ptr) { return _read("%p",ptr); }
    Type& read(char* str) {
      assert(IsValid(buffer)&&IsValid(property));
      char* inf=buffer.pdata+property[InStringLocation];
      unsigned int n=0;
      unsigned int sc=property[InStringCapacity];
      while(isspace(inf[n])&&(n<=sc)) ++n;
      property[InStringLocation]+=n;
      property[InStringCapacity]-=n;
      inf=buffer.pdata+property[InStringLocation];
      sc=property[InStringCapacity];
      if(sc>0) {
        n=0;
        while((!isspace(inf[n]))&&(n<=sc)&&(str[n]!=CharEOF)) {
          str[n]=inf[n];
          ++n;
        }
        str[n]='\n';
        property[InStringLocation]+=n;
        property[InStringCapacity]-=n;
      } else {
        Warn("Buffer Exhausted in StringInput!");
        SetState(FailBit);
      }
      return *this;
    }
    Type& unget() {
      --property[InStringLocation];
      ++property[InStringCapacity];
      return *this;
    }
    Type& unget(const char& c) {
      assert(c==buffer[property[InStringLocation]-1]);
      return unget();
    }

  };

  bool IsValid(const StringInput& I) {
    return IsValid(I.buffer)&&IsValid(I.property)&&
           IsValid(static_cast<const InputBase&>(I));
  }
  void release(StringInput& I) { I.clearData(); }

}

#endif

