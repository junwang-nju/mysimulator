
#ifndef _Geometry_H_
#define _Geometry_H_

#include "fix-vector.h"

namespace std {

  enum GeometryType {

    FreeSpaceType

  };

  class FreeSpace {
  
    public:

      static const uint Type=FreeSpaceType;
      
      FreeSpace() {}
      
      FreeSpace(const FreeSpace& FS) {
        myError("Copier for FreeSpace is disabled");
      }

      FreeSpace& operator=(const FreeSpace& FS) { return *this; }

  };

  template <uint Dim>
  class PeriodicBox {

    public:

      typedef PeriodicBox<Dim>    Type;

      static const uint Dimension;

      fixVector<double,Dim> Box;

      fixVector<uint,Dim> EdgeFlag;

    private:

      fixVector<double,Dim> halfBox;

    public:

      PeriodicBox() : Box(), EdgeFlag(), halfBox() { EdgeFlag=1; }

      PeriodicBox(const Type&) { assert(false); }

      Type& operator=(const Type& PB) {
        Box=PB.Box;
        EdgeFlag=PB.EdgeFlag;
        halfBox=PB.halfBox;
        return *this;
      }

      void Set(const VectorBase<double>& pbBox, const uint& fg=1) {
        assert(pbBox.size()>=Dim);
        Box=pbBox;
        EdgeFlag=fg;
        halfBox=Box;
        halfBox.scale(0.5);
      }

      void Set(const VectorBase<double>& pbBox,
               const VectorBase<uint>& fgBox) {
        assert(pbBox.size()>=Dim);
        assert(fgBox.size()>=Dim);
        Box=pbBox;
        EdgeFlag=fgBox;
        halfBox=Box;
        halfBox.scale(0.5);
      }

      void Shift2Main(VectorBase<double>& v) const {
        double *it=v.begin();
        double *bt=const_cast<double*>(Box.data());
        double *be;
        double  hftmd,tmd,*nowtmd;
        for(uint i=0;i<Dim;++i) {
          if(EdgeFlag[i]==0)  continue;
          nowtmd=&v[i];
          hftmd=halfBox[i];
          tmd=Box[i];
          while(*nowtmd<-tmd)  *nowtmd+=tmd;
          while(*nowtmd>=tmd)  *nowtmd-=tmd;
        }
      }

  };

  template <uint Dim>
  const uint PeriodicBox<Dim>::Dimension=Dim;

}

#endif
