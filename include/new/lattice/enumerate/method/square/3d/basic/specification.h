
#ifndef _Lattice_Enumerate_Method_Square3D_Basic_Specification_H_
#define _Lattice_Enumerate_Method_Square3D_Basic_Specification_H_

#include "lattice/enumerate/method/interface.h"
#include "lattice/library/interface.h"

namespace mysimulator {

  template <>
  struct LatticeEnumMethod<SquareLattice,3U,LatticeEnumBasic> {

    public:

      typedef LatticeEnumMethod<SquareLattice,3U,LatticeEnumBasic>
              Type;
      typedef typename LatticeLibrary<SquareLattice,3U>::NodeType   NodeType;

      static const int Map[4][6][6];

      LatticeEnumMethod() {}
      ~LatticeEnumMethod() { clearData(); }

      void clearData() {}
      bool isvalid() const { return true; }

      void PreProcess(
          Array1DContent<int>& Branch, Array1DContent<int>& State,
          Array1DContent<Square3DCoordinateType>& Pos,
          LatticeMesh<SquareLattice,3U>& Mesh, unsigned int& level,
          Array1DContent<NodeType*>& parent, Array1DContent<NodeType*>& child,
          NodeType* &now) {
        LatticeLibrary<SquareLattice,3U>::load();
        Branch[0]=0;
        State[0]=0;
        level=0;
        Pos[level].nullify();
        now=LatticeLibrary<SquareLattice,3U>::root;
        parent[level]=now->parent;
        child[level]=now->child;
      }

      int NextState(const Array1DContent<int>& Branch,
                    const Array1DContent<int>& State,
                    const Array1DContent<Square3DCoordinateType>& Pos,
                    const unsigned int& level) {
        unsigned int leveln1=level-1;
        return Map[State[leveln1]][Branch[leveln1]][Branch[level]];
      }

    private:

      LatticeEnumMethod(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  const int LatticeEnumMethod<SquareLattice,3U,LatticeEnumBasic>::Map[4][6][6]
    = {   {   {    1,   -1,   -1,   -1,   -1,   -1    },
              {    1,   -1,   -1,   -1,   -1,   -1    },
              {    1,   -1,   -1,   -1,   -1,   -1    },
              {    1,   -1,   -1,   -1,   -1,   -1    },
              {    1,   -1,   -1,   -1,   -1,   -1    },
              {    1,   -1,   -1,   -1,   -1,   -1    }   },
          {   {    1,    2,   -1,   -1,   -1,   -1    },
              {   -1,   -1,   -1,   -1,   -1,   -1    },
              {   -1,   -1,   -1,   -1,   -1,   -1    },
              {   -1,   -1,   -1,   -1,   -1,   -1    },
              {   -1,   -1,   -1,   -1,   -1,   -1    },
              {   -1,   -1,   -1,   -1,   -1,   -1    }   },
          {   {    2,    2,    3,   -1,    2,   -1    },
              {    2,    2,    3,   -1,   -1,    2    },
              {   -1,   -1,   -1,   -1,   -1,   -1    },
              {   -1,   -1,   -1,   -1,   -1,   -1    },
              {    2,   -1,    3,   -1,    2,    2    },
              {   -1,    2,    3,   -1,    2,    2    }   },
          {   {    3,    3,    3,    3,    3,   -1    },
              {    3,    3,    3,    3,   -1,    3    },
              {    3,    3,    3,   -1,    3,    3    },
              {    3,    3,   -1,    3,    3,    3    },
              {    3,   -1,    3,    3,    3,    3    },
              {   -1,    3,    3,    3,    3,    3    }   }   };

}

#endif

