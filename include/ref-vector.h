
#ifndef _Reference_Vector_H_
#define _Reference_Vector_H_

#include "referable-vector.h"

namespace std {
  template <typename T>
  class refVector : public VectorBase<T> {
    protected:
      Pool<void*>*  pRefList;
      int  thisID;
    public:
      static const bool IsReferable;
      typedef T DataType;
      typedef refVector<T>  Type;
      typedef VectorBase<T> ParentType;
      refVector() : ParentType(), pRefList(NULL), thisID(-1) {
        this->SetSwapFlag(true);
      }
      refVector(const Type& V) {
        myError("Cannot create from ref-vector");
      }
      ~refVector() { pRefList=NULL; thisID=-1; }
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
      void refer(const referableVector<T>& V);
      void refer(const referableVector<T>& V,
                 const unsigned int& off, const unsigned int& sz);
      void swap(Type& V);
      virtual const char* type() const;
  };
  template <typename T>
  const bool refVector<T>::IsReferable=false;
}

#endif

