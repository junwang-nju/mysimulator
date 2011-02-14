
#ifndef _Simple_Data_Output_H_
#define _Simple_Data_Output_H_

#include "data/basic/output-base.h"
#include "data/name/simple-data-output-property.h"

namespace std {
  
  template <typename T>
  struct SimpleDataOutput : public OutputBase {
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
    SimpleDataOutput(const SimpleDataOutput&) {
      Error("Cannot create Simple-Data Output");
    }
    SimpleDataOutput& operator=(const SimpleDataOutput&) {
      Error("Cannot copy Simple-Data Output");
      return *this;
    }
    ~SimpleDataOutput() { release(*this); }
    
    template <typename OT>
    SimpleDataOutput& __write(const OT& value) {
      return *this;
    }
    SimpleDataOutput& __write(const T& value) {
      buffer[property[DataOutLocation]]=value;
      ++property[DataOutLocation];
      return *this;
    }
    SimpleDataOutput& write(const bool& b) { return __write(b); }
    SimpleDataOutput& write(const char& c) { return __write(c); }
    SimpleDataOutput& write(const unsigned char& uc) { return __write(uc); }
    SimpleDataOutput& write(const short& s) { return __write(s); }
    SimpleDataOutput& write(const unsigned short& us) { return __write(us); }
    SimpleDataOutput& write(const int& i) { return __write(i); }
    SimpleDataOutput& write(const unsigned int& u) { return __write(u); }
    SimpleDataOutput& write(const long& l) { return __write(l); }
    SimpleDataOutput& write(const unsigned long& ul) { return __write(ul); }
    SimpleDataOutput& write(const long long int& ll) { return __write(ll); }
    SimpleDataOutput& write(const unsigned long long int& ull) {
      return __write(ull);
    }
    SimpleDataOutput& write(const float& f) { return __write(f); }
    SimpleDataOutput& write(const double& d) { return __write(d); }
    SimpleDataOutput& write(const long double& ld) { return __write(ld); }
    SimpleDataOutput& write(const void* ptr) { return __write(ptr); }
    SimpleDataOutput& write(const char* str) { return __write(str); }

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
