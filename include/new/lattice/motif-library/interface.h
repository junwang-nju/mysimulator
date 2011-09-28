
#ifndef _Lattice_Motif_Library_Interface_H_
#define _Lattice_Motif_Library_Interface_H_

#include "lattice/motif/import.h"
#include "array/2d/allocate.h"
#include "array/1d/fill.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  struct LatticeMotifLibrary {

    public:

      typedef LatticeMotifLibrary<LSN,Dim>  Type;

      static const unsigned int MaxBondOfMotif;
      static const unsigned int NumStart;
      static const char         relFileLoc[1024];

      static Array2D<LatticeMotif<LSN,Dim> >  map;
      static Array2D<unsigned char>  idtype;
      static Array2D<unsigned short> idstart;

      LatticeMotifLibrary() {}
      ~LatticeMotifLibrary() { clearData(); }

      void clearData() { release(map); release(idtype); release(idstart); }
      bool isvalid() const {
        return IsValid(map)&&IsValid(idtype)&&IsValid(idstart);
      }

      static void load(const char* Root) {
        if(IsValid(map)&&IsValid(idtype)&&IsValid(idstart))   return;
        static char tmbuff[1024];
        sprintf(tmbuff,"%s/%s/",Root,relFileLoc);
        _read(tmbuff);
      }

      static void _read(const char* fnTemplate) {
        static char nmbuff[1024], nmbuff1[1024], runmd[128], nowmd;
        FileInput ifs;
        Array1D<unsigned int> sz;
        allocate(sz,MaxBondOfMotif);
        sprintf(nmbuff,"%s-library",fnTemplate);
        ifs.open(nmbuff);
        if(IsFailed(ifs))   Error("Lattice Motif Library Not Found!");
        for(unsigned int i=0;i<MaxBondOfMotif;++i)  ifs>>nmbuff>>sz[i];
        ifs.close();
        allocate(map,sz);
        allocate(idtype,sz);
        allocate(idstart,MaxBondOfMotif,NumStart);
        for(unsigned int i=0;i<MaxBondOfMotif;++i)
          fill(idstart[i],static_cast<unsigned short>(sz[i]));
        release(sz);
        for(unsigned int i=0;i<MaxBondOfMotif;++i)
        for(unsigned int j=0;j<map[i].size;++j)
          allocate(map[i][j],i+1);
        FileInput ifs1;
        sprintf(nmbuff,"%s-library",fnTemplate);
        ifs.open(nmbuff);
        for(unsigned int i=0;i<MaxBondOfMotif;++i) {
          nowmd=' ';
          ifs>>nmbuff1;
          sprintf(nmbuff,"%s%s",fnTemplate,nmbuff1);
          ifs1.open(nmbuff);
          if(IsFailed(ifs1))   Error("Data for Motif Library Not Found!");
          for(unsigned int j=0;j<map[i].size;++j) {
            for(unsigned int k=0;k<map[i][j].bond.size;++k) {
              ifs1>>runmd;
              map[i][j].bond[k]=runmd[0];
            }
            ifs1>>runmd;
            _update_coordinate(map[i][j]);
            idtype[i][j]=runmd[0];
            if(nowmd!=runmd[0]) {
              nowmd=runmd[0];
              idstart[i][static_cast<unsigned int>(nowmd-'A')]=j;
            }
          }
          ifs1.close();
          ifs>>nmbuff1;
        }
        ifs.close();
      }

    private:

      LatticeMotifLibrary(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <LatticeShapeName LSN, unsigned int Dim>
  void release(LatticeMotifLibrary<LSN,Dim>& ML) { ML.clearData(); }

  template <LatticeShapeName LSN, unsigned int Dim>
  bool IsValid(LatticeMotifLibrary<LSN,Dim>& ML) { return ML.isvalid(); }

  template <LatticeShapeName LSN, unsigned int Dim>
  const unsigned int LatticeMotifLibrary<LSN,Dim>::MaxBondOfMotif=0;
  template <LatticeShapeName LSN, unsigned int Dim>
  const unsigned int LatticeMotifLibrary<LSN,Dim>::NumStart=0;
  template <LatticeShapeName LSN, unsigned int Dim>
  const char LatticeMotifLibrary<LSN,Dim>::relFileLoc[1024]="";

  template <LatticeShapeName LSN, unsigned int Dim>
  Array2D<LatticeMotif<LSN,Dim> > LatticeMotifLibrary<LSN,Dim>::map;
  template <LatticeShapeName LSN, unsigned int Dim>
  Array2D<unsigned char>    LatticeMotifLibrary<LSN,Dim>::idtype;
  template <LatticeShapeName LSN, unsigned int Dim>
  Array2D<unsigned short>   LatticeMotifLibrary<LSN,Dim>::idstart;

}

#include "lattice/motif-library/square-2d/specification.h"

#endif

