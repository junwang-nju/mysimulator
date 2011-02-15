
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
    Type& unget() {
      --property[DataInLocation];
      return *this;
    }
    Type& unget(const char& c) { return *this; }

  };

  template <typename T>
  bool IsAvailable(const SimpleDataInput<T>& I) {
    return IsAvailable(static_cast<const InputBase&>(I))&&
           IsAvailable(I.buffer)&&IsAvailable(I.property);
  }
  template <typename T>
  void release(SimpleDataInput<T>& I) {
    release(I.buffer);
    release(I.property);
    release(static_cast<InputBase&>(I));
  }
  template <typename T>
  void refer(SimpleDataInput<T>& I, const SimpleDataInput<T>& rI) {
    assert(IsAvailable(rI));
    release(I);
    refer(I.buffer,rI.buffer);
    refer(I.property,rI.property);
    refer(static_cast<InputBase&>(I),static_cast<const InputBase&>(rI));
  }
  template <typename T>
  void initSimpleDataInput(SimpleDataInput<T>& I) {
    allocate(I.property,DataInputNumberProperty);
    I.property[DataInLocation]=0;
    allocate(static_cast<InputBase&>(I));
  }
  template <typename T>
  void refer(SimpleDataInput<T>& I, const Vector<T>& vT) {
    assert(IsAvailable(vT));
    release(I);
    refer(I.buffer,vT);
    initSimpleDataInput(I);
  }
  template <typename T>
  void allocate(SimpleDataInput<T>& I, const unsigned int n) {
    release(I);
    allocate(I.buffer,n);
    initSimpleDataInput(I);
  }
  template <typename T>
  void imprint(SimpleDataInput<T>& I, const SimpleDataInput<T>& cI) {
    assert(IsAvailable(cI));
    allocate(I,cI.buffer.size);
  }
  template <typename T>
  void copy(SimpleDataInput<T>& I, const SimpleDataInput<T>& cI) {
    assert(IsAvailable(cI));
    imprint(I,cI);
    copy(I.buffer,cI.buffer);
    copy(I.property,cI.property);
    copy(static_cast<InputBase&>(I),static_cast<const InputBase&>(cI));
  }
  template <typename T>
  void copy(SimpleDataInput<T>& I, const Vector<T>& vT) {
    assert(IsAvailable(vT));
    allocate(I,vT.size);
    copy(I.buffer,vT);
    initSimpleDataInput(I);
  }

}

#endif
