
#ifndef _Fixed_Distance_Square_H_
#define _Fixed_Distance_Square_H_

#include "distance-square-base.h"
#include "object-with-storage.h"
#include "fix-vector.h"
#include "ref-vector.h"

namespace std {

  template <unsigned int Dim>
  class fixDistanceSq : public ObjectWStorage<DistanceSqBase<refVector> > {

    public:

      typedef fixDistanceSq<Dim>  Type;

      typedef ObjectWStorage<DistanceSqBase<refVector> >  ParentType;

    protected:

      fixVector<double,Dim> DspData;

    public:

      fixDistanceSq() : ParentType() { displacement().refer(DspData); }

      fixDistanceSq(const Type& fD) {
        myError("Cannot create from fixed distance-square functor");
      }

      ~fixDistanceSq() {}

      Type& operator=(const Type& fD) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(fD));
        return *this;
      }

  };

}

#endif

