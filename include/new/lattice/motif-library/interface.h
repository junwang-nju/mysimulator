
#ifndef _Lattice_Motif_Library_Interface_H_
#define _Lattice_Motif_Library_Interface_H_

#include "lattice/motif/import.h"
#include "array/2d/allocate.h"
//#include "io/input/file/interface.h"
#include "array/1d/io.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  struct LatticeMotifLibrary {

    public:

      struct RangeType {
        unsigned short first, last;
      };

      typedef LatticeMotifLibrary<LSN,Dim>  Type;

      static const unsigned int MaxBondOfMotif;
      static const unsigned int NumRanges;
      static const char         relLocation[1024];

      static Array2D<LatticeMotif>  map;
      static Array2D<RangeType>  idrange;

      LatticeMotifLibrary() {}
      ~LatticeMotifLibrary() { clearData(); }

      void clearData() { release(map); release(idrange); }
      bool isvalid() const { return IsValid(map)&&IsValid(idrange); }

      static void load(const char* Root) {
        if(isvalid())   return;
        static char tmbuff[1024];
        sprintf(tmbuff,"%s/%s/",Root,relLocation);
        _read(tmbuff);
      }

      static void _read(const char* fnTemplate) {
        static char nmbuff[1024], nmbuff1[1024];
        allocate(idrange,MaxBondOfMotif,NumRanges);
        FileInput ifs;
        sprintf(nmbuff,"%s-library",fnTemplate);
        ifs.open(nmbuff);
        if(IsFailed(ifs))   Error("Lattice Motif Library Not Found!");
        Array1D<unsigned int> sz;
        allocate(sz,MaxBondOfMotif);
        for(unsigned int i=0;i<MaxBondOfMotif;++i) {
          for(unsigned int j=0;j<NumRanges;++j)
            ifs>>idrange[i][j].first>>idrange[i][j].last;
          ifs>>nmbuff;
          sz[i]=idrange[i][NumRanges-1].last;
        }
        ifs.close();
        allocate(map,sz);
        release(sz);
        for(unsigned int i=0;i<MaxBondOfMotif;++i)
        for(unsigned int j=0;j<map[i].size;++j)
          allocate(map[i][j],i+1,Dim);
        FileInput ifs1;
        sprintf(nmbuff,"%s-library",fnTemplate);
        ifs.open(nmbuff);
        unsigned short ts;
        for(unsigned int i=0;i<MaxBondOfMotif;++i) {
          for(unsigned int j=0;j<NumRanges;++j) ifs>>ts>>ts;
          ifs>>nmbuff1;
          sprintf(nmbuff,"%s%s",fnTemplate,nmbuff1);
          ifs1.open(nmbuff);
          if(IsFailed(ifs))   Error("Data for Motif Library Not Found!");
          for(unsigned int j=0;j<map[i].size;++j) {
            ifs1>>map[i][j].bond;
            _update_coordinate<LSN,Dim>(map[i][j]);
          }
          ifs1.close();
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
  const unsigned int LatticeMotifLibrary<LSN,Dim>::NumRanges=0;
  template <LatticeShapeName LSN, unsigned int Dim>
  const unsigned int LatticeMotifLibrary<LSN,Dim>::relLocation[1024]="";

  template <LatticeShapeName LSN, unsigned int Dim>
  Array2D<LatticeMotif> LatticeMotifLibrary<LSN,Dim>::map;
  template <LatticeShapeName LSN, unsigned int Dim>
  Array2D<LatticeMotifLibrary<LSN,Dim>::RangeType>
  LatticeMotifLibrary<LSN,Dim>::idrange;

}

#endif

