
#ifndef _Pair_Storage_Base_H_
#define _Pair_Storage_Base_H_

#include "var-matrix-triangle.h"

namespace std {

  template <typename T, template <typename> class TriangMat=varTriangMatrix>
  class PairStorage {

    public:

      struct Item {
        T Element;
        unsigned int Status;
        Item() : Status(0U) {}
        Item(const Item& Im) { myError("Cannot create from Item"); }
        Item& operator=(const Item& Im) {
          Element=Im.Element;
          Status=Im.Status;
          return *this;
        }
      };

    protected:
      unsigned int GStatus;
      TriangMat<Item> Data;

    public:

      typedef PairStorage<T,TriangMat>  Type;

      PairStorage() : GStatus(0U), Data() {}

      PairStorage(const unsigned int NUnit)
        : GStatus(0U), Data(NUnit,COrder,NoTranspose,UpperPart,true,false) {}

      PairStorage(const Type& PS) {
        myError("Cannot create from pair storage");
      }

      Type& operator=(const Type& PS) {
        GStatus=PS.GStatus;
        Data=PS.Data;
      }

      void allocate(const unsigned int NUnit) {
        Data.allocate(NUnit,COrder,NoTranspose,UpperPart,true,false);
        GStatus=1U;
      }

      const unsigned int NumUnits() const { return Data.Dimension(); }

      Item& operator()(const unsigned int I, const unsigned int J) {
        return Data(I,J);
      }

      const Item& operator()(const unsigned int I, const unsigned int J) const{
        return Data(I,J);
      }

      void Inc() { ++GStatus; }

      void Inc(const unsigned int idx) {
        unsigned int n=NumUnits();
        for(unsigned int i=0;i<n;++i) {
          if(i==idx)  continue;
          Data(i,I).Status=GStatus-1;
        }
      }

      void Inc(const unsigned int idxI, const unsigned int idxJ) {
        Data(idxI,idxJ).Status=GStatus-1;
      }

  };
}

#endif

