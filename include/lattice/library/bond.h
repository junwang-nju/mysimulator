
#ifndef _Lattice_Library_Bond_H_
#define _Lattice_Library_Bond_H_

#include "list/allocate.h"
#include "vector/scale.h"
#include "vector/copy.h"
#include "list/io.h"
#include "vector/allocate.h"
#include "io/input/file/interface.h"

namespace mysimulator {

  template <unsigned int LatticeType, unsigned int Dimension>
  struct LatticeBondLib {

    typedef LatticeBondLib<LatticeType,Dimension>   Type;

    static const unsigned int MaxBonds;
    static const unsigned int NumNeighbors;
    static const unsigned int NumberShifts;
    static List<unsigned int> shiftLoc;
    static Vector<List<unsigned int> >  map;
    static Vector<List<int> > coordinateMap;

    LatticeBondLib() { load("."); }
    LatticeBondLib(const char* Root) { load(Root); }
    LatticeBondLib(const Type&) {
      Error("Copier of LatticeBondLib Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for LatticeBondLib Disabled!");
      return *this;
    }
    ~LatticeBondLib() { clearData(); }

    void load(const char* Root) {
      Error("Lattice Library Loading Disabled!");
    }

    void clearData() {
      release(shiftLoc);
      release(map);
      release(coordinateMap);
    }
    void read(const char* fTemplate) {
      Vector<unsigned int> sz;
      static char nmbuffer[1024];
      allocate(sz,MaxBonds);
      copy(sz,NumberShifts);
      allocate(shiftLoc,sz);
      allocate(map,MaxBonds);
      allocate(coordinateMap,MaxBonds);
      FileInput ifs;
      unsigned int nmotif;
      for(unsigned int i=1;i<=MaxBonds;++i) {
        sprintf(nmbuffer,"%s.%d-bond",fTemplate,i);
        ifs.open(nmbuffer);
        ifs>>shiftLoc[i];
        nmotif=shiftLoc[i][NumberShifts-1];
        allocate(sz,nmotif);
        copy(sz,i);
        allocate(map[i],sz);
        scale(sz,Dimension);
        allocate(coordinateMap[i],sz);
        for(unsigned int j=i-1,k=0;k<nmotif;++k)  ifs>>map[j][k];
        ifs.close();
      }
    }

  };

}

#endif

