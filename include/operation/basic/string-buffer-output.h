
#ifndef _String_Buffer_Output_H_
#define _String_Buffer_Output_H_

#include "data/basic/vector.h"
#include "data/name/string-output-property.h"
#include "operation/basic/output-base.h"
#include <cstdio>
#include <cassert>

namespace std {
  
  struct StringOutput;
  bool IsAvailable(const StringOutput&);
  void release(StringOutput&);
  void copy(StringOutput&, const Vector<char>&);
  void copy(StringOutput&, const char*, const unsigned int);
  void allocate(StringOutput&,const unsigned int);
  
  struct StringOutput : public OutputBase {
    Vector<char> buffer;
    Vector<unsigned int> property;
    StringOutput() : buffer(), property() {}
    StringOutput(const unsigned int n) : buffer(), property() {
      allocate(*this,n);
    }
    StringOutput(const Vector<char>& bf) : buffer(), property() {
      copy(*this,bf);
    }
    StringOutput(const char* ptr, const unsigned int n) : buffer(), property(){
      copy(*this,ptr,n);
    }
    StringOutput(const StringOutput&) {
      fprintf(stderr,"Cannot create String Output\n");
      exit(0);
    }
    StringOutput& operator=(const StringOutput&) {
      fprintf(stderr,"Cannot copy string output\n");
      exit(0);
      return *this;
    }
    ~StringOutput() { release(*this); }
    template <typename T>
    StringOutput& __write(const char* pat, const T& value) {
      assert(IsAvailable(*this));
      int n=snprintf(buffer.data+property[StrOutLocation],
                     property[StrOutCapacity],pat,value);
      if(n>property[StrOutCapacity]) {
        fprintf(stderr,"String Buffer Overflow\n");
        exit(0);
      }
      property[StrOutLocation]+=n;
      property[StrOutCapacity]-=n;
      return *this;
    }
    StringOutput& write(const bool& b) { return __write("%d",b?1:0); }
    StringOutput& write(const char& c) { return __write("%c",c); }
    StringOutput& write(const unsigned char& uc) { return __write("%c",uc); }
    StringOutput& write(const short& s) { return __write("%hd",s); }
    StringOutput& write(const unsigned short& us) { return __write("%hu",us); }
    StringOutput& write(const int& i) { return __write("%d",i); }
    StringOutput& write(const unsigned int& ui) { return __write("%u",ui); }
    StringOutput& write(const long& l) { return __write("%d",l); }
    StringOutput& write(const unsigned long& ul) { return __write("%u",ul); }
    StringOutput& write(const long long int& ll) { return __write("%lld",ll); }
    StringOutput& write(const unsigned long long int& ull) {
      return __write("%llu",ull);
    }
    StringOutput& write(const float& f) { return __write("%g",f); }
    StringOutput& write(const double& d) { return __write("%g",d); }
    StringOutput& write(const long double& ld) { return __write("%Lg",ld); }
    StringOutput& write(const void* ptr) { return __write("%p",ptr); }
    StringOutput& write(const char* s) { return __write("%s",s); }
    
  };

  bool IsAvailable(const StringOutput& O) {
    return IsAvailable(O.buffer)&& IsAvailable(O.property);
  }
  void release(StringOutput& O) {
    release(O.buffer);
    release(O.property);
  }
  void copy(StringOutput& O, const StringOutput& cO) {
    assert(IsAvailable(cO));
    release(O);
    refer(O.buffer,cO.buffer);
    refer(O.property,cO.property);
  }
  void initStringOutput(StringOutput& O) {
    O.buffer[O.buffer.size-1]='\0';
    allocate(O.property,StringOutputNumberProperty);
    O.property[StrOutLocation]=0;
    O.property[StrOutCapacity]=O.buffer.size;
  }
  void copy(StringOutput& O, const Vector<char>& bf) {
    release(O);
    refer(O.buffer,bf);
    initStringOutput(O);
  }
  void copy(StringOutput& O, const char* ptr, const unsigned int n) {
    release(O);
    refer(O.buffer,ptr,n);
    initStringOutput(O);
  }
  void allocate(StringOutput& O, const unsigned int n) {
    allocate(O.buffer,n);
    initStringOutput(O);
  }

}

#endif
