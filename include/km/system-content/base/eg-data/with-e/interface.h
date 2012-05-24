
#ifndef _System_Content_Base_EGData_WithE_Interface_H_
#define _System_Content_Base_EGData_WithE_Interface_H_

#include "array-numeric/interface.h"
#include "array2d/base/interface.h"

namespace mysimulator {

  template <typename T>
  class SystemContentBaseEData {

    public:

      typedef SystemContentBaseEData<T> Type;

      ArrayNumeric<T> Energy;

      SystemContentBaseEData() : Energy() {}
      ~SystemContentBaseEData() { Clear(*this); }

      bool IsValid() const { return Energy.IsValid(); }

      void Allocate() { Clear(*this); Energy.Allocate(1); }
      void Allocate(const ArrayNumeric<unsigned int>&) { Allocate(); }
      void Allocate(unsigned int,unsigned int) { Allocate(); }
      template <typename T1,template<typename> class AF>
      void Allocate(const Array2DBase<T1,AF>&) { Allocate(); }
      template <typename T1>
      void Copy(const SystemContentBaseEData<T1>& D) { Energy.Copy(D.Energy); }
      void BlasCopy(const Type& D) { Copy(D); }
      void Imprint(const Type& D) { Allocate(); }
      void Refer(Type& D) { Energy.Refer(D.Energy); }
      void Refer(Type& D,unsigned int,unsigned int) { Refer(D); }

      void Nullify() { assert(Energy.IsValid()); Energy[0]=0; }
      template <typename T1>
      void Append(const SystemContentBaseEData<T1>& D) {
        Energy[0]+=D.Energy[0];
      }

    private:

      SystemContentBaseEData(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(SystemContentBaseEData<T>& D) { Clear(D.Energy); }

  template <typename T,typename T1>
  void _Copy(SystemContentBaseEData<T>& D,const SystemContentBaseEData<T1>& B) {
    D.Copy(B);
  }

  template <typename T>
  void _Imprint(SystemContentBaseEData<T>& D,
                const SystemContentBaseEData<T>& BD) {
    D.Imprint(BD);
  }

}

#endif

