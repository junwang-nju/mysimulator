
#ifndef _Bond_Library_H_
#define _Bond_Library_H_

#include "data/name/lattice-type.h"
#include "data/name/bond-library-property.h"
#include "data/basic/property-list.h"
#include <fstream>

namespace std {

  template <unsigned int LatticeType, unsigned int LatticeDim>
  struct BondLib {

    private:
      static Vector<unsigned int> property;
      static Vector<unsigned int> motifNumber;
      static Vector<unsigned int> motifShift;
      static PropertyList<unsigned int> confShift;
      static PropertyList<unsigned int> mapper;
      static PropertyList<int> siteMapper;
      void loadLib(const char*) { myError("This library is not available"); }
      void readlib(const char* fname) {
        allocate(motifNumber,BondNumber());
        allocate(motifShift,BondNumber());
        Vector<unsigned int> sz(BondNumber());
        copy(sz,LatticeDim+1);
        allocate(confShift,sz);
        ifstream ifs(fname);
        for(unsigned int i=0;i<BondNumber();++i)
        for(unsigned int k=0;k<=LatticeDim;++k)
          ifs>>confShift[i][k];
        motifShift[0]=0;
        for(unsigned int i=1;i<BondNumber();++i)
          motifShift[i]=confShift[i-1][LatticeDim];
        motifNumber[0]=confShift[0][LatticeDim];
        for(unsigned int i=1;i<BondNumber();++i)
          motifNumber[i]=confShift[i][LatticeDim]-confShift[i-1][LatticeDim];
        allocate(sz,confShift[BondNumber()-1][LatticeDim]);
        for(unsigned int i=0,n=0;i<BondNumber();++i)
        for(unsigned int k=0;k<motifNumber[i];++k)
          sz[n++]=BondNumber()-i;
        allocate(mapper,sz);
        scale(sz,LatticeDim);
        allocate(siteMapper,sz);
        for(unsigned int i=0;i<mapper.nunit;++i)
          ifs>>mapper[i];
        ifs.close();
      }

    public:

      typedef BondLib<LatticeType,LatticeDim> Type;

      BondLib() { loadLib("."); }
      BondLib(const char* ROOT) { loadLib(ROOT); }
      BondLib(const Type& BL) { myError("This Library is not available"); }
      Type& operator=(const Type& BL) {
        myError("This Library is not available");
        return *this;
      }
      ~BondLib() { releaseLib(); }
      void releaseLib() {
        release(Type::property);
        release(Type::motifNumber);
        release(Type::motifShift);
        release(Type::confShift);
        release(Type::mapper);
        release(Type::siteMapper);
      }
      const bool libAvailable() const {
        return IsAvailable(property)&&IsAvailable(motifNumber)&&
               IsAvailable(motifShift)&&IsAvailable(confShift)&&
               IsAvailable(mapper)&&IsAvailable(siteMapper);
      }
      const unsigned int BondNumber() const {
        return property[BondNumberPerByte];
      }
      const unsigned int NeighborNumber() const {
        return property[NeighborNumberPerSite];
      }
      const unsigned int MotifNumber(const unsigned int msize) const {
        return motifNumber[msize];
      }
      const unsigned int MotifShift(const unsigned int msize) const {
        return motifShift[msize];
      }
      const Vector<unsigned int>& Bond(const unsigned int mid) const {
        return mapper[mid];
      }
      const Vector<int>& Site(const unsigned int mid) const {
        return siteMapper[mid];
      }
  };
  
  template <unsigned int LT, unsigned int LD>
  bool IsAvailable(const BondLib<LT,LD>& BL) {
    return BL.libAvailable();
  }
  template <unsigned int LT, unsigned int LD>
  void release(BondLib<LT,LD>& BL) {
    BL.releaseLib();
  }

  template <unsigned int LT, unsigned int LD>
  Vector<unsigned int> BondLib<LT,LD>::property;

  template <unsigned int LT, unsigned int LD>
  Vector<unsigned int> BondLib<LT,LD>::motifNumber;

  template <unsigned int LT, unsigned int LD>
  Vector<unsigned int> BondLib<LT,LD>::motifShift;

  template <unsigned int LT, unsigned int LD>
  PropertyList<unsigned int> BondLib<LT,LD>::confShift;

  template <unsigned int LT, unsigned int LD>
  PropertyList<unsigned int> BondLib<LT,LD>::mapper;

  template <unsigned int LT, unsigned int LD>
  PropertyList<int> BondLib<LT,LD>::siteMapper;

  template <unsigned int LT, unsigned int LD>
  const BondLib<LT,LD>& RunBondLibrary() {
    myError("This Library is not available");
  }

}

#include <cstring>

namespace std {

  template <>
  void BondLib<SquareLattice,2>::loadLib(const char* ROOT) {
    if(libAvailable())  return;
    static char buff[1024];
    strcpy(buff,ROOT);
    strcat(buff,"/include/data/lattice/square-2d.conf");
    allocate(property,BondLibraryPropertyNumberParameter);
    property[BondNumberPerByte]=4;
    property[NeighborNumberPerSite]=4;
    readlib(buff);
    int x,y;
    for(unsigned int i=0;i<mapper.nunit;++i) {
      x=y=0;
      for(unsigned int k=0,n=0;k<mapper[i].size;++k) {
        switch(mapper[i][k]) {
          case 0: ++x;  break;
          case 1: ++y;  break;
          case 2: --y;  break;
          case 3: --x;  break;
        }
        siteMapper[i][n++]=x;
        siteMapper[i][n++]=y;
      }
    }
  }

  BondLib<SquareLattice,2> *pBondLibSquare2D;

  template <>
  const BondLib<SquareLattice,2>& RunBondLibrary<SquareLattice,2>() {
    return *pBondLibSquare2D;
  }
  
}

#endif

