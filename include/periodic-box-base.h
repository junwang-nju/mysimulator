
#ifndef _Periodi_Box_Base_H_
#define _Periodi_Box_Base_H_

#include "direct-displacement.h"
#include "geometry-id.h"

namespace std {

  enum PeriodicityState {
    PeriodicON=1,
    PeriodicOFF=0
  };

  template <template <typename> class VecType>
  class PeriodicBoxBase {

    protected:

      VecType<double> Box;

      VecType<unsigned int> EdgeFlag;

      VecType<double> halfBox;

    public:

      static const unsigned int TypeID;

      typedef PeriodicBoxBase<VecType>  Type;

      PeriodicBoxBase() : Box(), EdgeFlag(), halfBox() {}

      PeriodicBoxBase(const Type& PBB) {
        myError("Cannot create from periodic box base");
      }

      ~PeriodicBoxBase() { clear(); }

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

      const VecType<double>& box() const { return Box; }

      VecType<double>& runBox() { return Box; }

      const VecType<double>& hfbox() const { return halfBox; }

      VecType<double>& runHfBox() { return halfBox; }

      const VecType<unsigned int>& flag() const { return EdgeFlag; }

      VecType<unsigned int>& runFlag() { return EdgeFlag; }

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

  };

  template <template <typename> class VecType>
  const unsigned int PeriodicBoxBase<VecType>::TypeID=PeriodicBoxType;

  template <template <typename> class VecType>
  void DisplacementFunc(const VectorBase<double>& va,
                        const VectorBase<double>& vb, VectorBase<double>& v,
                        const PeriodicBoxBase<VecType>& PB) {
    DirectDisplacement(va,vb,v);
    PB.shift2main(v);
  }

}

#endif

