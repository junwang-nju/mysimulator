
#ifndef _Variable_Vector_H_
#define _Variable_Vector_H_

#include "referable-vector.h"

namespace std {
  template <typename T>
  class varVector : public referableVector<T> {
    public:
      typedef T DataType;
      typedef varVector<T>    Type;
      typedef referableVector<T>  ParentType;
      varVector() : ParentType() { this->SetSwapFlag(true); }
      varVector(const unsigned int& N) : ParentType() {
        this->SetSwapFlag(true);
        allocate(N);
      }
      varVector(const Type& V) {
        myError("Cannot create from variable vector");
      }
      virtual ~varVector() {}
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
      void swap(Type& V);
      virtual const char* type() const;
  };
}

#endif

