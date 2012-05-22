
#ifndef _Array_Data_Interface_H_
#define _Array_Data_Interface_H_

#include "basic/fill.h"
#include "basic/imprint.h"
#include <cstdlib>
#include <cassert>

namespace mysimulator {

  template <typename T>
  class ArrayData {

    public:

      typedef ArrayData<T>  Type;
      template <typename T1> friend void Clear(ArrayData<T1>&);
      template <typename T1> friend void _Swap(ArrayData<T1>&,ArrayData<T1>&);
      template <typename T1>
      friend void _SwapContent(ArrayData<T1>&,ArrayData<T1>&);

      ArrayData() : _data(NULL), _size(0), _alloc(false) {}
      ~ArrayData() { Clear(*this); }

      bool IsValid() const { return _data!=NULL; }
      void Allocate(unsigned int n) {
        if(IsValid()&&(Size()==n))  return;
        Clear(*this);
        if(n==0)  return;
        _data=new T[n];
        _size=n;
        SetAllocFlag(true);
      }
      void Imprint(const ArrayData<T>& A) {
        Allocate(A.Size());
        T *p=Head(), *pEnd=p+Size();
        T *q=A.Head();
        for(;p!=pEnd;)  _Imprint(*(p++),*(q++));
      }
      void Refer(Type& A,unsigned int b,unsigned int n) {
        assert(b+n<=A.Size());
        Clear(*this);
        _data=A._data+b;
        _size=n;
        SetAllocFlag(false);
      }
      void Refer(Type& A) { Refer(A,0,A.Size()); }

      unsigned int Size() const { return _size; }
      const T& operator[](unsigned int n) const {
        assert(n<_size);
        return *(_data+n);
      }
      T& operator[](unsigned int n) { assert(n<_size); return *(_data+n); }

      template <typename T1>
      void Copy(const ArrayData<T1>& D) {
        typedef typename IsCopyable<ArrayData<T>,ArrayData<T1> >::Type
                CopyCheck;
        assert(IsValid());
        assert(D.IsValid());
        assert(Size()==D.Size());
        T   *p=_data, *pEnd=p+Size();
        T1  *q=D._data;
        for(;p!=pEnd;)  _Copy(*(p++),*(q++));
      }
      template <typename T1>
      void Fill(const T1& D) {
        typedef typename IsFillable<ArrayData<T>,T1>::Type  FillCheck;
        assert(IsValid());
        T   *p=_data, *pEnd=p+this->Size();
        for(;p!=pEnd;)  _Fill(*(p++),D);
      }

    protected:

      T* _data;
      unsigned int _size;
      bool _alloc;

      T* Head() const { return _data; }
      void SetAllocFlag(bool aFlag) { _alloc=aFlag; }

    private:

      ArrayData(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(ArrayData<T>& D) {
    if(D.IsValid()) {
      if(D._alloc)  delete[] D._data;
      D._data=NULL;
      D._size=0;
    }
  }

  template <typename T>
  void _Imprint(ArrayData<T>& A, const ArrayData<T>& B) { A.Imprint(B); }

  template <typename T, typename T1>
  void _Copy(ArrayData<T>& A, const ArrayData<T1>& cA) { A.Copy(cA); }

  template <typename T, typename T1>
  void _Fill_(ArrayData<T>& A, const T1& D) { A.Fill(D); }

}

#endif

