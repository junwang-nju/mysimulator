
#ifndef _Simple_Data_Output_H_
#define _Simple_Data_Output_H_

#include "data/basic/output-base.h"
#include "data/name/simple-data-output-property.h"

namespace std {
  
  template <typename T>
  struct SimpleDataOutput : public OutputBase {
    typedef SimpleDataOutput<T>   Type;
    Vector<T> buffer;
    Vector<unsigned int> property;
    SimpleDataOutput() : OutputBase(), buffer(), property() {}
    SimpleDataOutput(const unsigned int& n)
        : OutputBase(), buffer(), property() {
      allocate(*this,n);
    }
    SimpleDataOutput(const Vector<T>& vT) : OutputBase(), buffer(), property() {
      refer(*this,vT);
    }
    SimpleDataOutput(const Type&){ Error("Cannot create Simple-Data Output"); }
    Type& operator=(const Type&) {
      Error("Cannot copy Simple-Data Output");
      return *this;
    }
    ~SimpleDataOutput() { release(*this); }
    
    template <typename OT>
    Type& __write(const OT& value) { return *this; }
    Type& __write(const T& value) {
      if(property[DataOutLocation]==buffer.size) {
        Warn("Output Buffer is used out!");
        SetState(FailBit);
      } else {
        buffer[property[DataOutLocation]]=value;
        ++property[DataOutLocation];
      }
      return *this;
    }
    Type& write(const bool& b) { return __write(b); }
    Type& write(const char& c) { return __write(c); }
    Type& write(const unsigned char& uc) { return __write(uc); }
    Type& write(const short& s) { return __write(s); }
    Type& write(const unsigned short& us) { return __write(us); }
    Type& write(const int& i) { return __write(i); }
    Type& write(const unsigned int& u) { return __write(u); }
    Type& write(const long& l) { return __write(l); }
    Type& write(const unsigned long& ul) { return __write(ul); }
    Type& write(const long long int& ll) { return __write(ll); }
    Type& write(const unsigned long long int& ull) { return __write(ull); }
    Type& write(const float& f) { return __write(f); }
    Type& write(const double& d) { return __write(d); }
    Type& write(const long double& ld) { return __write(ld); }
    Type& write(const void* ptr) { return __write(ptr); }
    Type& write(const char* str) { return __write(str); }

  };

  template <typename T>
  bool IsAvailable(const SimpleDataOutput<T>& O) {
    return IsAvailable(O.buffer)&&IsAvailable(O.property)&&
           IsAvailable(static_cast<const OutputBase&>(O));
  }
  template <typename T>
  void release(SimpleDataOutput<T>& O) {
    release(O.buffer);
    release(O.property);
    release(static_cast<OutputBase&>(O));
  }
  template <typename T>
  void initSimpleDataOutput(SimpleDataOutput<T>& O) {
    allocate(O.property,DataOutputNumberProperty);
    O.property[DataOutLocation]=0;
    allocate(static_cast<OutputBase&>(O));
  }
  template <typename T>
  void refer(SimpleDataOutput<T>& O, const SimpleDataOutput<T>& rO) {
    assert(IsAvailable(rO));
    release(O);
    refer(O.buffer,rO.buffer);
    refer(O.property,rO.property);
    refer(static_cast<OutputBase&>(O),static_cast<const OutputBase&>(rO));
  }
  template <typename T>
  void refer(SimpleDataOutput<T>& O, const Vector<T>& bf) {
    assert(IsAvailable(bf));
    release(O);
    refer(O.buffer,bf);
    initSimpleDataOutput(O);
  }
  template <typename T>
  void allocate(SimpleDataOutput<T>& O, const unsigned int& n) {
    release(O);
    allocate(O.buffer,n);
    initSimpleDataOutput(O);
  }
  template <typename T>
  void imprint(SimpleDataOutput<T>& O, const SimpleDataOutput<T>& cO) {
    assert(IsAvailable(cO));
    allocate(O,cO.buffer.size);
  }
  template <typename T>
  void copy(SimpleDataOutput<T>& O, const SimpleDataOutput<T>& cO) {
    imprint(O,cO);
    copy(O.buffer,cO.buffer);
    copy(O.property,cO.property);
    copy(static_cast<OutputBase&>(O),static_cast<const OutputBase&>(cO));
  }

}

#endif
