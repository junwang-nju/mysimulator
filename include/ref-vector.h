
#ifndef _Reference_Vector_H_
#define _Reference_Vector_H_

#include "vector-base.h"
#include <cassert>

namespace std {

  template <typename T>
  class refVector : public VectorBase<T> {

    public:

      typedef refVector<T>  Type;

      typedef VectorBase<T> ParentType;

      refVector() : ParentType() {}

      refVector(const Type&) {
        myError("Cannot create from reference vector");
      }

      virtual ~refVector() {}

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

      void refer(const VectorBase<T>& V) { refer(V,0,V.size()); }

      void refer(const VectorBase<T>& V, const unsigned int off,
                                         const unsigned int size) {
        assert(V.IsAvailable());
        assert(off+size<=V.size());
        this->data()=const_cast<T*>(V.data())+off;
        this->SetSize(size);
      }

      void swap(Type& v) {
        T* pT;
        pT=this->data();    this->data()=v.data();      v.data()=pT;
        unsigned int n=this->size(),nv=v.size();
        this->SetSize(nv);    v.SetSize(n);
      }

      virtual const char* type() const { return "Reference Vector"; }

  };

}

#endif

