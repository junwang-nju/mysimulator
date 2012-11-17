
#ifndef _Array_2D_Interface_H_
#define _Array_2D_Interface_H_

#include "array/interface.h"

namespace mysimulator {

  template <typename,ArrayKernelName,ArrayKernelName> class Array2D;

  template <typename T,ArrayKernelName DK,ArrayKernelName LK>
  void
  __allocate_2d(Array2D<T,DK,LK>& A,unsigned int n, unsigned int dim) {
    fprintf(stderr,"Not Implemented for these kernels!\n");
  }

  template <typename T,ArrayKernelName DK,ArrayKernelName LK,
            typename Y,ArrayKernelName YK>
  void
  __allocate_2d(Array2D<T,DK,LK>& A, Array<Intrinsic<Y>,YK> const SZ) {
    fprintf(stderr,"Not Implemented for these kernels!\n");
  }

  template <typename T,ArrayKernelName DKernel=ArrayKernelName::Simple,
                       ArrayKernelName LKernel=ArrayKernelName::Simple>
  class Array2D : protected Array<T,DKernel>, public Array<Array<T,LKernel>> {

    public:

      typedef Array2D<T,DKernel,LKernel>    Type;
      typedef Array<T,DKernel>              ParentTypeA;
      typedef Array<T,LKernel>              LineType;
      typedef Array<LineType>               ParentTypeB;
      typedef unsigned int size_type;

      friend void __allocate_2d<T,DKernel,LKernel>(Type&,size_type,size_type);

      Array2D() : ParentTypeA(), ParentTypeB() {}
      Array2D(size_type n,size_type dim) : Array2D() { allocate(n,dim); }
      Array2D(const Type& A) : Array2D() { imprint(A); operator=(A); }
      Array2D(Type&& A) : Array2D() { swap(A); }
      ~Array2D() { reset(); }

      operator bool() const {
        return ParentTypeA::operator bool() && ParentTypeB::operator bool();
      }
      size_type size() const { return ParentTypeB::size(); }
      LineType operator[](size_type i) { return ParentTypeB::operator[](i); }
      LineType const& operator[](size_type i) const {
        return ParentTypeB::operator[](i);
      }
      template <typename Y,ArrayKernelName DKY,ArrayKernelName LKY>
      bool isSame(Array2D<Y,DKY,LKY>& A) const {
        if(size()!=A.size())  return false;
        for(size_type i=0;i<size();++i)
          if((*this)[i].size()!=A[i].size())  return false;
        return true;
      }
      void reset() { ParentTypeB::reset(); ParentTypeA::reset(); }

      void allocate(size_type n, size_type dim) { __allocate_2d(*this,n,dim); }
      template <typename Y,ArrayKernelName YK>
      void allocate(Array<Intrinsic<Y>,YK> const& Z) { __allocate_2d(*this,Z); }
      template <ArrayKernelName DK,ArrayKernelName LK>
      void imprint(Array2D<T,DK,LK> const& A) {
        assert((bool)A);
        Array<UInt> SZ(A.size());
        for(size_type i=0;i<SZ.size();++i)  SZ[i]=A[i].size();
        allocate(SZ);
        SZ.reset();
      }

  };

  template <typename T>
  void
  __allocate_2d(Array2D<T,ArrayKernelName::Simple,ArrayKernelName::Simple>& A,
                unsigned int n,unsigned int dim) {
    ((Array<T,ArrayKernelName::Simple>&)A).allocate(n*dim);
    ((Array<Array<T,ArrayKernelName::Simple>>&)A).allocate(n);
    for(unsigned int i=0,w=0;i<n;w+=dim,++i)
      A[i].refer((Array<T,ArrayKernelName::Simple> const&)A,w,dim);
  }

  template <typename T,typename Y,ArrayKernelName YK>
  void
  __allocate_2d(Array2D<T,ArrayKernelName::Simple,ArrayKernelName::Simple>& A,
                Array<Intrinsic<Y>,YK> const& SZ) {
    static_assert(Intrinsic<Y>::IsInteger,
                  "Only Integer permitted as size of allocation!\n");
    assert((bool)SZ);
  }
}

#endif

