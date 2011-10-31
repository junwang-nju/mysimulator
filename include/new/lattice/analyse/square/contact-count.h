
#ifndef _Lattice_Analyse_Square_ContactCount_H_
#define _Lattice_Analyse_Square_ContactCount_H_

#include "array/1d/content/interface.h"
#include "lattice/mesh/interface.h"
#include "lattice/node/neighbor/number.h"
#include "lattice/node/coordinate/create.h"

namespace mysimulator {

  template <unsigned int Dim>
  unsigned int NumContacts(
      const Array1DContent<int>& Branch,
      const LatticeMesh<SquareLattice,Dim>& Mesh,
      const Array1DContent<typename LatticeNodeCoordinate<SquareLattice,Dim>::Type>& Pos) {
    unsigned int nc=0;
    const unsigned int NN=NumNeighbors<SquareLattice,Dim>();
    const unsigned int NNn1=NN-1;
    typename LatticeNodeCoordinate<SquareLattice,Dim>::Type tPos;
    for(unsigned int i=0;i<NN;++i) {
      if(i==static_cast<unsigned int>(Branch[1]))  continue;
      create<SquareLattice,Dim>(Pos[0],i,tPos);
      if(Mesh.occupied(tPos)) ++nc;
    }
    for(unsigned int n=1;n<static_cast<unsigned int>(Pos.last);++n) {
      for(unsigned int i=0;i<NN;++i) {
        if(i==static_cast<unsigned int>(Branch[n+1]))  continue;
        if(i==NNn1-Branch[n])  continue;
        create<SquareLattice,Dim>(Pos[n],i,tPos);
        if(Mesh.occupied(tPos)) ++nc;
      }
    }
    for(unsigned int i=0;i<NN;++i) {
      if(i==NNn1-Branch[Branch.last])  continue;
      create<SquareLattice,Dim>(Pos[Pos.last],i,tPos);
      if(Mesh.occupied(tPos)) ++nc;
    }
    nc=(nc>>1);
    return nc;
  }

}

#endif

