
#ifndef _Referable_Object_Interface_H_
#define _Referable_Object_Interface_H_

#include "io/error.h"
#include "referable-object/state-name.h"
#include "intrinsic-type/allocate.h"
#include "intrinsic-type/release.h"
#include "generic/release.h"
#include "intrinsic-type/validity-check.h"

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
    ~Object() { clearData(); }

    void clearData() {
      if(flag==Unused)  return;
      if(flag==Allocated) { release(*pdata);  release(pdata); }
      pdata=NULL;
      flag=Unused;
    }
    T& operator()() { assert(IsValid(*this)); return *pdata; }
    const T& operator()() const { assert(IsValid(*this)); return *pdata; }
  };

  template <typename T>
  bool IsValid(const Object<T>& O) {
    return (O.pdata!=NULL)&&(O.flag!=Unused);
  }

  template <typename T>
  void release(Object<T>& O) { O.clearData(); }

}

#endif

