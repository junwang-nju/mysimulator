
#ifndef _Interaction_Method_H_
#define _Interaction_Method_H_

#include "ref-vector.h"
#include "var-vector.h"
#include "interaction-type.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  class InteractionMethod {

    public:

      typedef InteractionMethod<DistEvalMethod,GeomType>  Type;

      typedef refVector<double>   PropertyType;

      void (*EFuncVV)(const VectorBase<PropertyType>&,
                      const VectorBase<unsigned int>&,
                      const VectorBase<double>&,
                      DistEvalMethod<varVector>&, const GeomType<varVector>&,
                      double&);

      void (*GFuncVV)(const VectorBase<PropertyType>&,
                      const VectorBase<unsigned int>&,
                      const VectorBase<double>&,
                      DistEvalMethod<varVector>&, const GeomType<varVector>&,
                      VectorBase<PropertyType>&);

      void (*BFuncVV)(const VectorBase<PropertyType>&,
                      const VectorBase<unsigned int>&,
                      const VectorBase<double>&,
                      DistEvalMethod<varVector>&, const GeomType<varVector>&,
                      double&,VectorBase<PropertyType>&);

      void (*EFuncVR)(const VectorBase<PropertyType>&,
                      const VectorBase<unsigned int>&,
                      const VectorBase<double>&,
                      DistEvalMethod<varVector>&, const GeomType<refVector>&,
                      double&);

      void (*GFuncVR)(const VectorBase<PropertyType>&,
                      const VectorBase<unsigned int>&,
                      const VectorBase<double>&,
                      DistEvalMethod<varVector>&, const GeomType<refVector>&,
                      VectorBase<PropertyType>&);

      void (*BFuncVR)(const VectorBase<PropertyType>&,
                      const VectorBase<unsigned int>&,
                      const VectorBase<double>&,
                      DistEvalMethod<varVector>&, const GeomType<refVector>&,
                      double&,VectorBase<PropertyType>&);

      void (*EFuncRV)(const VectorBase<PropertyType>&,
                      const VectorBase<unsigned int>&,
                      const VectorBase<double>&,
                      DistEvalMethod<refVector>&, const GeomType<varVector>&,
                      double&);

      void (*GFuncRV)(const VectorBase<PropertyType>&,
                      const VectorBase<unsigned int>&,
                      const VectorBase<double>&,
                      DistEvalMethod<refVector>&, const GeomType<varVector>&,
                      VectorBase<PropertyType>&);

      void (*BFuncRV)(const VectorBase<PropertyType>&,
                      const VectorBase<unsigned int>&,
                      const VectorBase<double>&,
                      DistEvalMethod<refVector>&, const GeomType<varVector>&,
                      double&,VectorBase<PropertyType>&);

      void (*EFuncRR)(const VectorBase<PropertyType>&,
                      const VectorBase<unsigned int>&,
                      const VectorBase<double>&,
                      DistEvalMethod<refVector>&, const GeomType<refVector>&,
                      double&);

      void (*GFuncRR)(const VectorBase<PropertyType>&,
                      const VectorBase<unsigned int>&,
                      const VectorBase<double>&,
                      DistEvalMethod<refVector>&, const GeomType<refVector>&,
                      VectorBase<PropertyType>&);

      void (*BFuncRR)(const VectorBase<PropertyType>&,
                      const VectorBase<unsigned int>&,
                      const VectorBase<double>&,
                      DistEvalMethod<refVector>&, const GeomType<refVector>&,
                      double&,VectorBase<PropertyType>&);

      unsigned int iTag;

      InteractionMethod() : EFuncVV(NULL), GFuncVV(NULL), BFuncVV(NULL),
                            EFuncVR(NULL), GFuncVR(NULL), BFuncVR(NULL),
                            EFuncRV(NULL), GFuncRV(NULL), BFuncRV(NULL),
                            EFuncRR(NULL), GFuncRR(NULL), BFuncRR(NULL),
                            iTag(UnknownInteraction) {
        assert(DistEvalMethod<varVector>::IsDistanceEvalMethod);
        assert(GeomType<varVector>::IsGeometry);
      }

      InteractionMethod(const Type&) {
        myError("Cannot create from Interaction Method");
      }

      ~InteractionMethod() {}

      void clear() {
        EFuncVV=NULL;
        EFuncVR=NULL;
        EFuncRV=NULL;
        EFuncRR=NULL;
        GFuncVV=NULL;
        GFuncVR=NULL;
        GFuncRV=NULL;
        GFuncRR=NULL;
        BFuncVV=NULL;
        BFuncVR=NULL;
        BFuncRV=NULL;
        BFuncRR=NULL;
        iTag=UnknownInteraction;
      }

      Type& operator=(const Type& IM) {
        EFuncVV=IM.EFuncVV;
        EFuncVR=IM.EFuncVR;
        EFuncRV=IM.EFuncRV;
        EFuncRR=IM.EFuncRR;
        GFuncVV=IM.GFuncVV;
        GFuncVR=IM.GFuncVR;
        GFuncRV=IM.GFuncRV;
        GFuncRR=IM.GFuncRR;
        BFuncVV=IM.BFuncVV;
        BFuncVR=IM.BFuncVR;
        BFuncRV=IM.BFuncRV;
        BFuncRR=IM.BFuncRR;
        iTag=IM.iTag;
        return *this;
      }

      template <template <typename> class VecTypeD,
                template <typename> class VecTypeG>
      void EFunc(const VectorBase<PropertyType>& Coordinate,
                 const VectorBase<unsigned int>& Idx,
                 const VectorBase<double>& Param,
                 DistEvalMethod<VecTypeD>& DEval,
                 const GeomType<VecTypeG>& Geo, double& Energy) const {
        myError("Not Implemented");
      }

      void EFunc(const VectorBase<PropertyType>& Coordinate,
                 const VectorBase<unsigned int>& Idx,
                 const VectorBase<double>& Param,
                 DistEvalMethod<varVector>& DEval,
                 const GeomType<varVector>& Geo, double& Energy) const {
        EFuncVV(Coordinate,Idx,Param,DEval,Geo,Energy);
      }

      void EFunc(const VectorBase<PropertyType>& Coordinate,
                 const VectorBase<unsigned int>& Idx,
                 const VectorBase<double>& Param,
                 DistEvalMethod<refVector>& DEval,
                 const GeomType<varVector>& Geo, double& Energy) const {
        EFuncRV(Coordinate,Idx,Param,DEval,Geo,Energy);
      }

      void EFunc(const VectorBase<PropertyType>& Coordinate,
                 const VectorBase<unsigned int>& Idx,
                 const VectorBase<double>& Param,
                 DistEvalMethod<varVector>& DEval,
                 const GeomType<refVector>& Geo, double& Energy) const {
        EFuncVR(Coordinate,Idx,Param,DEval,Geo,Energy);
      }

      void EFunc(const VectorBase<PropertyType>& Coordinate,
                 const VectorBase<unsigned int>& Idx,
                 const VectorBase<double>& Param,
                 DistEvalMethod<refVector>& DEval,
                 const GeomType<refVector>& Geo, double& Energy) const {
        EFuncRR(Coordinate,Idx,Param,DEval,Geo,Energy);
      }

      template <template <typename> class VecTypeD,
                template <typename> class VecTypeG>
      void GFunc(const VectorBase<PropertyType>& Coordinate,
                 const VectorBase<unsigned int>& Idx,
                 const VectorBase<double>& Param,
                 DistEvalMethod<VecTypeD>& DEval,
                 const GeomType<VecTypeG>& Geo,
                 VectorBase<PropertyType>& Gradient) const {
        myError("Not Implemented");
      }

      void GFunc(const VectorBase<PropertyType>& Coordinate,
                 const VectorBase<unsigned int>& Idx,
                 const VectorBase<double>& Param,
                 DistEvalMethod<varVector>& DEval,
                 const GeomType<varVector>& Geo,
                 VectorBase<PropertyType>& Gradient) const {
        GFuncVV(Coordinate,Idx,Param,DEval,Geo,Gradient);
      }

      void GFunc(const VectorBase<PropertyType>& Coordinate,
                 const VectorBase<unsigned int>& Idx,
                 const VectorBase<double>& Param,
                 DistEvalMethod<refVector>& DEval,
                 const GeomType<varVector>& Geo,
                 VectorBase<PropertyType>& Gradient) const {
        GFuncRV(Coordinate,Idx,Param,DEval,Geo,Gradient);
      }

      void GFunc(const VectorBase<PropertyType>& Coordinate,
                 const VectorBase<unsigned int>& Idx,
                 const VectorBase<double>& Param,
                 DistEvalMethod<varVector>& DEval,
                 const GeomType<refVector>& Geo,
                 VectorBase<PropertyType>& Gradient) const {
        GFuncVR(Coordinate,Idx,Param,DEval,Geo,Gradient);
      }

      void GFunc(const VectorBase<PropertyType>& Coordinate,
                 const VectorBase<unsigned int>& Idx,
                 const VectorBase<double>& Param,
                 DistEvalMethod<refVector>& DEval,
                 const GeomType<refVector>& Geo,
                 VectorBase<PropertyType>& Gradient) const {
        GFuncRR(Coordinate,Idx,Param,DEval,Geo,Gradient);
      }

      template <template <typename> class VecTypeD,
                template <typename> class VecTypeG>
      void BFunc(const VectorBase<PropertyType>& Coordinate,
                 const VectorBase<unsigned int>& Idx,
                 const VectorBase<double>& Param,
                 DistEvalMethod<VecTypeD>& DEval,
                 const GeomType<VecTypeG>& Geo, double& Energy,
                 VectorBase<PropertyType>& Gradient) const {
        myError("Not Implemented");
      }

      void BFunc(const VectorBase<PropertyType>& Coordinate,
                 const VectorBase<unsigned int>& Idx,
                 const VectorBase<double>& Param,
                 DistEvalMethod<varVector>& DEval,
                 const GeomType<varVector>& Geo, double& Energy,
                 VectorBase<PropertyType>& Gradient) const {
        BFuncVV(Coordinate,Idx,Param,DEval,Geo,Energy,Gradient);
      }

      void BFunc(const VectorBase<PropertyType>& Coordinate,
                 const VectorBase<unsigned int>& Idx,
                 const VectorBase<double>& Param,
                 DistEvalMethod<refVector>& DEval,
                 const GeomType<varVector>& Geo, double& Energy,
                 VectorBase<PropertyType>& Gradient) const {
        BFuncRV(Coordinate,Idx,Param,DEval,Geo,Energy,Gradient);
      }

      void BFunc(const VectorBase<PropertyType>& Coordinate,
                 const VectorBase<unsigned int>& Idx,
                 const VectorBase<double>& Param,
                 DistEvalMethod<varVector>& DEval,
                 const GeomType<refVector>& Geo, double& Energy,
                 VectorBase<PropertyType>& Gradient) const {
        BFuncVR(Coordinate,Idx,Param,DEval,Geo,Energy,Gradient);
      }

      void BFunc(const VectorBase<PropertyType>& Coordinate,
                 const VectorBase<unsigned int>& Idx,
                 const VectorBase<double>& Param,
                 DistEvalMethod<refVector>& DEval,
                 const GeomType<refVector>& Geo, double& Energy,
                 VectorBase<PropertyType>& Gradient) const {
        BFuncRR(Coordinate,Idx,Param,DEval,Geo,Energy,Gradient);
      }

      const unsigned int InteractionTag() const { return iTag; }

  };

}

#endif

