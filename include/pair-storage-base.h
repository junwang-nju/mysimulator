
#ifndef _Pair_Storage_Base_H_
#define _Pair_Storage_Base_H_

#include "pair-storage-item.h"
#include <cassert>

namespace std {

  template <typename T, template <typename> class TriangMat,
                        template <typename> class VecType>
  class PairStorageBase {

    public:

      typedef PairStorageBase<T,TriangMat,VecType>  Type;

      typedef PairItem<T>   ItemType;

    protected:

      VecType<unsigned int> GStatus;
      TriangMat<ItemType> Data;

    public:

      PairStorageBase() : GStatus(), Data() {
        assert(VecType<unsigned int>::IsVector);
        assert(TriangMat<ItemType>::IsTriangleMatrix);
      }

      PairStorageBase(const Type& PS) {
        myError("Cannot create from pair storage");
      }

      ~PairStorageBase() { clear(); }

      void clear() {
        GStatus.clear();
        Data.clear();
      }

      Type& operator=(const Type& PS) {
        GStatus=PS.GStatus;
        Data=PS.Data;
        return *this;
      }

      const unsigned int NumUnits() const { return Data.Dimension(); }

      const unsigned int& GlobalStatus() const { return GStatus[0]; }

    protected:

      VecType<unsigned int>& GStatusVec() { return GStatus; }

      TriangMat<ItemType>& DataMat() { return Data; }

    public:

      const ItemType& operator()(const unsigned int I,const unsigned int J)
          const {
        return Data(I,J);
      }

      void Inc() { ++GStatus[0]; }

      void Inc(const unsigned int idx) {
        unsigned int n=NumUnits();
        for(unsigned int i=0;i<n;++i) {
          if(i==idx)  continue;
          Data(i,idx).Status=GStatus[0]-1;
        }
      }

      void Inc(const unsigned int idxI, const unsigned int idxJ) {
        Data(idxI,idxJ).Status=GStatus[0]-1;
      }

      const bool IsUpdated(const unsigned int I, const unsigned int J) {
        return operator()(I,J).Status==GStatus[0];
      }

      void Update(const unsigned int I, const unsigned int J,
                  const T& iItem) {
        ItemType& rItem=Data(I,J);
        rItem.Element=iItem;
        rItem.Status=GStatus[0];
      }

  };

}

#endif

