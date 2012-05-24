
#ifndef _System_Content_Base_XData_Interface_H_
#define _System_Content_Base_XData_Interface_H_

#include "array2d-numeric/interface.h"

namespace mysimulator {

  template <typename T>
  class SystemContentBaseXData {

    public:

      typedef SystemContentBaseXData<T>  Type;

      Array2DNumeric<T> X;

      SystemContentBaseXData() : X() {}
      ~SystemContentBaseXData() { Clear(*this); }

      bool IsValid() const { return X.IsValid(); }

      void Allocate(const ArrayData<unsigned int>& sz) {
        assert(sz.IsValid());
        Clear(*this);
        X.Allocate(sz);
      }
      void Allocate(unsigned int n1, unsigned int n2) {
        Clear(*this);
        X.Allocate(n1,n2);
      }
      template <typename T1,template<typename> class AF>
      void Allocate(const Array2DBase<T1,AF>& A) {
        assert(A.IsValid());
        X.ImprintStructure(A);
      }
      template <typename T1>
      void Copy(const SystemContentBaseXData<T1>& C) {
        assert(IsValid());
        assert(C.IsValid());
        X.Copy(C.X);
      }
      void BlasCopy(const Type& C) {
        assert(IsValid());
        assert(C.IsValid());
        X.BlasCopy(C.X);
      }
      void Imprint(const Type& C) {
        assert(C.IsValid());
        X.Imprint(C.X);
      }
      void Refer(Type& C) { assert(C.IsValid()); X.Refer(C.X); }
      void Refer(Type& C,unsigned int b,unsigned int n) {
        assert(C.IsValid());
        X.Refer(C.X,b,n);
      }

    private:

      SystemContentBaseXData(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(SystemContentBaseXData<T>& C) { Clear(C.X); }

  template <typename T,typename T1>
  void _Copy(SystemContentBaseXData<T>& C,const SystemContentBaseXData<T1>& B) {
    C.Copy(B);
  }

  template <typename T>
  void _Imprint(SystemContentBaseXData<T>& C,
                const SystemContentBaseXData<T>& BC) {
    C.Imprint(BC);
  }

}

#endif

