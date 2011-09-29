
#ifndef _Lattice_Enumerate_Check_Method_Square2D_Basic_Specification_H_
#define _Lattice_Enumerate_Check_Method_Square2D_Basic_Specification_H_

#include "lattice/enumerate/check/interface.h"
#include "lattice/enumerate/run-data/interface.h"

namespace mysimulator {

  template <>
  struct LatticeEnumCheck<SquareLattice,2U,LatticeEnumCheckMethodSquare2DBasic>{

    public:

      typedef
      LatticeEnumCheck<SquareLattice,2U,LatticeEnumCheckMethodSquare2DBasic>
      Type;

      LatticeEnumCheck() {}
      ~LatticeEnumCheck() { clearData(); }

      void clearData() {}
      bool isvalid() const { return true; }

      template <unsigned int Len>
      bool operator()(LatticeEumRunData<SquareLattice,2U,Len>& D) {
        if(D.RunMotif>0) {
          for(unsigned int i=D.RunMotifHead;i<=D.RunMotifEnd;++i)
            D.Pos[i].us=D.HeadPos[D.RunMotif].us+LatticeMotifLibrary<SquareLattice,2U>::map[D.RunMotifSize-1][D.RunMotif].coordinate[i-D.RunMotifHead].us;
          // TEMP MARK: here define many variables for run-data
        }
        return true;
      }

    private:

      LatticeEnumCheck(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

