
#ifndef _Array2D_Numeric_Interface_H_
#define _Array2D_Numeric_Interface_H_

#include "array2d/base/interface.h"

namespace mysimulator {

  template <typename T> class Array2DNumeric;
  template <typename T> void Clear(Array2DNumeric<T>&);
  template <typename T> T BlasDot(const Array2DNumeric<T>&,
                                  const Array2DNumeric<T>&);

  template <typename T>
  class Array2DNumeric : public Array2DBase<T,ArrayNumeric> {

    public:

      typedef Array2DNumeric<T>   Type;
      typedef Array2DBase<T,ArrayNumeric> ParentType;
      friend void Clear<T>(Array2DNumeric<T>&);
      friend T BlasDot<T>(const Array2DNumeric<T>&,const Array2DNumeric<T>&);
      template <typename T1> friend class Array2DNumeric;

      Array2DNumeric() : ParentType() {}
      ~Array2DNumeric() { Clear(*this); }

      typename DataType<Type>::Type Summation() const {
        assert(this->IsValid());
        return this->_ldata.Summation();
      }
      typename DataType<Type>::Type AbsSummation() const {
        assert(this->IsValid());
        return this->_ldata.AbsSummation();
      }
      typename DataType<Type>::Type NormSQ() const {
        assert(this->IsValid());
        return this->_ldata.NormSQ();
      }
      typename DataType<Type>::Type Norm() const {
        assert(this->IsValid());
        return __SqRoot(NormSQ());
      }

      template <typename T1>
      void Scale(const T1& d) {
        assert(this->IsValid());
        this->_ldata.Scale(d);
      }
      template <typename T1>
      void Scale(const Array2DNumeric<T1>& A) {
        assert(this->IsValid());
        assert(A.IsValid());
        assert(IsSameSize(*this,A));
        this->_ldata.Scale(A._ldata);
      }
      template <typename T1>
      void Shift(const T1& d) {
        assert(this->IsValid());
        this->_ldata.Shift(d);
      }
      template <typename T1>
      void Shift(Array2DNumeric<T1>& A) {
        assert(this->IsValid());
        assert(A.IsValid());
        assert(IsSameSize(*this,A));
        this->_ldata.Shift(A._ldata);
      }

      template <typename T1>
      void NegShift(const T1& d) {
        assert(this->IsValid());
        this->_ldata.NegShift(d);
      }
      template <typename T1>
      void NegShift(const Array2DNumeric<T1>& A) {
        assert(this->IsValid());
        assert(A.IsValid());
        assert(IsSameSize(*this,A));
        this->_ldata.NegShift(A._ldata);
      }
      template <typename T1,typename T2>
      void Shift(const Array2DNumeric<T1>& A,const T2& d) {
        assert(this->IsValid());
        assert(A.IsValid());
        assert(IsSameSize(*this,A));
        this->_ldata.Shift(A._ldata,d);
      }
      template <typename T1,typename T2>
      void Shift(const T1& d,const Array2DNumeric<T2>& A) { Shift(A,d); }
      template <typename T1,typename T2>
      void Shift(const Array2DNumeric<T1>& A,const Array2DNumeric<T2>& B) {
        assert(this->IsValid());
        assert(A.IsValid());
        assert(B.IsValid());
        assert(IsSameSize(*this,A));
        assert(IsSameSize(*this,B));
        this->_ldata.Shift(A._ldata,B._ldata);
      }
      template <typename T1,typename T2,typename T3>
      void Shift(const T1& d,const Array2DNumeric<T2>& A,
                 const Array2DNumeric<T3>& B) {
        assert(this->IsValid());
        assert(A.IsValid());
        assert(B.IsValid());
        assert(IsSameSize(*this,A));
        assert(IsSameSize(*this,B));
        this->_ldata.Shift(d,A._ldata,B._ldata);
      }

