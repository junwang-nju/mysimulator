
#ifndef _Array_LongDataArray_Interface_H_
#define _Array_LongDataArray_Interface_H_

#include "array/data-array-interface.h"
#include <cstring>

namespace mysimulator {

  template <typename T>
  class Array<T,ArrayFormat::LongDataArray> : public DataArray<T> {

    public:

      typedef Array<T,ArrayFormat::LongDataArray>     Type;
      typedef DataArray<T>    ParentType;

      Array() : ParentType() {}
      Array(unsigned int size) : Array() { allocate(size); }
      Array(const Type&) = delete;
      virtual ~Array() { ParentType::~DataArray(); }

      Type& operator=(const Type& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(this->size()<=A.size());
        memcpy(this->head(),A.head(),this->size()*sizeof(T));
      }
      Type& operator=(const T& D) { return ParentType::operator=(D); }

      virtual void allocate(unsigned int size) override {
        unsigned int byte_size=size*sizeof(T);
        assert(byte_size>ShortThresholdByte);
        ParentType::allocate(size);
      }

      void copy(const Array<T,ArrayFormat::LongDataArray>& A, unsigned int num,
                unsigned int bg=0,  unsigned int dlt=1,
                unsigned int bgA=0, unsigned int dltA=1) {
        ParentType::copy(A,num,bg,dlt,bgA,dltA);
      }
      void fill(const T& D,unsigned int bg=0,unsigned int dlt=1) {
        ParentType::fill(D,bg,dlt);
      }

  };

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  template <>
  Array<int,ArrayFormat::LongDataArray>&
  Array<int,ArrayFormat::LongDataArray>::operator=(
      const Array<int,ArrayFormat::LongDataArray>& A) {
    static_assert(sizeof(int)==sizeof(float),
                  "sizes of int and float need to be equal!\n");
    assert((bool)(*this));
    assert((bool)A);
    assert(this->size()<=A.size());
    long n=this->size(), one=1;
    scopy_(&n,reinterpret_cast<float*>(A.head()),&one,
              reinterpret_cast<float*>(this->head()),&one);
    return *this;
  }

  template <>
  Array<int,ArrayFormat::LongDataArray>&
  Array<int,ArrayFormat::LongDataArray>::operator=(const int& D) {
    static_assert(sizeof(int)==sizeof(float),
                  "sizes of int and float need to be equal!\n");
    assert((bool)(*this));
    long n=this->size(), one=1, zero=0;
    scopy_(&n,reinterpret_cast<float*>(const_cast<int*>(&D)),&zero,
              reinterpret_cast<float*>(this->head()),&one);
    return *this;
  }

  template <>
  void Array<int,ArrayFormat::LongDataArray>::copy(
      const Array<int,ArrayFormat::LongDataArray>& A, unsigned int num,
      unsigned int bg, unsigned int dlt, unsigned int bgA, unsigned int dltA) {
    static_assert(sizeof(int)==sizeof(float),
                  "sizes of int and float need to be equal!\n");
    assert((bool)(*this));
    assert((bool)A);
    assert(bg+num*dlt<=this->size());
    assert(bgA+num*dltA<=A.size());
    long n=num, d1=dltA, d2=dlt;
    scopy_(&n,reinterpret_cast<float*>(A.head())+bgA,&d1,
              reinterpret_cast<float*>(this->head()),&d2);
  }

  template <>
  void Array<int,ArrayFormat::LongDataArray>::fill(
      const int& D, unsigned int bg, unsigned int dlt) {
    static_assert(sizeof(int)==sizeof(float),
                  "sizes of int and float need to be equal!\n");
    assert((bool)(*this));
    long n=(this->size()-bg)/dlt+((this->size()-bg)%dlt>0?1:0),
         zero=0, d=dlt;
    scopy_(&n,reinterpret_cast<float*>(const_cast<int*>(&D)),&zero,
              reinterpret_cast<float*>(this->head())+bg,&d);
  }

  template <>
  Array<double,ArrayFormat::LongDataArray>&
  Array<double,ArrayFormat::LongDataArray>::operator=(
      const Array<double,ArrayFormat::LongDataArray>& A) {
    assert((bool)(*this));
    assert((bool)A);
    assert(this->size()<=A.size());
    long n=this->size(), one=1;
    dcopy_(&n,A.head(),&one,this->head(),&one);
    return *this;
  }

  template <>
  Array<double,ArrayFormat::LongDataArray>&
  Array<double,ArrayFormat::LongDataArray>::operator=(const double& D) {
    assert((bool)(*this));
    long n=this->size(), one=1, zero=0;
    dcopy_(&n,const_cast<double*>(&D),&zero,this->head(),&one);
    return *this;
  }

}

#endif

