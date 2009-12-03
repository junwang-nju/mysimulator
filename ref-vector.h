
#ifndef _Reference_Vector_H_
#define _Reference_Vector_H_

#include "vector-base.h"

namespace std {

  template <typename T>
  class refVector : public VectorBase<T> {

    public:

      typedef T             DataType;

      typedef refVector<T>  Type;

      typedef VectorBase<T> ParentType;

      refVector() : ParentType() {}

      refVector(const Type&) { myError("vector copier is prohibited!"); }

      Type& operator=(const Type& v) { this->assign(v); return *this; }

      template <typename inputT>
      Type& operator=(const inputT& v) { this->assign(v); return *this; }

      template <typename inputT>
      Type& operator*=(const inputT& v) { this->scale(v); return *this; }

      template <typename inputT>
      Type& operator+=(const inputT& v) { this->shift(v); return *this; }

      virtual const char* type() { return "Reference Vector"; }

      template <typename vType>
      Type& refer(const vType& v) {
        assert(vType::IsVector);
        this->Data=const_cast<T*>(v.data());
        this->nData=v.size();
        this->set_HeadTail();
        return *this;
      }

      bool isAvailable() const { return this->Data==NULL; }

      Type& swap(Type& v) {
        T* tptr;
        uint m;
        tptr=this->Data;  this->Data=v.Data;    v.Data=tptr;
        m=this->nData;    this->nData=v.nData;  v.nData=m;
        this->set_HeadTail();
        v.set_HeadTail();
        return *this;
      }

  };

  template <typename T>
  void swap(refVector<T>& va, refVector<T>& vb) { va.swap(vb); }

  template <typename T>
  istream& operator>>(istream& is, refVector<T>& v) {
    assert(v.isAvailable());
    uint n=v.size();
    for(uint i=0;i<n;++i)   is>>v[i];
    return is;
  }

}

#endif

