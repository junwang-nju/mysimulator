
#ifndef _Array2D_Base_Interface_
#define _Array2D_Base_Interface_

#include "array-numeric/interface.h"

namespace mysimulator {

  template <typename T,template<typename>class AF>  class Array2DBase;

  template <typename T,template<typename> class ArrayFormat>
  class Array2DBase : public ArrayFormat<ArrayFormat<T> > {

    public:

      typedef Array2DBase<T,ArrayFormat>  Type;
      typedef ArrayFormat<ArrayFormat<T> >  ParentType;
      template <typename T1,template<typename> class AF>
      friend void Clear(Array2DBase<T1,AF>&);
      template <typename T1,
                template<typename>class AF1,template<typename>class AF2>
      friend bool IsSame(const Array2DBase<T1,AF1>&,const Array2DBase<T1,AF2>&);
      template <typename T1,
                template<typename>class AF1,template<typename>class AF2>
      friend void _SwapContent(Array2DBase<T,AF1>&,Array2DBase<T,AF2>&);
      template <typename T1,template<typename> class AF1>
      friend class Array2DBase;

      Array2DBase() : ParentType(), _ldata() {}
      ~Array2DBase() { Clear(*this); }

      bool IsValid() const {
        return static_cast<const ParentType*>(this)->IsValid()&&
               _ldata.IsValid();
      }
      unsigned int NumElements() const { return _ldata.Size(); }

      void Allocate(const ArrayNumeric<unsigned int>& sz) {
        Clear(*this);
        static_cast<ParentType*>(this)->Allocate(sz.Size());
        _ldata.Allocate(sz.Summation());
        for(unsigned int i=0,m=0;i<sz.Size();m+=sz[i],++i)
          static_cast<ParentType*>(this)->operator[](i).Refer(_ldata,m,sz[i]);
      }
      void Allocate(unsigned int n1, unsigned int n2) {
        Clear(*this);
        static_cast<ParentType*>(this)->Allocate(n1);
        _ldata.Allocate(n1*n2);
        for(unsigned int i=0,m=0;i<n1;m+=n2,++i)
          static_cast<ParentType*>(this)->operator[](i).Refer(_ldata,m,n2);
      }
      void Refer(Type& A,unsigned int b, unsigned int n) {
        assert(A.IsValid());
        Clear(*this);
        static_cast<ParentType*>(this)->Refer(static_cast<ParentType&>(A),b,n);
        unsigned int bl,nl;
        bl=static_cast<unsigned int>(A[b].Head()-A[0].Head());
        nl=(b+n<this->Size()?
            static_cast<unsigned int>(A[b+n].Head()-A[b].Head()):
            A._ldata.Size()-bl);
        _ldata.Refer(A._ldata,bl,nl);
      }
      void Refer(Type& A) {
        assert(A.IsValid());
        Clear(*this);
        static_cast<ParentType*>(this)->Refer(static_cast<ParentType&>(A));
        _ldata.Refer(A._ldata);
      }

      template <typename T1,template<typename> class AF1>
      void Copy(const Array2DBase<T1,AF1>& A) {
        assert(this->IsValid());
        assert(A.IsValid());
        assert(IsSameSize(*this,A));
        _ldata.Copy(A._ldata);
      }
      template <typename T1>
      void Fill(const T1& d) {
        assert(this->IsValid());
        _ldata.Fill(d);
      }
      template <template<typename> class AF>
      void MemCopy(const Array2DBase<T,AF>& A) {
        assert(this->IsValid());
        assert(A.IsValid());
        assert(IsSameSize(*this,A));
        _ldata.MemCopy(A._ldata);
      }
      template <typename T1>
      void MemFill(const T1 c) {
        assert(this->IsValid());
        _ldata.MemFill(c);
      }
      template <template<typename> class AF>
      void Imprint(const Array2DBase<T,AF>& A) {
        assert(A.IsValid());
        Clear(*this);
        static_cast<ParentType*>(this)->Allocate(A.Size());
        _ldata.Imprint(A._ldata);
        for(unsigned int i=0,m=0;i<A.Size();m+=A[i].Size(),++i)
          this->operator[](i).Refer(_ldata,m,A[i].Size());
      }
      template <typename T1,template<typename> class AF>
      void ImprintStructure(const Array2DBase<T1,AF>& A) {
        assert(A.IsValid());
        Clear(*this);
        static_cast<ParentType*>(this)->Allocate(A.Size());
        _ldata.Allocate(A._ldata.Size());
        for(unsigned int i=0,m=0;i<A.Size();m+=A[i].Size(),++i)
          this->operator[](i).Refer(_ldata,m,A[i].Size());
      }

    protected:

      ArrayFormat<T>  _ldata;

    private:

      Array2DBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,template<typename> class AF>
  void Clear(Array2DBase<T,AF>& A) {
    Clear(static_cast<AF<AF<T> >&>(A));
    Clear(A._ldata);
  }

  template <typename T1,template<typename> class AF1,
            typename T2,template<typename> class AF2>
  void _Copy(Array2DBase<T1,AF1>& A,const Array2DBase<T2,AF2>& B) { A.Copy(B); }
  template <typename T1,template<typename> class AF1,typename T2>
  void _Fill(Array2DBase<T1,AF1>& A,const T2& d) { A.Fill(d); }

  template <typename T,template<typename> class AF>
  void _Imprint(Array2DBase<T,AF>& A,const Array2DBase<T,AF>& B) {
    A.Imprint(B);
  }

  template <typename T,
           template<typename> class AF1,template<typename> class AF2>
  void _SwapContent(Array2DBase<T,AF1>& A,Array2DBase<T,AF2>& B) {
    assert(A.IsValid());
    assert(B.IsValid());
    assert(IsSameSize(A,B));
    _SwapContent(A._ldata,B._ldata);
  }

  template <typename T1,template<typename> class AF1,
            typename T2,template<typename> class AF2>
  bool IsSameSize(const Array2DBase<T1,AF1>& A,const Array2DBase<T2,AF2>& B) {
    typedef typename Array2DBase<T1,AF1>::ParentType  PType1;
    typedef typename Array2DBase<T2,AF2>::ParentType  PType2;
    if(!IsSameSize(static_cast<const PType1&>(A),static_cast<const PType2&>(B)))
      return false;
    for(unsigned int i=0;i<A.Size();++i)
      if(!IsSameSize(A[i],B[i]))  return false;
    return true;
  }

  template <typename T,template<typename>class AF1,template<typename>class AF2>
  bool IsSame(const Array2DBase<T,AF1>& A,const Array2DBase<T,AF2>& B) {
    if(!IsSameSize(A,B))  return false;
    return IsSame(A._ldata,B._ldata);
  }

}

#endif

