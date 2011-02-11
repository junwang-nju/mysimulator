
#ifndef _String_Buffer_Input_H_
#define _String_Buffer_Input_H_

#include "operation/basic/input-base.h"
#include "data/name/vector.h"
#include <cstdio>
#include <cassert>

namespace std {

  struct StringInput;
  void release(StringInput&);
  void copy(StringInput&, const Vector<char>&);
  void copy(StringInput&, const char*, const unsigned int);
  
  struct StringInput : public InputBase {
    Vector<char> buffer;
    Vector<unsigned int> property;
    StringInput() : buffer(), property() {}
    StringInput(const Vector<char>& bf) : buffer(), property() {
      copy(*this,bf);
    }
    StringInput(const char* ptr, const unsigned int n) : buffer(), property() {
      copy(*this,ptr,n);
    }
    StringInput(const StringInput&) {
      fprintf(stderr,"Cannot create String Input");
      exit(0);
    }
    StringInput& operator=(const StringInput&) {
      fprintf(stderr,"Cannot copy String Input");
      exit(0);
      return *this;
    }
    ~StringInput() { release(*this); }
    template <typename T>
    StringInput& __read(const char* pat, T& value) {
      assert(IsAvailable(*this));
      assert(property[StrInCapacity]);
      int n=sscanf(buffer.data+property[StrInLocation],pat,&value);
      property[StrInCapacity]-=n;
      return *this;
    }
    StringInput& read(bool& b) {
      assert(IsAvailable(*this));
      assert(property[StrInCapacity]);
      int i=1;
      unsigned int n;
      n=sscanf(buffer.data+property[StrInLocation],"%d",&i);
      b=(i==0?false:true);
      property[StrInCapacity]-=n;
      return *this;
    }
    StringInput& read(char& c) { return __read("%c",c); }
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
  };

}

#endif
