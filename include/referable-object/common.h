
#ifndef _Referable_Object_Common_H_
#define _Referable_Object_Common_H_

#include "IO/error.h"
#include "referable-object/state-name.h"

namespace mysimulator {

  template <typename T>
  struct Object {

    typedef Object<T> Type;

    T* pdata;
    ObjectStateName flag;

    Object() : pdata(NULL), flag(Unused) {}
    Object(const Type&) { Error("Copier of Object Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for Object Disabled!");
      return *this;
    }
    ~Object() { release(); }

    void release() {
      if(flag==Unused)  return;
      if(flag==Referred)  pdata=NULL;
      else if(flag==Allocated)  delete pdata;
      flag=Unused;
    }
    T& operator()() { assert(IsValid(*this)); return *pdata; }
    const T& operator()() const { assert(IsValid(*this)); return *pdata; }
  };

  template <typename T>
  bool IsValid(const Object<T>& O) {
    return (O.pdata!=NULL)&&(O.flag!=Unused)&&IsValid(*(O.pdata));
  }

  template <typename T1, typename T2>
  void copy(Object<T1>& O, const Object<T2>& cO) {
    assert(IsValid(O)&&IsValid(cO));
    copy(O(),cO());
  }

  template <typename T1, typename T2>
  void copy(Object<T1>& O, const T2& ovalue) {
    assert(IsValid(O));
    copy(O(),ovalue);
  }

  template <typename T1, typename T2>
  void copy(T1& ovalue, const Object<T2>& O) {
    assert(IsValid(O));
    copy(ovalue,O());
  }

  template <typename T>
  void refer(Object<T>& O, const Object<T>& cO) {
    assert(IsValid(cO));
    O.release();
    O.pdata=const_cast<T*>(cO.pdata);
    O.flag=Referred;
  }

  template <typename T>
  void refer(Object<T>& O, const T& ovalue) {
    O.release();
    O.pdata=const_cast<T*>(&ovalue);
    O.flag=Referred;
  }

  template <typename T>
  void allocate(Object<T>& O) {
    O.release();
    O.pdata=new T;
    O.flag=Allocated;
  }

}

#endif

