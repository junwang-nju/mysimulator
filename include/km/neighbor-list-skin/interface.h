
#ifndef _Neighbor_List_Skin_Interface_H_
#define _Neighbor_List_Skin_Interface_H_

#include "array2d-numeric/interface.h"
#include "distance/calc.h"

namespace mysimulator {

  template <typename T> class NeighborListSkin;
  template <typename T> void Clear(NeighborListSkin<T>&);

  template <typename T>
  class NeighborListSkin {

    public:

      typedef NeighborListSkin<T>   Type;
      friend void Clear<T>(NeighborListSkin<T>&);

      NeighborListSkin() : _SkinR(0), _HfSkinRSQ(0), _snapshot() {}
      ~NeighborListSkin() { Clear(*this); }

      bool IsValid() const { return (_SkinR>0) && _snapshot.IsValid(); }

      template <typename T1>
      void Imprint(const Array2DNumeric<T1>& X) {
        _snapshot.ImprintStructure(X);
        _Dsp.Allocate(X[0].Size());
      }

      template <typename T1>
      void SetSkinRadius(const T1& SR) {
        _Copy(_SkinR,SR);
        _HfSkinRSQ=_SkinR*_SkinR*0.25;
      }
      template <typename GT>
      bool Check(const Array2DNumeric<T>& X, const GT& Geo) {
        assert(IsSameSize(X,_snapshot));
        bool check=false;
        const unsigned int n=X.Size();
        for(unsigned int i=0;i<n;++i)
          if(DistanceSQ(_Dsp,X[i],_snapshot[i],Geo)>_HfSkinRSQ) {
            check=true;
            break;
          }
        return check;
      }

      void Update(const Array2DNumeric<T>& X) { _snapshot.Copy(X); }

    protected:

      T _SkinR;
      T _HfSkinRSQ;
      Array2DNumeric<T> _snapshot;

      void ClearTMP() { Clear(_Dsp); }

    private:

      ArrayNumeric<T> _Dsp;

      NeighborListSkin(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(NeighborListSkin<T>& K) {
    K.ClearTMP();
    Clear(K._snapshot);
    K._HfSkinRSQ=0;
    K._SkinR=0;
  }

}

#endif

