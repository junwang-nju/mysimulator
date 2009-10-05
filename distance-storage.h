
#ifndef _Distance_Storage_H_
#define _Distance_Storage_H_

#include "var-vector.h"

namespace std {

  class DistanceSqStorage {
  
    public:

      struct Item {

          double DistanceSQ;
          
          uint Status;

          Item() : DistanceSQ(0.), Status(0U) {}
          
          Item(const Item& Itm) { myError("Copier for Item is disabled!"); }
          
          Item& operator=(const Item& Itm) {
            DistanceSQ=Itm.DistanceSQ;
            Status=Itm.Status;
            return *this;
          }

      };

      uint GStatus;
    
    private:
    
      varVector<Item> Data;
      
      varVector<Item*> DLevel;
      
      void SetLevel(const uint& N) {
        assert(Data.data()!=NULL);
        DLevel[0]=Data.data();
        for(uint i=1,j=N-1;i<N;++i,--j) DLevel[i]=DLevel[i-1]+j;
      }       

    public:
    
      DistanceSqStorage() : GStatus(0),Data(), DLevel() {}
      
      DistanceSqStorage(const uint& N)
        : GStatus(1), Data((N*(N-1))/2), DLevel(N) {
        SetLevel(N);
      }

      DistanceSqStorage(const DistanceSqStorage& DSS) {
        myError("copier is disabled!");
      }
      
      DistanceSqStorage& operator=(const DistanceSqStorage& DSS) {
        Data=DSS.Data;
        GStatus=DSS.GStatus;
        return *this;
      }

      DistanceSqStorage& allocate(const uint& N) {
        uint n=(N*(N-1))/2;
        Data.allocate(n);
        DLevel.allocate(N);
        SetLevel(N);
        GStatus=1;
        return *this;
      }

      DistanceSqStorage& allocate(const DistanceSqStorage& DSS) {
        return allocate(DSS.DLevel.size());
      }

      DistanceSqStorage& Duplicate(const DistanceSqStorage& DSS) {
        return allocate(DSS).operator=(DSS);
      }

      Item& operator()(const uint I, const uint J) {
        assert(I!=J);
        uint rI=I,rJ=J;
        if(rI>rJ) { rI=J; rJ=I; }
        return *(DLevel[rI]+rJ-rI-1);
      }

      const Item& operator()(const uint I, const uint J) const {
        assert(I!=J);
        uint rI=I,rJ=J;
        if(rI>rJ) { rI=J; rJ=I; }
        return *(DLevel[rI]+rJ-rI-1);
      }

      void Inc() { ++GStatus; }
      
      void Inc(const uint& I) {
        uint n=DLevel.size();
        for(uint i=0;i<n;++i) {
          if(i==I)  continue;
          operator()(i,I).Status=GStatus-1;
        }
      }

      void Inc(const uint& I, const uint& J) {
        operator()(I,J).Status=GStatus-1;
      }

      const bool isUpdated(const uint& I, const uint& J) {
        return operator()(I,J).Status==GStatus;
      }

      void Update(const uint& I, const uint& J, const double& dsq) {
        Item& Itm=operator()(I,J);
        Itm.DistanceSQ=dsq;
        Itm.Status=GStatus;
      }

  };

}

#endif
