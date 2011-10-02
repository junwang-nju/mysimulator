
#ifndef _Lattice_Enumerate_Method_Square2D_Basic_Specification_H_
#define _Lattice_Enumerate_Method_Square2D_Basic_Specification_H_

#include "lattice/enumerate/method/interface.h"
#include "array/1d/content/interface.h"

namespace mysimulator {

  template <>
  struct LatticeEnumMethod<SquareLattice,2U,LatticeEnumBasic> {

    public:

      typedef LatticeEnumMethod<SquareLattice,2U,LatticeEnumBasic>  Type;

      static const int Map[3][4][4];

      LatticeEnumMethod() {}
      ~LatticeEnumMethod() { clearData(); }

      void clearData() {}
      bool isvalid() const { return true; }

      int NextState(const int& pBranch, const int& Branch, const int& pState) {
        return Map[pState][pBranch][Branch];
      }

  };

  const int LatticeEnumMethod<SquareLattice,2U,LatticeEnumBasic>::Map[3][4][4]=
    { { {  1, -1, -1, -1},
        {  1, -1, -1, -1},
        {  1, -1, -1, -1},
        {  1, -1, -1, -1} },
      { {  1,  2, -1, -1},
        { -1, -1, -1, -1},
        { -1, -1, -1, -1},
        { -1, -1, -1, -1} },
      { {  2,  2,  2, -1},
        {  2,  2, -1,  2},
        {  2, -1,  2,  2},
        { -1,  2,  2,  2} } };

}

#endif

