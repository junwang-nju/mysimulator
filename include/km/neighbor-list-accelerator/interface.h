
#ifndef _Neighbor_List_Accelerator_Interface_H_
#define _Neighbor_List_Accelerator_Interface_H_

#include "array2d-numeric/interface.h"

namespace mysimulator {

  template <typename T,typename GT>
  class NeighborListAccelerator {

    public:

      typedef NeighborListAccelerator<T,GT>   Type;

      NeighborListAccelerator() {}
      virtual ~NeighborListAccelerator() { Clear(*this); }

      virtual bool IsValid() const = 0;
      virtual void ImprintX(const Array2DNumeric<T>&) = 0;
      virtual void Init(const Array2DNumeric<T>&) = 0;
      virtual void Update(const Array2DNumeric<T>&) = 0;

    private:

      NeighborListAccelerator(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(NeighborListAccelerator<T,GT>& A) {}

}

#endif

