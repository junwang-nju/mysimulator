
#ifndef _Array_Data_Interface_H_
#define _Array_Data_Interface_H_

#include "basic/fill.h"
#include "basic/imprint.h"
#include "basic/is-same.h"
#include "type/is-memcopyable.h"
#include "type/is-char.h"
#include <cstdlib>
#include <cstring>
#include <cassert>

namespace mysimulator {

  template <typename T> class ArrayData;
  template <typename T> void Clear(ArrayData<T>&);
  template <typename T> void _Swap(ArrayData<T>&,ArrayData<T>&);
  template <typename T> void _SwapContent(ArrayData<T>&,ArrayData<T>&);
  template <typename T> bool IsSame(const ArrayData<T>&,const ArrayData<T>&);

  template <typename T>
  class ArrayData {

    public:

      typedef ArrayData<T>  Type;
      friend void Clear<T>(ArrayData<T>&);
      friend void _Swap<T>(ArrayData<T>&,ArrayData<T>&);
      friend void _SwapContent<T>(ArrayData<T>&,ArrayData<T>&);
      friend bool IsSame<T>(const ArrayData<T>&,const ArrayData<T>&);
      template <typename T1>  friend class ArrayData;

      ArrayData() : _data(NULL), _size(0), _alloc(false) {}
      virtual ~ArrayData() { Clear(*this); }

      bool IsValid() const { return _data!=NULL; }
      virtual void Allocate(unsigned int n) {
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
      template <typename T1>
      void ImprintStructure(const ArrayData<T1>& A) { Allocate(A.Size()); }
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
      void CopyN(const ArrayData<T1>& D,unsigned int n) {
        assert(IsValid());
        assert(D.IsValid());
        assert(Size()>=n);
        assert(D.Size()>=n);
        T   *p=_data, *pEnd=p+n;
        T1  *q=D._data;
        for(;p!=pEnd;)  _Copy(*(p++),*(q++));
      }
      template <typename T1>
      void Copy(const ArrayData<T1>& D) {
        assert(Size()==D.Size());
        CopyN(D,Size());
      }
      template <typename T1>
      void Fill(const T1& D) {
        assert(IsValid());
        T   *p=_data, *pEnd=p+this->Size();
        for(;p!=pEnd;)  _Fill(*(p++),D);
      }

     void MemCopy(const ArrayData<T>& A) {
       typedef typename IsMemCopyable<T>::Type  MemCopyCheck;
       assert(IsValid());
       assert(A.IsValid());
       assert(Size()==A.Size());
       memcpy(Head(),A.Head(),Size()*sizeof(T));
     }
     template <typename T1>
     void MemFill(const T1 c) {
       typedef typename IsChar<T>::Type   CharCheck1;
       typedef typename IsChar<T1>::Type  CharCheck2;
       memset(Head(),c,Size());
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

  template <typename T1, typename T2>
  bool IsSameSize(const ArrayData<T1>& A,const ArrayData<T2>& B) {
    return A.Size()==B.Size();
  }

  template <typename T>
  bool IsSame(const ArrayData<T>& A, const ArrayData<T>& B) {
    if(!IsSameSize(A,B))  return false;
    if(A.Size()==0)   return true;
    char *p=reinterpret_cast<char*>(A.Head()),*pEnd=p+A.Size()*sizeof(T);
    char *q=reinterpret_cast<char*>(B.Head());
    for(;p!=pEnd;)  if(!IsSame(*(p++),*(q++)))  return false;
    return true;
  }

}

#include "basic/swap.h"

namespace mysimulator {

  template <typename T>
  void _Swap(ArrayData<T>& A, ArrayData<T>& B) {
    _SwapContent(A._data,B._data);
    _SwapContent(A._size,B._size);
    _SwapContent(A._alloc,B._alloc);
  }

  template <typename T>
  void _SwapContent(ArrayData<T>& A, ArrayData<T>& B) {
    assert(A.IsValid());
    assert(B.IsValid());
    assert(A.Size()==B.Size());
    T *p=A.Head(), *pEnd=A.Head()+A.Size();
    T *q=B.Head();
    for(;p!=pEnd;)  _SwapContent(*(p++),*(q++));
  }

}

#endif

