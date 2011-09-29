
#ifndef _Lattice_Enumerate_Square2D_Act_H_
#define _Lattice_Enumerate_Square2D_Act_H_

namespace mysimulator {

  template <unsigned int Len, LatticeSquare2DEnumCheckMethodName EMethod>
  unsigned long long enumerate(
      const LatticeSquare2DEnumCheck<EMethod>& Check,
      LatticeSquare2DEnumProcessBase<Len>& Proc) {
    unsigned long long NC=0;
    LatticeSquare2DEnumRunData<Len> Data;
    allocate(Data);
    return NC;
  }

}

#endif

