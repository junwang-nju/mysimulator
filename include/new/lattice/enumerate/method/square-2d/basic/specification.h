
#ifndef _Lattice_Enumerate_Method_Square2D_Basic_Specification_H_
#define _Lattice_Enumerate_Method_Square2D_Basic_Specification_H_

#include "lattice/enumerate/method/interface.h"
#include "lattice/library/interface.h"

namespace mysimulator {

  template <>
  struct LatticeEnumMethod<SquareLattice,2U,LatticeEnumBasic> {

    public:

      typedef LatticeEnumMethod<SquareLattice,2U,LatticeEnumBasic>  Type;
      typedef typename LatticeLibrary<SquareLattice,2U>::NodeType   NodeType;

      static const int Map[3][4][4];

      LatticeEnumMethod() {}
      ~LatticeEnumMethod() { clearData(); }

      void clearData() {}
      bool isvalid() const { return true; }

      void PreProcess(
          Array1DContent<int>& Branch, Array1DContent<int>& State,
          Array1DContent<Square2DCoordinateType>& Pos,
          LatticeMesh<SquareLattice,2U>& Mesh, unsigned int& level,
          Array1DContent<NodeType*>& parent, Array1DContent<NodeType*>& child,
          NodeType* &now) {
          LatticeLibrary<SquareLattice,2U>::load();
        Branch[0]=0;
        State[0]=0;
        level=0;
        Pos[level].nullify();
        now=LatticeLibrary<SquareLattice,2U>::root;
        parent[level]=now->parent;
        child[level]=now->child;
      }

      int NextState(const Array1DContent<int>& Branch,
                    const Array1DContent<int>& State,
                    const Array1DContent<Square2DCoordinateType>& Pos,
                    const unsigned int& level) {
        unsigned int leveln1=level-1;
        return Map[State[leveln1]][Branch[leveln1]][Branch[level]];
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

