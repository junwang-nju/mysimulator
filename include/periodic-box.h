
#ifndef _Periodi_Box_H_
#define _Periodi_Box_H_

#include "geometry-id.h"
#include "displacement-direct.h"
#include "var-vector.h"
#include "ref-vector.h"

namespace std {

  enum PeriodicityState {
    PeriodicON=1,
    PeriodicOFF=0
  };

  template <template <typename> class VecType>
  class PeriodicBox {

    protected:

      VecType<double> Box;

      VecType<unsigned int> EdgeFlag;

      VecType<double> halfBox;

    public:

      static const unsigned int TypeID;

      typedef PeriodicBox<VecType>  Type;

      PeriodicBox() : Box(), EdgeFlag(), halfBox() {}

      PeriodicBox(const unsigned int Dim)
        : Box(), EdgeFlag(), halfBox() {
        allocate(Dim);
      }

      PeriodicBox(const Type& PBB) {
        myError("Cannot create from periodic box base");
      }

      ~PeriodicBox() { clear(); }

      void clear() { Box.clear(); EdgeFlag.clear(); halfBox.clear(); }

    protected:

      void update() { halfBox=Box;  halfBox.scale(0.5); }

    public:

      Type& operator=(const Type& PBB) {
        Box=PBB.Box;
        EdgeFlag=PBB.EdgeFlag;
        update();
        return *this;
      }

      template <template <typename> class iVecType>
      Type& operator=(const PeriodicBox<iVecType>& PB) {
        Box=PB.Box;
        EdgeFlag=PB.EdgeFlag;
        update();
        return *this;
      }

      const VecType<double>& box() const { return Box; }

      VecType<double>& box() { return Box; }

      const VecType<double>& hfbox() const { return halfBox; }

      VecType<double>& hfbox() { return halfBox; }

      const VecType<unsigned int>& flag() const { return EdgeFlag; }

      VecType<unsigned int>& flag() { return EdgeFlag; }

      void Set(const VectorBase<double>& pbBox,
               const VectorBase<unsigned int>& fgBox) {
        Box=pbBox;
        EdgeFlag=fgBox;
        update();
      }

      void Set(const VectorBase<double>& pbBox,
               const unsigned int fg=PeriodicON) {
        Box=pbBox;
        EdgeFlag=fg;
        update();
      }

      void shift2main(VectorBase<double>& v) const {
        assert(v.size()>=Box.size());
        double tmd,bmd,bhd;
        unsigned int n=Box.size();
        for(unsigned int i=0;i<n;++i) {
          if(EdgeFlag[i]==0)  continue;
          tmd=v[i];
          bmd=Box[i];
          bhd=halfBox[i];
          while(tmd<-bhd)   tmd+=bmd;
          while(tmd>=bhd)   tmd-=bmd;
          v[i]=tmd;
        }
      }

      void allocate(const unsigned int Dim) { myError("Not Available"); }

      template <template <typename> class iVecType>
      void refer(const PeriodicBox<iVecType>& PB) {
        refer(PB,0U,PB.box().size());
      }

      template <template <typename> class iVecType>
      void refer(const PeriodicBox<iVecType>& PB, const unsigned int off,
                 const unsigned int size) {
        myError("Not Available");
      }

      Type& CanonicalForm() { return *this; }

      const Type& CanonicalForm() const { return *this; }

  };

  template <template <typename> class VecType>
  const unsigned int PeriodicBox<VecType>::TypeID=PeriodicBoxType;

  template <>
  void PeriodicBox<varVector>::allocate(const unsigned int Dim) {
    box().allocate(Dim);
    flag().allocate(Dim);
    hfbox().allocate(Dim);
  }

  template <>
  template <template <typename> class iVecType>
  void PeriodicBox<refVector>::refer(const PeriodicBox<iVecType>& PB,
                                     const unsigned int off,
                                     const unsigned int size) {
    box().refer(PB.box(),off,size);
    flag().refer(PB.flag(),off,size);
    hfbox().refer(PB.hfbox(),off,size);
  }

  template <template <typename> class VecType>
  void DisplacementFunc(const VectorBase<double>& va,
                        const VectorBase<double>& vb, VectorBase<double>& v,
                        const PeriodicBox<VecType>& PB) {
    DisplacementFunc(va,vb,v);
    PB.shift2main(v);
  }

}

#endif