      void BlasCopy(const Array2DNumeric<T>& A) {
        assert(this->IsValid());
        assert(A.IsValid());
        assert(IsSameSize(*this,A));
        this->_ldata.BlasCopy(A._ldata);
      }
      void BlasFill(const T& d) {
        assert(this->IsValid());
        this->_ldata.BlasFill(d);
      }
      template <typename T1>
      void BlasScale(const T1& d) {
        assert(this->IsValid());
        this->_ldata.BlasScale(d);
      }
      void BlasScale(const Array2DNumeric<T>& A) {
        assert(this->IsValid());
        assert(A.IsValid());
        assert(IsSameSize(*this,A));
        this->_ldata.BlasScale(A._ldata);
      }
      template <typename T1>
      void BlasShift(const T1& d) {
        assert(this->IsValid());
        this->_ldata.BlasShift(d);
      }
      template <typename T1>
      void BlasShift(const T1& d,const Array2DNumeric<T>& A) {
        assert(this->IsValid());
        assert(A.IsValid());
        assert(IsSameSize(*this,A));
        this->_ldata.BlasShift(d,A._ldata);
      }
      template <typename T1>
      void BlasShift(const Array2DNumeric<T>& A,const T1& d) {
        BlasShift(d,A);
      }
      void BlasShift(const Array2DNumeric<T>& A) { BlasShift(1.,A); }
      template <typename T1>
      void BlasShift(const T1& d,const Array2DNumeric<T>& A,
                     const Array2DNumeric<T>& B) {
        assert(this->IsValid());
        assert(A.IsValid());
        assert(B.IsValid());
        assert(IsSameSize(*this,A));
        assert(IsSameSize(*this,B));
        this->_ldata.BlasShift(d,A._ldata,B._ldata);
      }
      void BlasShift(const Array2DNumeric<T>& A,const Array2DNumeric<T>& B) {
        BlasShift(1.,A,B);
      }
      T BlasNormSQ() const {
        assert(this->IsValid());
        return this->_ldata.BlasNormSQ();
      }
      T BlasNorm() const {
        assert(this->IsValid());
        return this->_ldata.BlasNorm();
      }
      T BlasAbsSum() const {
        assert(this->IsValid());
        return this->_ldata.BlasAbsSum();
      }

      void Inverse() {
        assert(this->IsValid());
        this->_ldata.Inverse();
      }
      void SqRoot() {
        assert(this->IsValid());
        this->_ldata.SqRoot();
      }

      template <typename T1>
      typename CombineType<typename DataType<T>::Type,
                           typename DataType<T1>::Type>::Type
      __Dot(const Array2DNumeric<T1>& B) const {
        assert(this->IsValid());
        assert(B.IsValid());
        assert(IsSameSize(*this,B));
        return _Dot<T,T1>(this->_ldata,B._ldata);
      }

    private:

