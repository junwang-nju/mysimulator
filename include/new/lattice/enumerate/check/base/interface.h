
#ifndef _Lattice_Enumerate_Check_Base_Interface_H_
#define _Lattice_Enumerate_Check_Base_Interface_H_

#include "array/2d/interface.h"
#include "lattice/shape/name.h"
#include "lattice/enumerate/check/method-name.h"
#include "io/error.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim,
            LatticeEnumCheckMethodName LEMN>
  struct LatticeEnumCheckBase {

    public:

      typedef LatticeEnumCheckBase<LSN,Dim,LEMN>  Type;

      static Array1D<Array2D<unsigned short> > SegMap;

      LatticeEnumCheckBase() : SegMap() {}
      ~LatticeEnumCheckBase() { clearData(); }

      void clearData() { release(SegMap); }
      bool isvalid() const { return IsValid(SegMap); }

      void load() { Error("Load for this Lattice Not Implemented!"); }

    private:

      LatticeEnumCheckBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <LatticeShapeName LN, unsigned int D, LatticeEnumCheckMethodName EN>
  Array1D<Array2D<unsigned short> > LatticeEnumCheckBase<LN,D,EN>::SegMap;

  template <LatticeShapeName LN, unsigned int D, LatticeEnumCheckMethodName EN>
  void release(LatticeEnumCheckBase<LN,D,EN>& DB) { DB.clearData(); }

  template <LatticeShapeName LN, unsigned int D, LatticeEnumCheckMethodName EN>
  bool IsValid(const LatticeEnumCheckBase<LN,D,EN>& DB) {
    return DB.isvalid();
  }

}

#include "lattice/enumerate/check/base/square-2d/load-specification.h"

#endif

