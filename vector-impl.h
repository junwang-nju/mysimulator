
/**
 * @file vector-impl.cc
 * @brief Implementation for vector-related operations
 *
 * As an interface between background procedures (such as BLAS which
 * is not in C++ style) and vector infra-structure, these procedures
 * ease the invocation and convention of type matching. For different
 * kinds of data, different internal implementations are used. These
 * procedures hide the inner complexity, and ease the generic programming.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Vector_Implementation_CC_
#define _Vector_Implementation_CC_

#include "constant.h"
#include "blas.h"
#include "error-proc.h"
#include <cassert>
#include <cstring>

namespace std {

  /**
   * @brief assign a vector with data of generic type from another
   *
   * This procedure assigns the data one by one from one vector
   * to another. This is safest method, but it may lose some
   * efficiency. This function is for values with generic type.
   * For some specific types, this method is overloaded for
   * efficiency.
   *
   * @see vector_assign(double* v, const double* iv, long ncopy,
   *                    int offset=iZero, int ioffset=iZero,
   *                    long step=lOne, long istep=lOne)
   *
   * \a T
   *    The type for data in vectors
   *
   * @param [out] v
   *        The destination array (vector) storing data for output
   *
   * @param [in] iv
   *        The source array (vector) storing input data
   *
   * @param [in] ncopy
   *        The number of elements to be copied
   *
   * @param [in] offset
   *        The starting place in vector v for assignment operation.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] ioffset
   *        The starting place in vector iv for assignment operation.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] step
   *        The spacing between elements in vector v during assignment.
   *        Defaultly, there are no spacing (step is one)
   *
   * @param [in] istep
   *        The spacing between elements in vector iv during assignment.
   *        Defaultly, there are no spacing (step is one)
   */
  template <typename T>
  void vector_assign(T* v, const T* iv, long ncopy,
                     int offset=iZero,int ioffset=iZero,
                     long step=lOne, long istep=lOne) {
    T* optr=v+offset;
    T* iptr=const_cast<T*>(iv)+ioffset;
    for(int i=0;i<ncopy;++i) {
      *optr=*iptr;
      optr+=step;
      iptr+=istep;
    }
  }
  
  /**
   * @brief assign a vector with \c double type data from another
   *
   * The assignment of vectors with \c double type data is implemented
   * with BLAS procedure dcopy_(). For large arraies, this method
   * would be faster. This function is for \c double type data.
   *
   * @see vector_assign<T>(T* v, const T* iv, long ncopy,
   *                       int offset=iZero,int ioffset=iZero,
   *                        long step=lOne, long istep=lOne)
   *
   * @param [out] v
   *        The destination array (vector) storing data for output
   *
   * @param [in] iv
   *        The source array (vector) storing input data
   *
   * @param [in] ncopy
   *        The number of elements to be copied
   *
   * @param [in] offset
   *        The starting place in vector v for assignment operation.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] ioffset
   *        The starting place in vector iv for assignment operation.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] step
   *        The spacing between elements in vector v during assignment.
   *        Defaultly, there are no spacing (step is one)
   *
   * @param [in] istep
   *        The spacing between elements in vector iv during assignment.
   *        Defaultly, there are no spacing (step is one)
   *
   * @todo Check how large the dimension of arrays should be to achieve
   *       a faster running with BLAS.
   */
  void vector_assign(double* v, const double* iv, long ncopy,
                     int offset=iZero, int ioffset=iZero,
                     long step=lOne, long istep=lOne) {
    dcopy_(&ncopy,const_cast<double*>(iv)+ioffset,&istep,v+offset,&step);
  }
  
  /**
   * @brief scale a vector with a generic type quantity
   *
   * Just pop up an error to disable this function. For some specific
   * type of value for scaling, this function is overloaded. This
   * function is for generic types.
   *
   * @see vector_scale(double* v, const double& d, long nscale,
   *                   int offset=iZero, int soffset=iZero,
   *                   long step=lOne, long sstep=lZero)
   * @see vector_scale(double* v, const double* sv, long nscale,
   *                   int offset=iZero, int soffset=iZero,
   *                   long step=lOne, long sstep=lOne)
   *
   * \a T
   *    The type for the data in vector
   *
   * \a ScaleT
   *    The type of the quantity to scale the vector
   *
   * @param [in,out] v
   *        The vector to be scaled
   *
   * @param [in] s
   *        The quantity to scale the vector v
   *
   * @param [in] nscale
   *        The number of elements to be scaled in vector v
   *
   * @param [in] offset
   *        The starting place in vector v for scale operation.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] soffset
   *        The starting place in object s for scale operation.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] step
   *        The spacing between elements in vector v to be scaled.
   *        Defaultly, there are no spacing (step is one)
   *
   * @param [in] sstep
   *        The spacing between elements in object s.
   *        Defaultly, there are no spacing (step is one)
   *
   * @note This function could be omitted. Therefore, when improper
   *       objects are used, the compiler may pop up an error. Now,
   *       the error would be observed in run time.
   * @note Since scale operation only works for numerical data type,
   *       thus there are no implementations for generic types.
   */
  template <typename T, typename ScaleT>
  void vector_scale(T* v, const ScaleT& s, long nscale,
                    int offset=iZero, int soffset=iZero,
                    long step=lOne, long sstep=lOne) {
    myError("Scale for generic type is not available!");
  }

  /**
   * @brief scale a vector with \c double data with a \c double constant
   *
   * This operation is implemented with BLAS procedure dscal_(). The
   * input parameters for constant are checked for consistence. This
   * kind of implementation would be faster for large arrays. This
   * function is for \c double type data.
   *
   * @see vector_scale<T,ScaleT>(T* v, const ScaleT& s, long nscale,
   *                             int offset=iZero, int soffset=iZero,
   *                             long step=lOne, long sstep=lOne)
   * @see vector_scale(double* v, const double* sv, long nscale,
   *                   int offset=iZero, int soffset=iZero,
   *                   long step=lOne, long sstep=lOne)
   *
   * @param [in,out] v
   *        The vector to be scaled
   *
   * @param [in] d
   *        The \c double type constant to scale the vector v
   *
   * @param [in] nscale
   *        The number of elements to be scaled in vector v
   *
   * @param [in] offset
   *        The starting place in vector v for scale operation.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] soffset
   *        The starting place in object d for scale operation.
   *        To be consistent with constant type, it should be zero.
   *
   * @param [in] step
   *        The spacing between elements in vector v to be scaled.
   *        Defaultly, there are no spacing (step is one)
   *
   * @param [in] sstep
   *        The spacing between elements in object d.
   *        To be consistent with constant type, it should be zero.
   *
   * @brief The inclusion of two parameters for constant is to match
   *        the general format of the function, which eases the generic
   *        programming
   *
   * @todo Check how large the dimension of arrays should be to achieve
   *       a faster running with BLAS.
   */
  void vector_scale(double* v, const double& d, long nscale,
                    int offset=iZero, int soffset=iZero,
                    long step=lOne, long sstep=lZero) {
    assert((soffset==iZero)&&(sstep==lZero));
    dscal_(&nscale,const_cast<double*>(&d),v+offset,&step);
  }

  /**
   * @brief scale a vector with \c double data with another vector
   *
   * The scale operation with a vector is to scale each element
   * with different factors in another vector. This operation is
   * implemented with BLAS procedure dtbmv_(). The
   * input vector is used as a diagonal matrix for the procedure.
   * kind of implementation would be faster for large arrays. This
   * function is for \c double type data.
   *
   * @see vector_scale<T,ScaleT>(T* v, const ScaleT& s, long nscale,
   *                             int offset=iZero, int soffset=iZero,
   *                             long step=lOne, long sstep=lOne)
   * @see vector_scale(double* v, const double& d, long nscale,
   *                   int offset=iZero, int soffset=iZero,
   *                   long step=lOne, long sstep=lZero)
   *
   * @param [in,out] v
   *        The vector to be scaled
   *
   * @param [in] sv
   *        The vector to scale the vector v
   *
   * @param [in] nscale
   *        The number of elements to be scaled in vector v
   *
   * @param [in] offset
   *        The starting place in vector v for scale operation.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] soffset
   *        The starting place in vector sv for scale operation.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] step
   *        The spacing between elements in vector v to be scaled.
   *        Defaultly, there are no spacing (step is one)
   *
   * @param [in] sstep
   *        The spacing between elements in vector sv to scale vector v.
   *        Defaultly, there are no spacing (step is one)
   *
   * @todo Check how large the dimension of arrays should be to achieve
   *       a faster running with BLAS.
   */
  void vector_scale(double* v, const double* sv, long nscale,
                    int offset=iZero, int soffset=iZero,
                    long step=lOne, long sstep=lOne) {
    static char flag[]="LNN";
    dtbmv_(flag,flag+1,flag+2,&nscale,&lZero,
           const_cast<double*>(sv)+soffset,&sstep,v+offset,&step);
  }
  
  template <typename T, typename ScaleT>
  void vector_shift(T* v, const ScaleT& s, const T* sfv, long nshift,
                    int offset=iZero, int soffset=iZero, int sfoffset=iZero,
                    long step=lOne, long sstep=lOne, long sfstep=lOne) {
    myError("Shift for generic type is not available!");
  }

  void vector_shift(double* v, const double& s, const double* sfv, long nshift,
                    int offset=iZero, int soffset=iZero, int sfoffset=iZero,
                    long step=lOne, long sstep=lZero, long sfstep=lOne) {
    assert((soffset==iZero)&&(sstep==lZero));
    daxpy_(&nshift,const_cast<double*>(&s),const_cast<double*>(sfv)+sfoffset,
           &sfstep,v+offset,&step);
  }

  void vector_shift(uint* v, const uint& s, const uint* sfv, long nshift,
                    int offset=iZero, int soffset=iZero, int sfoffset=iZero,
                    long step=lOne, long sstep=lZero, long sfstep=lOne) {
    assert((soffset==iZero)&&(sstep==lZero));
    for(int i=0,iv=offset,ifv=sfoffset;i<nshift;++i,iv+=step,ifv+=sfstep)
      v[iv]+=s*sfv[ifv];
  }

  void vector_shift(uint* v, const uint* s, const uint* sfv, long nshift,
                    int offset=iZero, int soffset=iZero, int sfoffset=iZero,
                    long step=lOne, long sstep=lZero, long sfstep=lOne) {
    for(int i=0,iv=offset,isv=soffset,ifv=sfoffset;i<nshift;
        ++i,iv+=step,isv+=sstep,ifv+=sfstep)
      v[iv]+=s[isv]*sfv[ifv];
  }

  template <typename T>
  void vector_scaleshift(T* v, const T& s, const T& sf, const T* sfv,
                         const T* sv, long nscaleshift, int offset=iZero,
                         int sfoffset=iZero, int soffset=iZero,
                         long step=lOne, long sfstep=lOne, long sstep=lOne) {
    myError("Scaled Shift for generic type is not available!");
  }
  
  void vector_scaleshift(double* v, const double& s, const double& sf,
                         const double* sfv, const double* sv, long nscaleshift,
                         int offset=iZero, int sfoffset=iZero,
                         int soffset=iZero, long step=lOne,
                         long sfstep=lOne, long sstep=lOne) {
    static char flag[]="L";
    dsbmv_(flag,&nscaleshift,&lZero,const_cast<double*>(&sf),
           const_cast<double*>(sfv)+sfoffset,&sfstep,
           const_cast<double*>(sv)+soffset,&sstep,const_cast<double*>(&s),
           v+offset,&step);
  }

  template <typename T>
  void vector_swap(T* va, T* vb, long nswap,
                   int aoffset=iZero, long astep=lOne,
                   int boffset=iZero, long bstep=lOne) {
    T tmT, *pa, *pb;
    pa=va+aoffset;
    pb=vb+boffset;
    for(int i=0;i<nswap;++i) {
      tmT=*pa;    *pa=*pb;    *pb=tmT;
      pa+=astep;
      pb+=bstep;
    }
  }

  void vector_swap(double* va, double* vb, long nswap,
                   int aoffset=iZero, int boffset=iZero,
                   long astep=lOne, long bstep=lOne) {
    dswap_(&nswap,va+aoffset,&astep,vb+boffset,&bstep);
  }

}

#endif
