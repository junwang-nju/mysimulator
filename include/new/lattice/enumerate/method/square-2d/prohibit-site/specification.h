
#ifndef _Lattice_Enumerate_Method_Square2D_ProhibitSite_Specification_H_
#define _Lattice_Enumerate_Method_Square2D_ProhibitSite_Specification_H_

#include "lattice/enumerate/method/interface.h"
#include "lattice/node/coordinate/copy.h"

namespace mysimulator {

  template <>
  struct LatticeEnumMethod<SquareLattice,2U,LatticeEnumProhibitSite> {

    public:

      typedef LatticeEnumMethod<SquareLattice,2U,LatticeEnumProhibitSite>
              Type;
      typedef LatticeNodeCoordinate<SquareLattice,2U>::Type CoorType;
      typedef typename LatticeLibrary<SquareLattice,2U>::NodeType   NodeType;

      static const int Map[5][4];

      CoorType StartPos;
      Array1D<CoorType> HPos;

      LatticeEnumMethod() : StartPos(), HPos() {}
      ~LatticeEnumMethod() { clearData(); }

      void clearData() { StartPos.nullify(); release(HPos); }
      bool isvalid() const { return IsValid(HPos); }

      void PreProcess(
          Array1DContent<int>& Branch, Array1DContent<int>& State,
          Array1DContent<Square2DCoordinateType>& Pos,
          LatticeMesh<SquareLattice,2U>& Mesh, unsigned int& level,
          Array1DContent<NodeType*>& parent, Array1DContent<NodeType*>& child,
          NodeType* &now) {
        for(unsigned int i=0;i<HPos.size;++i) Mesh.set_occupied(HPos[i]);
        Branch[0]=4;
        State[0]=0;
        level=0;
        copy(Pos[level],StartPos);
        now=LatticeLibrary<SquareLattice,2U>::root;
        parent[level]=now->parent;
        child[level]=now->child;
      }

      int NextState(const Array1DContent<int>& Branch,
                    const Array1DContent<int>& State,
                    const Array1DContent<Square2DCoordinateType>& Pos,
                    const unsigned int& level) {
        unsigned int leveln1=level-1;
        return Map[Branch[leveln1]][Branch[level]];
      }

    private:

      LatticeEnumMethod(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  const int LatticeEnumMethod<SquareLattice,2U,LatticeEnumProhibitSite>::Map[5][4]=
    { {  1,  1,  1, -1 },
      {  1,  1, -1,  1 },
      {  1, -1,  1,  1 },
      { -1,  1,  1,  1 },
      {  1,  1,  1,  1 } };

}

#endif

