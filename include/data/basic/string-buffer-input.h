
#ifndef _String_Buffer_Input_H_
#define _String_Buffer_Input_H_

#include "data/name/string-input-property.h"
#include "data/basic/input-base.h"

namespace std {

  struct StringInput;
  bool IsAvailable(const StringInput&);
  void release(StringInput&);
  void refer(StringInput&, const Vector<char>&);
  void refer(StringInput&, const char*, const unsigned int);
  void allocate(StringInput&,const unsigned int);
  
  struct StringInput : public InputBase {
    Vector<char> buffer;
    Vector<unsigned int> property;
    StringInput() : InputBase(), buffer(), property() {}
    StringInput(const unsigned int n) : InputBase(), buffer(), property() {
      allocate(*this,n);
    }
    StringInput(const Vector<char>& bf) : InputBase(), buffer(), property() {
      refer(*this,bf);
    }
    StringInput(const char* ptr, const unsigned int n)
        : InputBase(), buffer(), property() {
      refer(*this,ptr,n);
    }
    StringInput(const StringInput&) { Error("Cannot create String Input"); }
    StringInput& operator=(const StringInput&) {
      Error("Cannot copy String Input");
      return *this;
    }
    ~StringInput() { release(*this); }
    template <typename T>
    void __read_part(char* inf,unsigned int len,const char* pat,T& value) {
      char nowc=inf[len];
      inf[len]='\0';
      sscanf(inf,pat,&value);
      inf[len]=nowc;
    }
    template <typename T>
    StringInput& __read(const char* pat, T& value) {
      assert(IsAvailable(*this));
      unsigned int n,sc;
      char* inf=buffer.data+property[StrInLocation];
      n=0;
      sc=property[StrInCapacity];
      while((isspace(inf[n]))&&(n<=sc))  n++;
      property[StrInLocation]+=n;
      property[StrInCapacity]-=n;
      inf=buffer.data+property[StrInLocation];
      sc=property[StrInCapacity];
      if(sc>0) {
        n=1;
        __read_part(inf,n,pat,value);
        n++;
        while(n<=sc) {
          T tmvalue;
          __read_part(inf,n,pat,tmvalue);
          if(tmvalue==value)  break;
          value=tmvalue;
          n++;
        }
        --n;
        property[StrInLocation]+=n;
        property[StrInCapacity]-=n;
      } else {
        Warn("String Input Buffer Exhausted\n");
        SetState(FailBit);
      }
      return *this;
    }
    StringInput& read(char& c) { return __read("%c",c); }
    StringInput& read(bool& b) {
      char c;
      __read("%c",c);
      b=(c=='0'?false:true);
      return *this;
    }
    StringInput& read(unsigned char& uc) { return __read("%c",uc); }
    StringInput& read(short& s) { return __read("%hd",s); }
    StringInput& read(unsigned short& us) { return __read("%hu",us); }
    StringInput& read(int& i) { return __read("%d",i); }
    StringInput& read(unsigned int& u) { return __read("%u",u); }
    StringInput& read(long& l) { return __read("%d",l); }
    StringInput& read(unsigned long& ul) { return __read("%u",ul); }
    StringInput& read(long long int& ll) { return __read("%lld",ll); }
    StringInput& read(unsigned long long int& ull) {
      return __read("%llu",ull);
    }
    StringInput& read(float& f) { return __read("%f",f); }
    StringInput& read(double& d) { return __read("%lf",d); }
    StringInput& read(long double& ld) { return __read("%Lf",ld); }
    StringInput& read(void*& ptr) { return __read("%p",ptr); }
    StringInput& read(char* str) {
      assert(IsAvailable(*this));
      unsigned int n,sc;
      char* inf=buffer.data+property[StrInLocation];
      n=0;
      sc=property[StrInCapacity];
      while((isspace(inf[n]))&&(n<=sc))  n++;
      property[StrInLocation]+=n;
      property[StrInCapacity]-=n;
      inf=buffer.data+property[StrInLocation];
      sc=property[StrInCapacity];
      if(sc>0) {
        n=0;
        while((!isspace(inf[n]))&&(n<=sc)&&(str[n]!=CharEOF)) {
          str[n]=inf[n];
          ++n;
        }
        str[n]='\0';
        property[StrInLocation]+=n;
        property[StrInCapacity]-=n;
      } else {
        Warn("String Input Buffer Exhausted");
        SetState(FailBit);
      }
      return *this;
    }

  };

  bool IsAvailable(const StringInput& I) {
    return IsAvailable(static_cast<const InputBase&>(I))&&
           IsAvailable(I.buffer)&&IsAvailable(I.property);
  }
  void release(StringInput& I) {
    release(I.buffer);
    release(I.property);
    release(static_cast<InputBase&>(I));
  }
  void refer(StringInput& I, const StringInput& rI) {
    assert(IsAvailable(rI));
    release(I);
    refer(I.buffer,rI.buffer);
    refer(I.property,rI.property);
    refer(I.state,rI.state);
  }
  void initStringInput(StringInput& I) {
    I.buffer[I.buffer.size-1]='\0';
    allocate(I.property,StringInputNumberProperty);
    I.property[StrInLocation]=0;
    I.property[StrInCapacity]=I.buffer.size-1;
  }
  void refer(StringInput& I, const Vector<char>& bf) {
    release(I);
    refer(I.buffer,bf);
    initStringInput(I);
    allocate(static_cast<InputOutputBase&>(I));
  }
  void refer(StringInput& I, const char* ptr, const unsigned int n) {
    release(I);
    refer(I.buffer,ptr,n);
    initStringInput(I);
    allocate(static_cast<InputOutputBase&>(I));
  }
  void allocate(StringInput& I, const unsigned int n) {
    release(I);
    allocate(I.buffer,n);
    initStringInput(I);
    allocate(static_cast<InputOutputBase&>(I));
  }
  void imprint(StringInput& I, const StringInput& cI) {
    assert(IsAvailable(cI));
    allocate(I,cI.buffer.size);
  }
  void copy(StringInput& I, const Vector<char>& bf) {
    assert(IsAvailable(bf));
    allocate(I,bf.size);
    copy(I.buffer,bf);
  }
  
}

#include <cstring>

namespace std {

  void copy(StringInput& I, const char* ptr, const unsigned int n) {
    allocate(I,n);
    strncpy(I.buffer.data,ptr,n-1);
  }

}

#endif
