
#ifndef _Boundary_PeriodicBox_Interface_H_
#define _Boundary_PeriodicBox_Interface_H_

#include "vector/copy.h"
#include "vector/scale.h"
#include "intrinsic-type/shift.h"

namespace mysimulator {

  template <typename T>
  struct PeriodicBox {

    typedef PeriodicBox<T>    Type;

    Vector<T> box;
    Vector<T> hbox;
    Vector<bool>  flag;

    PeriodicBox() : box(), hbox(), flag() {}
    PeriodicBox(const Type&) { Error("Copier of PeriodicBox Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for PeriodicBox Disabled!");
      return *this;
    }
    ~PeriodicBox() { clearData(); }

    void clearData() { box.clearData(); hbox.clearData(); flag.clearData(); }
    const unsigned int dimension() const {
      assert(IsValid(box));
      return box.size;
    }
    void synchronize() {
      assert(IsValid(*this));
      copy(hbox,box);
      scale(hbox,0.5);
    }
    template <typename vT>
    void vectorNormalize(vT* v, const unsigned int dim,
                         const int off=iZero, const long step=lOne) const {
      assert(IsValid(v)&&IsValid(*this));
      unsigned int n=(dimension()<dim?dimension():dim);
      vT* pv=v+off;
      vT* pend=pv+n*step;
      T*  pb=const_cast<T*>(box.pdata);
      T*  ph=const_cast<T*>(hbox.pdata);
      bool* pf=const_cast<bool*>(flag.pdata);
      for(;pv!=pend;pv+=step,++pb,++ph,++pf) {
        if(!(*pf))  continue;
        while((*pv)<-(*ph))   shift(*pv,cOne,*pb);
        while((*pv)>=(*ph))   shift(*pv,-cOne,*pb);
      }
    }
    template <typename vT>
    void vectorNormalize(Vector<vT>& v) { vectorNormalize(v.pdata,v.size); }

  };

  template <typename T>
  bool IsValid(const PeriodicBox<T>& B) {
    return IsValid(B.box)&&IsValid(B.hbox)&&IsValid(B.flag);
  }

  template <typename T>
  void release(PeriodicBox<T>& B) { B.clearData(); }

}

#endif

