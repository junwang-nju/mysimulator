
#ifndef _Lattice_Enumerate_Check_Interface_H_
#define _Lattice_Enumerate_Check_Interface_H_

#include "lattice/enumerate/run-data/interface.h"
#include "lattice/enumerate/check/method/name.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim,
            LatticeEnumCheckMethodName LEMN>
  struct LatticeEnumCheck {

    public:

      typedef LatticeEnumCheck<LSN,Dim,LEMN>  Type;

      LatticeEnumCheck() {}
      ~LatticeEnumCheck() { clearData(); }

      void clearData() {}
      bool isvalid() const { return false; }

    private:

      LatticeEnumCheck(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <LatticeShapeName LSN,unsigned int D,LatticeEnumCheckMethodName MN>
  bool IsValid(const LatticeEnumCheck<LSN,D,MN>& C) { return C.isvalid(); }

  template <LatticeShapeName LSN,unsigned int D,LatticeEnumCheckMethodName MN>
  void release(LatticeEnumCheck<LSN,D,MN>& C) { C.clearData(); }

}

#endif

