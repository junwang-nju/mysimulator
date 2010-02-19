
#ifndef _Variable_Distance_Square_H_
#define _Variable_Distance_Square_H_

#include "distance-square-base.h"
#include "object-with-storage.h"
#include "var-vector.h"

namespace std {

  class varDistanceSq : public ObjectWStorage<DistanceSqBase<varVector> > {

    public:

      typedef varDistanceSq   Type;

      typedef ObjectWStorage<DistanceSqBase<varVector> >   ParentType;

      varDistanceSq() : ParentType() {}

      varDistanceSq(const Type& vD) {
        myError("Cannot create from variable distance-square functor");
      }

      ~varDistanceSq() {}

      Type& operator=(const Type& vD) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(vD));
        return *this;
      }

      void allocate(const unsigned int Dim) { displacement().allocate(Dim); }

  };

}

#endif

