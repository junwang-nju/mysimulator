
#ifndef _Lattice_Enumerate_Method_Base_Interface_H_
#define _Lattice_Enumerate_Method_Base_Interface_H_

#include "lattice/library/interface.h"
#include "object/interface.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  struct LatticeEnumMethodBase {

    public:

      typedef LatticeEnumMethodBase<LSN,Dim>  Type;

      Object<LatticeLibrary<LSN,Dim> >  Lib;

      LatticeEnumMethodBase() : Lib() {}
      ~LatticeEnumMethodBase() { clearData(); }

      void clearData() { release(Lib); }
      bool isvalid() const { return IsValid(Lib); }

    private:

      LatticeEnumMethodBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <LatticeShapeName LSN, unsigned int Dim>
  void release(LatticeEnumMethodBase<LSN,Dim>& M) { M.clearData(); }

  template <LatticeShapeName LSN, unsigned int Dim>
  bool IsValid(const LatticeEnumMethodBase<LSN,Dim>& M) { return M.isvalid(); }

}

#endif

