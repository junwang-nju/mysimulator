
#ifndef _Accelerator_NeighborList_Interface_H_
#define _Accelerator_NeighborList_Interface_H_

#include "array/1d/interface.h"
#include "array/2d/content/interface.h"
#include "distance/calc.h"

#define _RENEW(typeID,typeX) \
  template <typename GeomType> \
  unsigned int renew(typeID& id, const typeX& X, const GeomType& Geo) { \
    _renew(id,X,Geo); \
  }

namespace mysimulator {

  template <typename T>
  struct NeighborList {

    public:

      typedef NeighborList<T>   Type;

      T CutRadius;
      T InteractionCutRadius;
      T BufferRadius;
      T UpdateTime;
      T CutRadiusSQ;
      Array1D<T>  tmpVec;

      NeighborList()
        : CutRadius(0), InteractionCutRadius(0), BufferRadius(0),
          UpdateTime(0), tmpVec() {}
      ~NeighborList() { clearData(); }

      void clearData() {
        CutRadius=0; InteractionCutRadius=0; BufferRadius=0; UpdateTime=0;
        release(tmpVec);
      }
      bool isvalid() const {
        return IsValid(tmpVec)&&(CutRadius>RelativeDelta<T>());
      }

      _RENEW(Array1DContent<Array1D<int> >,Array2DContent<T>)
      _RENEW(Array1DContent<Array1D<int> >,Array1DContent<Array1D<T> >)
      _RENEW(Array2DContent<int>,Array2DContent<T>)
      _RENEW(Array2DContent<int>,Array1DContent<Array1D<T> >)

    private:

      NeighborList(const Type&) {}
      Type& operator=(const Type&) { return *this; }

      template <typename IDType, typename PosType, typename GeomType>
      unsigned int _renew(IDType& id, const PosType& X, const GeomType& Geo) {
        assert(IsValid(X)&&IsValid(id)&&IsValid(Geo));
        assert(tmpVec.size>=X[0].size);
        T dsq;
        unsigned int n=0;
        for(int i=id.last;i>=static_cast<int>(n);) {
          dsq=DistanceSQ(tV,X[id[i][0]],X[id[i][1]],Geo);
          if(dsq<CutRadiusSQ) {
            if(n!=i)  exchange(id[n],id[i]);
            ++n;
          } else --i;
        }
        return n;
      }

  };

  template <typename T>
  void release(NeighborList<T>& L) { L.clearData(); }

  template <typename T>
  bool IsValid(const NeighborList<T>& L) { return L.isvalid(); }

}

#undef _RENEW

#endif

