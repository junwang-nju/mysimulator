
#ifndef _String_Buffer_Input_H_
#define _String_Buffer_Input_H_

#include "data/name/string-input-property.h"
#include "operation/basic/input-base.h"
#include "data/basic/vector.h"
#include <cstdio>
#include <cassert>

namespace std {

  struct StringInput;
  bool IsAvailable(const StringInput&);
  void release(StringInput&);
  void copy(StringInput&, const Vector<char>&);
  void copy(StringInput&, const char*, const unsigned int);
  void allocate(StringInput&,const unsigned int);
  
  struct StringInput : public InputBase {
    Vector<char> buffer;
    Vector<unsigned int> property;
    StringInput() : buffer(), property() {}
    StringInput(const unsigned int n) : buffer(), property() {
      allocate(*this,n);
    }
    StringInput(const Vector<char>& bf) : buffer(), property() {
      copy(*this,bf);
    }
    StringInput(const char* ptr, const unsigned int n) : buffer(), property() {
      copy(*this,ptr,n);
    }
    StringInput(const StringInput&) {
      fprintf(stderr,"Cannot create String Input\n");
      exit(0);
    }
    StringInput& operator=(const StringInput&) {
      fprintf(stderr,"Cannot copy String Input\n");
      exit(0);
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
      while(isspace(inf[n]))  n++;
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
        fprintf(stderr,"String Input Buffer Exhausted\n");
        exit(0);
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
      unsigned int n;
      char* inf=buffer.data+property[StrInLocation];
      n=0;
      while(isspace(inf[n]))  n++;
      property[StrInLocation]+=n;
      property[StrInCapacity]-=n;
      inf=buffer.data+property[StrInLocation];
      if(property[StrInCapacity]>0) {
        n=0;
        while((!isspace(inf[n]))&&(str[n]!=CharEOF)) {
          str[n]=inf[n];
          ++n;
        }
        str[n]='\0';
        property[StrInLocation]+=n;
        property[StrInCapacity]-=n;
      } else {
        fprintf(stderr,"String Input Buffer Exhausted\n");
        exit(0);
      }
      return *this;
    }
  };

  bool IsAvailable(const StringInput& I) {
    return IsAvailable(I.buffer)&&IsAvailable(I.property);
  }
  void release(StringInput& I) {
    release(I.buffer);
    release(I.property);
  }
  void copy(StringInput& I, const StringInput& cI) {
    assert(IsAvailable(cI));
    release(I);
    refer(I.buffer,cI.buffer);
    refer(I.property,cI.property);
  }
  void initStringInput(StringInput& I) {
    I.buffer[I.buffer.size-1]='\0';
    allocate(I.property,StringInputNumberProperty);
    I.property[StrInLocation]=0;
    I.property[StrInCapacity]=I.buffer.size-1;
  }
  void copy(StringInput& I, const Vector<char>& bf) {
    release(I);
    refer(I.buffer,bf);
    initStringInput(I);
  }
  void copy(StringInput& I, const char* ptr, const unsigned int n) {
    release(I);
    refer(I.buffer,ptr,n);
    initStringInput(I);
  }
  void allocate(StringInput& I, const unsigned int n) {
    allocate(I.buffer,n);
    initStringInput(I);
  }

}

#endif
