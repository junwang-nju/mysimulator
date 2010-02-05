
#ifndef _Variable_Vector_H_
#define _Variable_Vector_H_

#include "object-with-storage.h"
#include "vector-base.h"
#include "memory.h"

namespace std {
  template <typename T>
  class varVector : public ObjectWStorage<VectorBase<T> > {
    public:
      typedef T DataType;
      typedef varVector<T>  Type;
      typedef ObjectWStorage<VectorBase<T> >  ParentType;
      varVector() : ParentType() { }
      varVector(const unsigned int N) : ParentType() { allocate(N); }
      varVector(const Type& V) {
        myError("Cannot create from variable vector");
      }
      virtual ~varVector() { safe_delete(this->data()); }
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
      void clear();
      void allocate(const unsigned int N);
      virtual const char* type() const;
  };
}

#endif

