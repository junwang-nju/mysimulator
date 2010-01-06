
/**
 * @file var-vector.h
 * @brief Vector with variable storage
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Variable_Vector_H_
#define _Variable_Vector_H_

#include "memory.h"
#include "ref-vector.h"

namespace std {

  template <typename T>
  class varVector : public referableVector<T> {

    public:

      typedef T               DataType;

      typedef varVector<T>    Type;

      typedef referableVector<T>   ParentType;

      varVector() : ParentType() {}

      varVector(const uint& n) : ParentType() { allocate(n); }

      varVector(const Type& v) { myError("vector copier is prohibited!"); }

      ~varVector() {  clear(); }

      void clear() {
        if(!this->isAvailable())  return;
        safe_delete(this->Data);
        static_cast<ParentType*>(this)->clear();
      }

      Type& allocate(const uint& n) {
        this->rTable.clear();
        if(this->nData!=n) {
          safe_delete(this->Data);
          this->nData=n;
          this->Data=new T[this->nData];
          this->set_HeadTail();
        }
        return *this;
      }

      Type& allocate(const int& n) { return allocate(static_cast<uint>(n)); }

      template <typename rT>
      Type& allocate(const VectorBase<rT>& v) { return allocate(v.size()); }

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
        this->rTable.swap(v.rTable);
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
