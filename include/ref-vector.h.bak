
#ifndef _Reference_Vector_H_
#define _Reference_Vector_H_

#include "ref-object.h"
#include "vector-base.h"
#include <cassert>

namespace std {

  template <typename T>
  class refVector : public refObject<VectorBase<T>,VectorBase<T> > {

    public:

      typedef T   DataType;

      typedef refVector<T>  Type;

      typedef refObject<VectorBase<T>,VectorBase<T> > ParentType;

      refVector() : ParentType() {
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

      virtual void refer(ParentType& V) { refer(V,0,V.size()); }

      virtual void refer(ObjectWStorage<VectorBase<T> >& V) {
        refer(V,0,V.size());
      }

      void refer(ParentType& V, const unsigned int off, const unsigned int sz){
        assert(off+sz<=V.size());
        if(this->IsAvailable()) this->RefInfo().remove_self();
        this->data()=const_cast<T*>(V.data())+off;
        this->SetSize(sz);
        this->SetHeadTail();
        V.RefInfo().add_before(this->RefInfo());
      }

      void refer(ObjectWStorage<VectorBase<T> >& V,
                 const unsigned int off, const unsigned int sz) {
        assert(off+sz<=V.size());
        if(this->IsAvailable()) this->RefInfo().remove_self();
        this->data()=const_cast<T*>(V.data())+off;
        this->SetSize(sz);
        this->SetHeadTail();
        V.RefList().append(this->RefInfo());
      }

      virtual const char* type() const { return "Reference Vector"; }

  };

}

#endif

