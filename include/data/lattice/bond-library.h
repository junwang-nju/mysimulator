
#ifndef _Bond_Library_H_
#define _Bond_Library_H_

#include "data/name/lattice-type.h"
#include "data/basic/property-list.h"
#include "data/basic/file-input.h"
#include "operation/basic/vector-io.h"

namespace std {

  template <unsigned int LatticeType, unsigned int LatticeDim>
  struct BondLib {
    static const unsigned int MaxBonds;
    static const unsigned int NeighborNumber;
    static const unsigned int MaxShiftConditions;
    static PropertyList<unsigned int> mshift; 
    static Vector<PropertyList<unsigned int> > mapper;
    static Vector<PropertyList<int> > xmapper;
    void loadlib(const char* ROOT) {
      Error("The library is not available");
    }
    void readlib(const char* ftemplate) {
      Vector<unsigned int> sz;
      static char nmbuff[1024];
      allocate(mapper,MaxBonds);
      allocate(xmapper,MaxBonds);
      allocate(sz,MaxBonds);
      copy(sz,MaxShiftConditions);
      allocate(mshift,sz);
      FileInput ifs;
      unsigned int nmotif;
      for(unsigned int i=0;i<MaxBonds;++i) {
        sprintf(nmbuff,"%s.%d-bond",ftemplate,i+1);
        allocate(ifs,nmbuff);
        ifs>>mshift[i];
        nmotif=mshift[i][MaxShiftConditions-1];
        allocate(sz,nmotif);
        copy(sz,i+1);
        allocate(mapper[i],sz);
        scale(sz,LatticeDim);
        allocate(xmapper[i],sz);
        for(unsigned int k=0;k<nmotif;++k)  ifs>>mapper[i][k];
        release(ifs);
      }
    }
    
    typedef BondLib<LatticeType,LatticeDim>   Type;
    
    BondLib() { loadlib("."); }
    BondLib(const char* ROOT) { loadlib(ROOT); }
    BondLib(const Type& BL) { Error("This library is not available"); }
    Type& operator=(const Type& BL) {
      Error("This Library is not available");
      return *this;
    }
    ~BondLib() { release(*this); }
};

  template <unsigned int LT, unsigned int LD>
  const unsigned int BondLib<LT,LD>::MaxBonds=0;

  template <unsigned int LT, unsigned int LD>
  const unsigned int BondLib<LT,LD>::NeighborNumber=0;

  template <unsigned int LT, unsigned int LD>
  const unsigned int BondLib<LT,LD>::MaxShiftConditions=0;

  template <unsigned int LT, unsigned int LD>
  PropertyList<unsigned int> BondLib<LT,LD>::mshift;

  template <unsigned int LT, unsigned int LD>
  Vector<PropertyList<unsigned int> > BondLib<LT,LD>::mapper;

  template <unsigned int LT, unsigned int LD>
  Vector<PropertyList<int> > BondLib<LT,LD>::xmapper;

  template <unsigned int LT, unsigned int LD>
  bool IsAvailable(const BondLib<LT,LD>& BL) {
    typedef BondLib<LT,LD>  Type;
    return IsAvailable(Type::mshift)&&IsAvailable(Type::mapper)&&
           IsAvailable(Type::xmapper);
  }

  template <unsigned int LT, unsigned int LD>
  void release(BondLib<LT,LD>& BL) {
    typedef BondLib<LT,LD>  Type;
    release(Type::mshift);
    release(Type::mapper);
    release(Type::xmapper);
  }
  
  template <unsigned int LT, unsigned int LD>
  const BondLib<LT,LD>& RunBondLibrary() {
    Error("This Library is not available");
    return BondLib<LT,LD>();
  }
  
  template <>
  const unsigned int BondLib<SquareLattice,2>::MaxBonds=10;
  template <>
  const unsigned int BondLib<SquareLattice,2>::NeighborNumber=4;
  template <>
  const unsigned int BondLib<SquareLattice,2>::MaxShiftConditions=3;

  template <>
  void BondLib<SquareLattice,2>::loadlib(const char* ROOT) {
    if(IsAvailable(*this))  return;
    static char tmbuff[1024];
    sprintf(tmbuff,"%s/include/data/lattice/square-2d",ROOT);
    readlib(tmbuff);
    int x,y;
    for(unsigned int i=0,nbond=0;i<MaxBonds;++i) {
      nbond=i+1;
      for(unsigned int k=0;k<mapper[i].nunit;++k) {
        x=y=0;
        for(unsigned int l=0,n=0;l<nbond;++l) {
          switch(mapper[i][k][l]) {
            case 0: ++x;  break;
            case 1: ++y;  break;
            case 2: --y;  break;
            case 3: --x;  break;
          }
          xmapper[i][k][n++]=x;
          xmapper[i][k][n++]=y;
        }
      }
    }
  }

  BondLib<SquareLattice,2>  *pBondLibSquare2D;
  
  template <>
  const BondLib<SquareLattice,2>& RunBondLibrary<SquareLattice,2>() {
    return *pBondLibSquare2D;
  }

}

#endif
