
#ifndef _Pair_Storage_H_
#define _Pair_Storage_H_

#include "pair-storage-item.h"
#include "var-matrix-triangle.h"
#include "ref-matrix-triangle.h"

namespace std {

  template <typename T, template <typename> class TriangMat,
                        template <typename> class VecType>
  class PairStorage {

    public:

      typedef PairStorage<T,TriangMat,VecType>  Type;

      typedef PairItem<T>   ItemType;

    protected:

      VecType<unsigned int> GStatus;
      typename TriangMat<ItemType>::Type Data;

    public:

      PairStorage() : GStatus(), Data() {
        assert(VecType<unsigned int>::IsVector);
        assert(TriangMat<ItemType>::IsTriangleMatrix);
      }

      PairStorage(const unsigned int N) : GStatus(), Data() { allocate(N); }

      PairStorage(const Type& PS) {
        myError("Cannot create from pair storage");
      }

      ~PairStorage() { clear(); }

      void clear() {
        GStatus.clear();
        Data.clear();
      }

      Type& operator=(const Type& PS) {
        GStatus=PS.GStatus;
        Data=PS.Data;
        return *this;
      }

      template <template <typename> class iTriangMat,
                template <typename> class iVecType>
      Type& operator=(const PairStorage<T,iTriangMat,iVecType>& PS) {
        GStatus=PS.GStatusVec();
        Data=PS.DataMat();
        return *this;
      }

      const unsigned int NumUnits() const { return Data.Dimension(); }

      const unsigned int& GlobalStatus() const { return GStatus[0]; }

      VecType<unsigned int>& GStatusVec() { return GStatus; }

      typename TriangMat<ItemType>::Type& DataMat() { return Data; }

      const VecType<unsigned int>& GStatusVec() const { return GStatus; }

      const typename TriangMat<ItemType>::Type& DataMat() const{ return Data; }

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

    protected:

      struct AllocateOp {
        template <template <typename> class iTriangMat,
                  template <typename> class iVecType>
        void operator()(const unsigned int N,
                        PairStorage<T,iTriangMat,iVecType>& Self) {
          myError("Not Available");
        }
        void operator()(const unsigned int N,
                        PairStorage<T,varMatrixTriangle,varVector>& Self) {
          Self.DataMat().allocate(N,COrder,NoTranspose,UpperPart,true,false);
          Self.GStatusVec().allocate(1);
          Self.GStatusVec()=1U;
        }
      };

      struct ReferOp {
        template <template <typename> class iTriangMat,
                  template <typename> class iVecType,
                  template <typename> class rTriangMat,
                  template <typename> class rVecType>
        void operator()(const PairStorage<T,iTriangMat,iVecType>& PS,
                        PairStorage<T,rTriangMat,rVecType>& Self) {
          myError("Not Available");
        }
        template <template <typename> class iTriangMat,
                  template <typename> class iVecType>
        void operator()(const PairStorage<T,iTriangMat,iVecType>& PS,
                        PairStorage<T,refMatrixTriangle,refVector>& Self) {
          Self.GStatusVec().refer(PS.GStatusVec());
          Self.DataMat().refer(PS.DataMat());
        } 
      };

      AllocateOp runAllocateOp;

      ReferOp runReferOp;

    public:

      void allocate(const unsigned int N) {
        runAllocateOp(N,*this);
      }

      template <template <typename> class iTriangMat,
                template <typename> class iVecType>
      void refer(const PairStorage<T,iTriangMat,iVecType>& PS) {
        runReferOp(PS,*this);
      }

      Type& CanonicalForm() { return *this; }

      const Type& CanonicalForm() const { return *this; }

  };

}

#endif

