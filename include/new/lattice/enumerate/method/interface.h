
#ifndef _Lattice_Enumerate_Method_Interface_H_
#define _Lattice_Enumerate_Method_Interface_H_

#include "lattice/shape/name.h"
#include "lattice/enumerate/method/name.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim, LatticeEnumMethodName LEN>
  struct LatticeEnumMethod {
    public:
      typedef LatticeEnumMethod<LSN,Dim,LEN>  Type;
      LatticeEnumMethod() {}
      ~LatticeEnumMethod() { clearData(); }

      void clearData() {}
      bool isvalid() const { return false; }
    private:
      LatticeEnumMethod(const Type&) {}
      Type& operator=(const Type&) { return *this; }
  };

  template <LatticeShapeName LSN, unsigned int Dim, LatticeEnumMethodName LEN>
  void release(LatticeEnumMethod<LSN,Dim,LEN>& M) { M.clearData(); }

  template <LatticeShapeName LSN, unsigned int Dim, LatticeEnumMethodName LEN>
  bool IsValid(const LatticeEnumMethod<LSN,Dim,LEN>& M) { return M.isvalid(); }

}

#endif

