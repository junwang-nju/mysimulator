
#ifndef _Reference_Vector_H_
#define _Reference_Vector_H_

#include "ref-object.h"
#include "vector-base.h"

namespace std {
  template <typename T>
  class refVector : public refObject<VectorBase<T>,VectorBase<T> > {
    public:
      typedef T   DataType;
      typedef refVector<T>  Type;
      typedef refObject<VectorBase<T>,VectorBase<T> > ParentType;
      refVector() : ParentType() {
        this->SetSwapFlag(true);
        this->RefInfo().content()=static_cast<void*>(this);
      }
      refVector(const Type& V) {
        myError("Cannot create from reference vector");
      }
      virtual ~refVector() {}
      Type& operator=(const Type& V) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(V));
        return *this;
      }
      template <typename inputT>
      Type& operator=(const inputT& V) {
        static_cast<ParentType*>(this)->operator=(V);
        return *this;
      }
      virtual void refer(Type& V);
      virtual void refer(ObjectWStorage<VectorBase<T> >& V);
      void refer(Type& V, const unsigned int off, const unsigned int sz);
      void refer(ObjectWStorage<VectorBase<T> >& V,
                 const unsigned int off, const unsigned int sz);
      virtual const char* type() const;
  };
}

#endif

