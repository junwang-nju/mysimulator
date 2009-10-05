
#ifndef _Distance_Evaluation_H_
#define _Distance_Evaluation_H_

#include "property.h"
#include "geometry.h"
#include "vector-op.h"
#include "distance-storage.h"

namespace std {

  template <uint N>
  class Displacement : public fixVector<double,N> {

    public:

      typedef Displacement          Type;
      
      typedef fixVector<double,N>   ParentType;
      
      Displacement() : ParentType() {}
      
      Displacement(const Type& Dsp) {
        myError("copier for Displacement is disabled!");
      }
      
      Type& operator=(const Type& Dsp) {
        static_cast<ParentType*>(this)->operator=(Dsp);
        return *this;
      }
      
      fixVector<double,N>& operator()() {
        return *static_cast<ParentType*>(this);
      }

      template <typename vTypeA, typename vTypeB>
      fixVector<double,N>& operator()(const vTypeA& va, const vTypeB& vb) {
        assert(isVector<vTypeA>()&&isVector<vTypeB>());
        assert(va.size()==vb.size());
        assert(this->size()>=va.size());
        static_cast<ParentType*>(this)->operator=(va);
        this->shift(-1.,vb);
        return operator()();
      }

      fixVector<double,N>& operator()(const Property& pa, const Property& pb) {
        return operator()(pa.Coordinate,pb.Coordinate);
      }

      template <typename vTypeA, typename vTypeB>
      fixVector<double,N>& operator()(const vTypeA& va, const vTypeB& vb,
                                      const FreeSpace& FS) {
        return operator()(va,vb);
      }

      template <typename GeomType>
      fixVector<double,N>& operator()(const Property& pa, const Property& pb,
                                      const GeomType& Geo) {
        return operator()(pa.Coordinate,pb.Coordinate,Geo);
      }

  };

  template <uint N>
  class DistanceSquare : public Displacement<N> {

    public:
    
      typedef DistanceSquare<N>   Type;
    
      typedef Displacement<N>     ParentType;
    
      DistanceSquare() : ParentType() {}
      
      DistanceSquare(const Type& DSq) {
        myError("copier for DistanceSquare is disabled!");
      }

      Type& operator=(const Type& DSq) {
        static_cast<ParentType*>(this)->operator=(DSq);
        return *this;
      }

      ParentType& Direction() { return *static_cast<ParentType*>(this); }

      const ParentType& Direction() const {
        return *static_cast<const ParentType*>(this);
      }

      template <typename vTypeA, typename vTypeB>
      double operator()(const vTypeA& va, const vTypeB& vb) {
        return normSQ(Direction()(va,vb)); 
      }

      double operator()(const Property& pa, const Property& pb) {
        return operator()(pa.Coordinate,pb.Coordinate);
      }

      template <typename vTypeA, typename vTypeB, typename GeomType>
      double operator()(const vTypeA& va, const vTypeB& vb,
                        const GeomType& Geo) {
        return normSQ(Direction()(va,vb,Geo));
      }

      template <typename GeomType>
      double operator()(const Property& pa, const Property& pb,
                        const GeomType& Geo) {
        return operator()(pa.Coordinate,pb.Coordinate,Geo);
      }

  };

  template <uint N>
  class DistanceEvalDirect {
  
    private:
    
      DistanceSquare<N> GetDistSQ;
      
      double nowDistSQ;
      
      fixVector<double,N> nowDisp;
      
    public:
    
      DistanceEvalDirect() : GetDistSQ(), nowDistSQ(0.), nowDisp() {}
      
      DistanceEvalDirect(const DistanceEvalDirect<N>& DEval) {
        myError("copier for Direct DistanceEval is disabled!");
      }
      
      const double& DistanceSQ() { return nowDistSQ; }
      
      const fixVector<double,N>& DisplaceVector() { return nowDisp; }
      
      template <typename GeomType>
      double operator()(const Property& pa, const Property& pb,
                        const GeomType& Geo) {
        nowDistSQ=GetDistSQ(pa,pb,Geo);
        return nowDistSQ;
      }

      template <typename GeomType>
      double operator()(const Property& pa, const Property& pb,
                        const GeomType& Geo, const char) {
        nowDistSQ=GetDistSQ(pa,pb,Geo);
        nowDisp=GetDistSQ.Direction()();
        return nowDistSQ;
      }
      
      void Update() {}

  };

  template <uint N>
  class DistanceEvalwStorage {
  
    private:
    
      DistanceSquare<N> GetDistSQ;
    
      double nowDistSQ;
      
      fixVector<double,N> nowDisp;
      
      DistanceSqStorage DistSQPack;
      
    public:
    
      DistanceEvalwStorage()
        : GetDistSQ(), nowDistSQ(0.), nowDisp(), DistSQPack() {
      }
      
      DistanceEvalwStorage(const DistanceEvalwStorage<N>& DEval) {
        myError("copier for storage-base DistanceEval is disabled!");
      }
      
      const double& DistanceSQ() { return nowDistSQ; }
      
      const fixVector<double,N>& DisplaceVector() { return nowDisp; }
      
      template <typename GeomType>
      double operator()(const Property& pa, const Property& pb,
                        const GeomType& Geo) {
        DistanceSqStorage::Item &DItem=DistSQPack(pa.Index,pb.Index);
        if(DItem.Status!=DistSQPack.GStatus) {
          DItem.DistanceSQ=GetDistSQ(pa,pb,Geo);
          DItem.Status=DistSQPack.GStatus;
        } 
        nowDistSQ=DItem.DistanceSQ;
        return nowDistSQ;
      }

      template <typename GeomType>
      double operator()(const Property& pa, const Property& pb,
                        const GeomType& Geo, const char) {
        DistanceSqStorage::Item &DItem=DistSQPack(pa.Index,pb.Index);
        if(DItem.Status!=DistSQPack.GStatus) {
          DItem.DistanceSQ=GetDistSQ(pa,pb,Geo);
          DItem.Status=DistSQPack.GStatus;
        } else
          GetDistSQ.Direction()(pa,pb,Geo); 
        nowDistSQ=DItem.DistanceSQ;
        nowDisp=GetDistSQ.Direction()();
        return nowDistSQ;
      }
      
      void Update() { DistSQPack.Inc(); }

      void allocate_storage(const uint& NS) { DistSQPack.allocate(NS); }
      
  };

}

#endif
