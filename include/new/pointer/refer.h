
#ifndef _Pointer_Refer_H_
#define _Pointer_Refer_H_

#include "pointer/interface.h"
#include "intrinsic-type/valid.h"
#include <cassert>

namespace mysimulator {

  template <typename T, typename PT>
  void _pointer_refer_basic(Pointer<T>& p, const PT& cp) {
    assert(IsValid(cp));
    p.clearData();
    p.state=0;
    p.pstate=0;
    p.delfunc=NULL;
  }

  template <typename T>
  void refer(Pointer<T>& p, Pointer<T>& cp) {
    _pointer_refer_basic(p,cp);
    if(cp.pstate<0) {
      p.ptr=cp.ptr;
      p.parent=&cp;
      ++(cp.state);
    } else {
      if(cp.parent==NULL) p.ptr=cp.ptr;
      else {
        p.ptr=cp.parent->ptr;
        ++(cp.parent->state);
      }
      p.parent=cp.parent;
    }
  }

  template <typename T>
  void refer(Pointer<T>& p, const T* const& cp) {
    _pointer_refer_basic(p,cp);
    p.ptr=const_cast<T* const&>(cp);
    p.parent=NULL;
  }

  template <typename T>
  void refer(Pointer<T>& p, const T& cp) {
    _pointer_refer_basic(p,cp);
    p.ptr=const_cast<T*>(&cp);
    p.parent=NULL;
  }

}

#endif

