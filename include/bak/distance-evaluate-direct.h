
#ifndef _Distance_Evaluate_Direct_H_
#define _Distance_Evaluate_Direct_H_

#include "distance-evaluate-base.h"
#include "distance-displacement-calc.h"
#include "var-vector.h"
#include "ref-vector.h"

namespace std {

  template <template <typename> class VecType>
  class DistanceEvalDirect : public DistanceEvalBase<VecType> {

    public:

      typedef DistanceEvalDirect<VecType>   Type;

      typedef DistanceEvalBase<VecType>   ParentType;

      static const unsigned int DistanceEvalMethod;

      DistanceEvalDirect() : ParentType() {}

      DistanceEvalDirect(const unsigned int D) : ParentType() { allocate(D); }

      DistanceEvalDirect(const Type&) {
        myError("Cannot create from Direct Distance Evaluate");
      }

      ~DistanceEvalDirect() {}

      Type& operator=(const Type& DEDB) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(DEDB));
        return *this;
      }

      template <template <typename> class iVecType>
      Type& operator=(const DistanceEvalDirect<iVecType>& DEDB) {
        static_cast<ParentType*>(this)->operator=(DEDB);
        return *this;
      }

      template <typename GeomType>
      void Evaluate(const VectorBase<double>& va, const VectorBase<double>& vb,
                    const unsigned int aIdx, const unsigned int bIdx,
                    const GeomType& Geo) {
        DistanceDisplacementFunc(va,vb,this->Displacement(),
                                 this->DistanceSQVec()[0],Geo);
      }

      virtual void update() {}

      void allocate(const unsigned int Dim) { myError("Not Available"); }

      template <template <typename> class iVecType>
      void refer(const DistanceEvalDirect<iVecType>& DED) {
        myError("Not Available");
      }

      Type& CanonicalForm() { return *this; }

      const Type& CanonicalForm() const { return *this; }

  };

  template <template <typename> class VecType>
  const unsigned int
  DistanceEvalDirect<VecType>::DistanceEvalMethod=1;

  template <>
  void DistanceEvalDirect<varVector>::allocate(const unsigned int Dim) {
    static_cast<ParentType*>(this)->DistanceSQVec().allocate(1);
    static_cast<ParentType*>(this)->Displacement().allocate(Dim);
  }

  template <>
  template <template <typename> class iVecType>
  void DistanceEvalDirect<refVector>::refer(
      const DistanceEvalDirect<iVecType>& DED) {
    static_cast<ParentType*>(this)->DistanceSQVec().refer(
        DED.DistanceSQVec());
    static_cast<ParentType*>(this)->Displacement().refer(
        DED.Displacement());
  }
        
}

#endif

