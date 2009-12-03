
#ifndef _Variable_Vector_H_
#define _Variable_Vector_H_

#include "memory.h"
#include "refer-table.h"
#include "vector-base.h"

namespace std {

  template <typename T>
  class varVector : public VectorBase<T> {

    public:

      typedef T               DataType;

      typedef varVector<T>    Type;

      typedef VectorBase<T>   ParentType;

      ReferTable<T> rTable;

      varVector() : ParentType(), rTable() {}

      varVector(const uint& n) : ParentType(), rTable() { allocate(n); }

      varVector(const Type& v) { myError("vector copier is prohibited!"); }

      ~varVector() {  clear(); }

      void clear() {
        if(!this->isAvailable())  return;
        rTable.clear();
        safe_delete(this->Data);
        static_cast<ParentType*>(this)->clear();
      }

      Type& allocate(const uint& n) {
        rTable.clear();
        if(this->nData!=n) {
          safe_delete(this->Data);
          this->nData=n;
          this->Data=new T[this->nData];
          this->set_HeadTail();
        }
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

      virtual const char* type() { return "Variable Vector"; }

      Type& swap(Type& v) {
        T* tptr;
        uint tmn;
        tptr=this->Data;        this->Data=v.Data;            v.Data=tptr;
        tmn=this->nData;        this->nData=v.nData;          v.nData=tmn;
        this->set_HeadTail();
        v.set_HeadTail();
        rTable.clear();
        v.rTable.clear();
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
