
#ifndef _Simple_Data_Input_H_
#define _Simple_Data_Input_H_

#include "data/name/simple-data-input-property.h"
#include "data/basic/input-base.h"

namespace std {
  
  template <typename T>
  struct SimpleDataInput : public InputBase {
    typedef SimpleDataInput<T>    Type;
    Vector<T> buffer;
    Vector<unsigned int> property;
    SimpleDataInput() : InputBase(), buffer(), property() {}
    SimpleDataInput(const unsigned int& n) : InputBase(), buffer(), property(){
      allocate(*this,n);
    }
    SimpleDataInput(const Vector<T>& vT) : InputBase(), buffer(), property() {
      refer(*this,vT);
    }
    SimpleDataInput(const Type&) { Error("Cannot create Simple-Data Input"); }
    Type& operator=(const Type&) {
      Error("Cannot copy Simple-Data Input");
      return *this;
    }
    ~SimpleDataInput() { release(*this); }
    
    template <typename IT>
    Type& __read(IT& value) {
      Warn("The types between output stream and data are different");
      SetState(FailBit);
      return *this;
    }
    Type& __read(T& value) {
      if(property[DataInLocation]==buffer.size) {
        Warn("Stream is used out");
        SetState(FailBit);
      } else {
        value=buffer[property[DataInLocation]];
        ++property[DataInLocation];
      }
      return *this;
    }
    Type& read(bool& b) { return __read(b); }
    Type& read(char& c) { return __read(c); }
    Type& read(unsigned char& uc) { return __read(uc); }
    Type& read(short& s) { return __read(s); }
    Type& read(unsigned short& us) { return __read(us); }
    Type& read(int& i) { return __read(i); }
    Type& read(unsigned int& u) { return __read(u); }
    Type& read(long& l) { return __read(l); }
    Type& read(unsigned long& ul) { return __read(ul); }
    Type& read(long long int& ll) { return __read(ll); }
    Type& read(unsigned long long int& ull) { return __read(ull); }
    Type& read(float& f) { return __read(f); }
    Type& read(double& d) { return __read(d); }
    Type& read(long double& ld) { return __read(ld); }
    Type& read(void*& ptr) { return __read(ptr); }
    Type& read(char* str) { return __read(str); }
    Type& unget(const T& value) {
      assert(value==buffer[property[DataInLocation]-1]);
      --property[DataInLocation];
      return *this;
    }

  };

  template <typename T>
  bool IsAvailable(const SimpleDataInput<T>& I) {
    return IsAvailable(static_cast<const InputBase&>(I))&&
           IsAvailable(I.buffer)&&IsAvailable(I.property);
  }

}

#endif
