
#ifndef _Reference_Vector_H_
#define _Reference_Vector_H_

#include "vector-base.h"
#include "refer-table.h"

namespace std {

  template <typename T>
  class refVector : public VectorBase<T> {

    public:

      typedef T             DataType;

      typedef refVector<T>  Type;

      typedef VectorBase<T> ParentType;

      ReferTable<T>* pTable;

      int inTable;

      refVector() : ParentType(), pTable(NULL), inTable(-1) {}

      refVector(const Type&) { myError("vector copier is prohibited!"); }

      ~refVector() { clear(); }

      void clear() {
        static_cast<ParentType*>(this)->clear();
        pTable=NULL;
        inTable=-1;
      }

      Type& operator=(const Type& v) { this->assign(v); return *this; }

      template <typename inputT>
      Type& operator=(const inputT& v) { this->assign(v); return *this; }

      template <typename inputT>
      Type& operator*=(const inputT& v) { this->scale(v); return *this; }

      template <typename inputT>
      Type& operator+=(const inputT& v) { this->shift(v); return *this; }

      virtual const char* type() { return "Reference Vector"; }

      template <typename vType>
      Type& refer(const vType& v, const uint& offset, const uint& sz) {
        assert(vType::IsVector);
        assert(v.rTable.count()<ReferTable<T>::MaxRefInstance);
        assert(offset+sz<=v.size());
        if(this->isAvailable()) {
          if(inTable!=static_cast<int>(pTable->count())-1)
            pTable->refinst[inTable]=pTable->refinst[pTable->count()-1];
          pTable->dec();
          pTable=NULL;
          inTable=-1;
        }
        this->Data=const_cast<T*>(v.data()+offset);
        this->nData=sz;
        this->set_HeadTail();
        pTable=const_cast<ReferTable<T>*>(&(v.rTable));
        pTable->refinst[pTable->count()]=this;
        inTable=pTable->count();
        pTable->inc();
        return *this;
      }

      template <typename vType>
      Type& refer(const vType& v) { return refer(v,uZero,v.size()); }

      Type& swap(Type& v) {
        T* tptr;
        uint m;
        tptr=this->Data;  this->Data=v.Data;    v.Data=tptr;
        m=this->nData;    this->nData=v.nData;  v.nData=m;
        this->set_HeadTail();
        v.set_HeadTail();
        ReferTable<T>* rptr;
        rptr=pTable;      pTable=v.pTable;      v.pTable=rptr;
        m=inTable;        inTable=v.inTable;    v.inTable=m;
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

