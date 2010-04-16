
#ifndef _Variable_Vector_H_
#define _Variable_Vector_H_

#include "vector-base.h"
#include "memory.h"

namespace std {

  template <typename T>
  class varVector : public VectorBase<T> {

    public:

      typedef varVector<T>    Type;

      typedef VectorBase<T>   ParentType;

      varVector() : ParentType() {}

      varVector(const unsigned int N) : ParentType() { allocate(N); }

      varVector(const Type&) { myError("Cannot create from variable vector"); }

      virtual ~varVector() { safe_delete_array(this->data()); }

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

      void clear() {
        safe_delete_array(this->data());
        static_cast<ParentType*>(this)->clear();
      }

      void allocate(const unsigned int N) {
        if(this->size()!=N) {
          safe_delete_array(this->data());
          this->data()=new T[N];
          this->SetSize(N);
        }
      }

      void swap(Type& v) {
        T* pT;
        pT=this->data();    this->data()=v.data();      v.data()=pT;
        unsigned int n=this->size(),nv=v.size();
        this->SetSize(nv);    v.SetSize(n);
      }

      void duplicate(const VectorBase<T>& v) {
        if(v.IsAvailable()) {
          allocate(v.size());
          operator=(v);
        } else clear();
      }

      virtual const char* type() const { return "Variable Vector"; }

  };

}

#endif

