
#ifndef _Lattice_Enumerate_Check_Interface_H_
#define _Lattice_Enumerate_Check_Interface_H_

#include "lattice/enumerate/run-data/interface.h"
#include "lattice/enumerate/check/method-name.h"

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

      template <unsigned int Len>
      bool operator()(LatticeEnumRunData<LSN,Dim,Len>& D) {
        Error("This Check is not Available!");
        return false;
      }

    private:

      LatticeEnumCheck(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <LatticeShapeName N,unsigned int D,LatticeEnumCheckMethodName EN>
  void release(LatticeEnumCheck<N,D,EN>& C) { C.clearData(); }

  template <LatticeShapeName N,unsigned int D,LatticeEnumCheckMethodName EN>
  bool IsValid(const LatticeEnumCheck<N,D,EN>& C) { return C.isvalid(); }

}

#include "lattice/enumerate/check/basic/specification.h"

#endif

