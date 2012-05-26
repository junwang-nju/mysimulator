
#ifndef _Array_Data_Interface_H_
#define _Array_Data_Interface_H_

#include "basic/copy.h"
#include <cstdlib>
#include <cassert>

namespace mysimulator {

  template <typename T> class ArrayData;
  template <typename T> void Clear(ArrayData<T>&);

  template <typename T>
  class ArrayData {

    public:

      typedef ArrayData<T>  Type;
      friend void Clear<T>(Type&);

      ArrayData() : _data(NULL), _size(0), _alloc(false) {}
      ~ArrayData() { Clear(*this); }

      bool IsValid() const { return _data!=NULL; }
      void Allocate(unsigned int n) {
        Clear(*this);
        if(n==0)  return;
        _data=new T[n];
        _size=n;
        SetAllocFlag(true);
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
      void Copy(const ArrayData<T1>& D, unsigned int n) {
        typedef typename IsCopyable<T,T1>::Type CopyCheck;
        assert(IsValid());
        assert(D.IsValid());
        assert(n<=Size());
        assert(n<=D.Size());
        T   *p=_data, *pEnd=p+n;
        T1  *q=D._data;
        for(;p!=pEnd;)  _Copy(*(p++),*(q++));
      }
      template <typename T1>
      void Copy(const ArrayData<T1>& D) {
        assert(Size()==D.Size());
        Copy(D,Size());
      }
      template <typename T1>
      void Fill(const T1& D, unsigned int n) {
        assert(IsValid());
        assert(D.IsValid());
        assert(n<=Size());
        T   *p=_data, *pEnd=p+n;
        for(;p!=pEnd;)  _Fill(*(p++),D);
      }
      template <typename T1>
      void Fill(const T1& D) {  Fill(D,Size()); }

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
  void Clear(ArrayData<T>& D) {   // Cannot work after Allocate
    if(D.IsValid()) {
      if(D._alloc)  delete[] D._data;
      D._data=NULL;
      D._size=0;
    }
  }

  template <typename T, typename T1>
  void _Copy(ArrayData<T>& A, const ArrayData<T>& cA, unsigned int  n) {
    A.Copy(cA,n);
  }

  template <typename T, typename T1>
  void _Copy(ArrayData<T>& A, const ArrayData<T>& cA) { A.Copy(cA); }

  template <typename T, typename T1>
  void _Fill(ArrayData<T>& A, const T1& D, unsigned int n) { A.Fill(D,n); }

  template <typename T, typename T1>
  void _Fill_(ArrayData<T>& A, const T1& D) { A.Fill(D); }

}

#endif

