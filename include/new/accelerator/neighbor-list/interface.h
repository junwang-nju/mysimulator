
#ifndef _Accelerator_NeighborList_Interface_H_
#define _Accelerator_NeighborList_Interface_H_

#include "array/1d/interface.h"
#include "array/2d/content/interface.h"
#include "distance/calc.h"

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

      NeighborList()
        : CutRadius(0), InteractionCutRadius(0), BufferRadius(0),
          UpdateTime(0) {}
      ~NeighborList() { clearData(); }

      void clearData() {
        CutRadius=0; InteractionCutRadius=0; BufferRadius=0; UpdateTime=0;
      }
      bool isvalid() const { return true; }

      template <typename GeomType>
      unsigned int renew(Array1DContent<Array1D<unsigned int> >& id,
                         Array2DContent<T>& X, const GeomType& Geo) {
        Array1D<T> tV;
        imprint(tV,X[0]);
        T dsq;
        unsigned int n=0;
        for(unsigned int i=id.last;i>=id.first;--i) {
          dsq=DistanceSQ(tV,X[id[i][0]],X[id[i][1]],Geo);
          if(dsq<CutRadiusSQ) {
            if(n!=i)  exchange(id[n],id[i]);
            ++n;
          }
          
        }
      }

    private:

      NeighborList(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void release(NeighborList<T>& L) { L.clearData(); }

  template <typename T>
  bool IsValid(const NeighborList<T>& L) { return L.isvalid(); }

}

#endif

