
#ifndef _Variable_Vector_H_
#define _Variable_Vector_H_

#include "memory.h"
#include "vector-base.h"

namespace std {

  template <typename T, uint NT>
  class fixVector;

  template <typename T>
  class varVector : public VectorBase<T> {

    public:

      typedef T               DataType;

      typedef varVector<T>    Type;

      typedef VectorBase<T>   ParentType;

      uint ref_state;

      varVector() : ParentType(), ref_state(0) {}

      varVector(const uint& n) : ParentType() { allocate(n); }

      varVector(const Type& v) { myError("vector copier is prohibited!"); }

      ~varVector() {  clear();  }

      void clear() {
        if(ref_state==0)  safe_delete(this->Data);
        static_cast<ParentType*>(this)->clear();
      }

      Type& allocate(const uint& n) {
        if((ref_state==0)&&(this->nData==n))  return *this;
        clear();
        this->nData=n;
        this->Data=new T[this->nData];
        this->set_HeadTail();
        ref_state=0;
        return *this;
      }

      Type& allocate(const int& n) { return allocate(static_cast<uint>(n)); }

      template <typename vType>
      Type& allocate(const vType& v) {
        assert(vType::IsVector);
        return allocate(v.size());
      }

      template <typename vType>
      Type& Duplicate(const vType& v) { allocate(v).assign(v); return *this; }

      Type& operator=(const Type& v) { this->assign(v); return *this; }

      template <typename inputT>
      Type& operator=(const inputT& v) { this->assign(v); return *this; }

      template <typename inputT>
      Type& operator*=(const inputT& v) { this->scale(v); return *this; }

      template <typename inputT>
      Type& operator+=(const inputT& v) { this->shift(v); return *this; }

      const uint& state() const { return ref_state; }

      void set_state(const uint& state) { ref_state=state; }

      virtual const char* type() { return "Variable Vector"; }

      Type& swap(Type& v) {
        T* tptr;
        uint tmn;
        tptr=this->Data;        this->Data=v.Data;            v.Data=tptr;
        tmn=this->nData;        this->nData=v.nData;          v.nData=tmn;
        tptr=this->head_ptr;    this->head_ptr=v.head_ptr;    v.head_ptr=tptr;
        tptr=this->tail_ptr;    this->tail_ptr=v.tail_ptr;    v.tail_ptr=tptr;
        tmn=ref_state;    ref_state=v.ref_state;  v.ref_state=tmn;
        return *this;
      }

      Type& refer(const Type& v) {
        if(ref_state==0)  clear();
        this->Data=v.Data;
        this->nData=v.nData;
        this->head_ptr=v.head_ptr;
        this->tail_ptr=v.tail_ptr;
        ref_state=1;
        return *this;
      }

  };

  template <typename T>
  void swap(varVector<T>& va, varVector<T>& vb) { va.swap(vb); }

  template <typename T>
  istream& operator>>(istream& is, varVector<T>& v) {
    uint n;
    is>>n;
    v.allocate(n);
    for(uint i=0;i<n;++i) is>>v[i];
    return is;
  }

}

#endif