      Array2DNumeric(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(Array2DNumeric<T>& A) {
    Clear(static_cast<Array2DBase<T,ArrayNumeric>&>(A));
  }

  template <typename T>
  bool IsSame(const Array2DNumeric<T>& A, const Array2DNumeric<T>& B) {
    //typedef typename Array2DNumeric<T>::ParentType  PType;
    //return IsSame<ArrayNumeric,ArrayNumeric>(static_cast<const PType&>(A),
    //                                         static_cast<const PType&>(B));
    return IsSame(static_cast<const Array2DBase<T,ArrayNumeric>&>(A),
                  static_cast<const Array2DBase<T,ArrayNumeric>&>(B));
  }

  template <typename T1,typename T2>
  void _Copy(Array2DNumeric<T1>& A,const Array2DNumeric<T2>& B) { A.Copy(B); }

  template <typename T1,typename T2>
  void _Fill(Array2DNumeric<T1>& A,const T2& d) { A.Fill(d); }

  template <typename T>
  void _Imprint(Array2DNumeric<T>& A,const Array2DNumeric<T>& B) {
    A.Imprint(B);
  }

  template <typename T>
  void _SwapContent(Array2DNumeric<T>& A,Array2DNumeric<T>& B) {
    typedef typename Array2DNumeric<T>::ParentType  PType;
    _SwapContent<T,ArrayNumeric,ArrayNumeric>(static_cast<PType&>(A),
                                              static_cast<PType&>(B));
  }

  template <typename T> class Array2D;

  template <typename T>
  bool IsSame(const Array2DNumeric<T>& A, const Array2D<T>& B) {
    return IsSame(static_cast<const Array2DBase<T,ArrayNumeric>&>(A),
                  static_cast<const Array2DBase<T,Array>&>(B));
  }

  template <typename T1,typename T2>
  void _Copy(Array2DNumeric<T1>& A,const Array2D<T2>& B) { A.Copy(B); }

  template <typename T>
  void _Imprint(Array2DNumeric<T>& A,const Array2D<T>& B) { A.Imprint(B); }

  template <typename T>
  void _SwapContent(Array2DNumeric<T>& A, Array2D<T>& B) {
    _SwapContent(static_cast<Array2DBase<T,ArrayNumeric>&>(A),
                 static_cast<Array2DBase<T,Array>&>(B));
  }

  template <typename T1,typename T2>
  typename CombineType<typename DataType<T1>::Type,
                       typename DataType<T2>::Type>::Type
  _Dot(const Array2DNumeric<T1>& A,const Array2DNumeric<T2>& B) {
    return A.__Dot(B);
  }

  template <typename T>
  T BlasDot(const Array2DNumeric<T>& A,const Array2DNumeric<T>& B) {
    assert(A.IsValid());
    assert(B.IsValid());
    assert(IsSameSize(A,B));
    return BlasDot(A._ldata,B._ldata);
  }

  template <typename T>
  typename DataType<Array2DNumeric<T> >::Type _Sum(const Array2DNumeric<T>& A){
    return A.Summation();
  }

  template <typename T>
  typename DataType<Array2DNumeric<T> >::Type
  _AbsSum(const Array2DNumeric<T>& A) { return A.AbsSummation(); }

  template <typename T>
  typename DataType<Array2DNumeric<T> >::Type
  _NormSQ(const Array2DNumeric<T>& A) { return A.NormSQ(); }

  template <typename T,typename T1>
  void _Scale(Array2DNumeric<T>& A,const T1& d) { A.Scale(d); }
  template <typename T,typename T1>
  void _Scale(Array2DNumeric<T>& A,const Array2DNumeric<T1>& B) { A.Scale(B); }

  template <typename T,typename T1>
  void _Shift(Array2DNumeric<T>& A,const T1& d) { A.Shift(d); }
  template <typename T,typename T1>
  void _Shift(Array2DNumeric<T>& A,const Array2DNumeric<T1>& B) { A.Shift(B); }

  template <typename T,typename T1>
  void _NegShift(Array2DNumeric<T>& A,const T1& d) { A.NegShift(d); }
  template <typename T,typename T1>
  void _NegShift(Array2DNumeric<T>& A,const Array2DNumeric<T>& B) {
    A.NegShift(B);
  }

  template <typename T,typename T1,typename T2>
  void _Shift(Array2DNumeric<T>& A,const Array2DNumeric<T1>& B,const T2& d) {
    A.Shift(B,d);
  }
  template <typename T,typename T1,typename T2>
  void _Shift(Array2DNumeric<T>& A,const T1& d,const Array2DNumeric<T2>& B) {
    A.Shift(d,B);
  }
  template <typename T,typename T1,typename T2>
  void _Shift(Array2DNumeric<T>& A,
              const Array2DNumeric<T1>& B,const Array2DNumeric<T2>& C) {
    A.Shift(B,C);
  }
  template <typename T,typename T1,typename T2,typename T3>
  void _Shift(Array2DNumeric<T>& A,const T1& d,
              const Array2DNumeric<T2>& B,const Array2DNumeric<T3>& C) {
    A.Shift(d,B,C);
  }
  template <typename T>
  void _Inverse(const Array2DNumeric<T>& A) { A.Inverse(); }
  template <typename T>
  void _SqRoot(const Array2DNumeric<T>& A) { A.SqRoot(); }

}

#endif

