
#ifndef _Fixed_Vector_H_
#define _Fixed_Vector_H_

#include "vector-base.h"

namespace std {

  template <typename T, unsigned int ND>
  class fixVector : public VectorBase<T> {

    private:

      T runData[ND];

    public:

      typedef   fixVector<T,ND>   Type;

      typedef   VectorBase<T>     ParentType;

      fixVector() : ParentType() {
        this->data()=runData;
        this->SetSize(ND);
      }

      fixVector(const Type&) { myError("Cannot create from fixed vector"); }

      virtual ~fixVector() {}

      Type& operator=(const Type& V) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(V));
        return *this;
      }

      template <typename iType>
      Type& operator=(const iType& V) {
        static_cast<ParentType*>(this)->operator=(V);
        return *this;
      }

      void clear() {}

      virtual const char* type() const { return "Fixed Vector"; }

  };

}

#endif

