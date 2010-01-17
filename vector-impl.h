
/**
 * @file vector-impl.h
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
  
  /**
   * @brief shift a vector with generic type of objects
   *
   * Just pop up an error to disable this function. For some specific types
   * of objects, this  function is overloaded. This function is for the
   * generic types.
   *
   * \a T
   *    The type of the data in vector.
   *
   * \a ScaleT
   *    The type of the object to scale the input vector.
   *
   * @param [in,out] v
   *        The vector to be shifted. The result after shift operation
   *        is also stored in this array.
   *
   * @param [in] s
   *        The input object to scale the input vector sfv
   *
   * @param [in] sfv
   *        The input array to be scaled.
   *
   * @param [in] nshift
   *        The number of elements related to the shift operation
   *
   * @param [in] offset
   *        The starting place in vector v for shift operation.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] soffset
   *        The starting place in object s. This is valid when s is
   *        an array or vector-like object. Otherwise, this is useless.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] sfoffset
   *        The starting place in vector sfv to be scaled. Defaultly,
   *        it starts from head (the first element).
   *
   * @param [in] step
   *        The spacing between elements in vector v to be shifted.
   *        Defaultly, there are no spacing (step is one)
   *
   * @param [in] sstep
   *        The spacing between elements in object s. This is valid when s
   *        is an array or vector-like object. Otherwise, this is useless.
   *        Defaultly, there are no spacing (step is one).
   *
   * @param [in] sfstep
   *        The spacing between elements in vector sfv to be scaled.
   *        Defaultly, there are no spacing (step is one).
   */
  template <typename T, typename ScaleT>
  void vector_shift(T* v, const ScaleT& s, const T* sfv, long nshift,
                    int offset=iZero, int soffset=iZero, int sfoffset=iZero,
                    long step=lOne, long sstep=lOne, long sfstep=lOne) {
    myError("Shift for generic type is not available!");
  }

  /**
   * @brief shift a vector with \c double data with another vector scaled by a \c double constant
   *
   * This function is implemented with BLAS daxpy_() operation. The element
   * in the input vector sfv is scaled with the constant s, and is then added
   * to the corresponding element in vector v. The parameter soffset and
   * sstep are checked to avoid side-effects.
   *
   * @param [in,out] v
   *        The vector to be shifted. The result after shift operation
   *        is also stored in this array.
   *
   * @param [in] s
   *        The input \c double constant to scale the input vector sfv
   *
   * @param [in] sfv
   *        The input array to be scaled.
   *
   * @param [in] nshift
   *        The number of elements related to the shift operation
   *
   * @param [in] offset
   *        The starting place in vector v for shift operation.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] soffset
   *        The starting place in object s. This is valid when s is
   *        an array or vector-like object. Otherwise, this is useless.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] sfoffset
   *        The starting place in vector sfv to be scaled. Defaultly,
   *        it starts from head (the first element).
   *
   * @param [in] step
   *        The spacing between elements in vector v to be shifted.
   *        Defaultly, there are no spacing (step is one)
   *
   * @param [in] sstep
   *        The spacing between elements in object s. This is valid when s
   *        is an array or vector-like object. Otherwise, this is useless.
   *        Defaultly, there are no spacing (step is one).
   *
   * @param [in] sfstep
   *        The spacing between elements in vector sfv to be scaled.
   *        Defaultly, there are no spacing (step is one).
   */
  void vector_shift(double* v, const double& s, const double* sfv, long nshift,
                    int offset=iZero, int soffset=iZero, int sfoffset=iZero,
                    long step=lOne, long sstep=lZero, long sfstep=lOne) {
    assert((soffset==iZero)&&(sstep==lZero));
    daxpy_(&nshift,const_cast<double*>(&s),const_cast<double*>(sfv)+sfoffset,
           &sfstep,v+offset,&step);
  }

  /**
   * @brief shift a vector with \c int data with another vector scaled by a \c int constant
   *
   * This function is implemented by shift each element one by one. The element
   * in the input vector sfv is scaled with the constant s, and is then added
   * to the corresponding element in vector v. The parameter soffset and
   * sstep are checked to avoid side-effects.
   *
   * @param [in,out] v
   *        The vector to be shifted. The result after shift operation
   *        is also stored in this array.
   *
   * @param [in] s
   *        The input \c int constant to scale the input vector sfv
   *
   * @param [in] sfv
   *        The input array to be scaled.
   *
   * @param [in] nshift
   *        The number of elements related to the shift operation
   *
   * @param [in] offset
   *        The starting place in vector v for shift operation.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] soffset
   *        The starting place in object s. This is valid when s is
   *        an array or vector-like object. Otherwise, this is useless.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] sfoffset
   *        The starting place in vector sfv to be scaled. Defaultly,
   *        it starts from head (the first element).
   *
   * @param [in] step
   *        The spacing between elements in vector v to be shifted.
   *        Defaultly, there are no spacing (step is one)
   *
   * @param [in] sstep
   *        The spacing between elements in object s. This is valid when s
   *        is an array or vector-like object. Otherwise, this is useless.
   *        Defaultly, there are no spacing (step is one).
   *
   * @param [in] sfstep
   *        The spacing between elements in vector sfv to be scaled.
   *        Defaultly, there are no spacing (step is one).
   */
  void vector_shift(uint* v, const uint& s, const uint* sfv, long nshift,
                    int offset=iZero, int soffset=iZero, int sfoffset=iZero,
                    long step=lOne, long sstep=lZero, long sfstep=lOne) {
    assert((soffset==iZero)&&(sstep==lZero));
    for(int i=0,iv=offset,ifv=sfoffset;i<nshift;++i,iv+=step,ifv+=sfstep)
      v[iv]+=s*sfv[ifv];
  }

  /**
   * @brief shift a vector with \c int data with another vector scaled by a vector
   *
   * This function is implemented by shift each element one by one. The element
   * in the input vector sfv is scaled with the element in array s, and is
   * then added to the corresponding element in vector v.
   *
   * @param [in,out] v
   *        The vector to be shifted. The result after shift operation
   *        is also stored in this array.
   *
   * @param [in] s
   *        The input vector to scale the input vector sfv
   *
   * @param [in] sfv
   *        The input array to be scaled.
   *
   * @param [in] nshift
   *        The number of elements related to the shift operation
   *
   * @param [in] offset
   *        The starting place in vector v for shift operation.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] soffset
   *        The starting place in object s. This is valid when s is
   *        an array or vector-like object. Otherwise, this is useless.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] sfoffset
   *        The starting place in vector sfv to be scaled. Defaultly,
   *        it starts from head (the first element).
   *
   * @param [in] step
   *        The spacing between elements in vector v to be shifted.
   *        Defaultly, there are no spacing (step is one)
   *
   * @param [in] sstep
   *        The spacing between elements in object s. This is valid when s
   *        is an array or vector-like object. Otherwise, this is useless.
   *        Defaultly, there are no spacing (step is one).
   *
   * @param [in] sfstep
   *        The spacing between elements in vector sfv to be scaled.
   *        Defaultly, there are no spacing (step is one).
   */
  void vector_shift(uint* v, const uint* s, const uint* sfv, long nshift,
                    int offset=iZero, int soffset=iZero, int sfoffset=iZero,
                    long step=lOne, long sstep=lZero, long sfstep=lOne) {
    for(int i=0,iv=offset,isv=soffset,ifv=sfoffset;i<nshift;
        ++i,iv+=step,isv+=sstep,ifv+=sfstep)
      v[iv]+=s[isv]*sfv[ifv];
  }

  /**
   * @brief composite operation of scale and shift for generic type of data
   *
   * Just pop up an error to disable this function. For some specific types
   * of objects, this function is overloaded. This function is for the
   * generic types.
   *
   * \a T
   *    The type of the data in array
   *
   * @param [in,out] v
   *        The array to be operated. The result after scale and shift
   *        operations is stored in this array.
   *
   * @param [in] s
   *        The input constant to scale the array v
   *
   * @param [in] sf
   *        The input constant to scale the array sv
   *
   * @param [in] sfv
   *        The input array as the scale factor for array sv
   *
   * @param [in] sv
   *        The input array to be scaled
   *
   * @param [in] nscaleshift
   *        The number of elements to be operated.
   *
   * @param [in] offset
   *        The starting place in vector v for the composite operation.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] sfoffset
   *        The starting place in vector sfv related to scale operation.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] soffset
   *        The starting place in vector sv related to scale operation.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] step
   *        The spacing between elements in vector v to be operated.
   *        Defaultly, there are no spacing (step is one)
   *
   * @param [in] sfstep
   *        The spacing between elements in vector sfv in scale operation.
   *        Defaultly, there are no spacing (step is one).
   *
   * @param [in] sstep
   *        The spacing between elements in vector sv related to scale
   *        operation. Defaultly, there are no spacing (step is one).
   */
  template <typename T>
  void vector_scaleshift(T* v, const T& s, const T& sf, const T* sfv,
                         const T* sv, long nscaleshift, int offset=iZero,
                         int sfoffset=iZero, int soffset=iZero,
                         long step=lOne, long sfstep=lOne, long sstep=lOne) {
    myError("Scaled Shift for generic type is not available!");
  }
  
  /**
   * @brief composite operation of scale and shift for \c double type of data
   *
   * This function is implemented with BLAS dsbmv_() operation. The vector
   * sv is scaled with the constant sf and the vector sfv, and the vector v
   * is scaled with the constant s. The resultant two vectors are added
   * together and the result is stored in the vector v.
   *
   * @param [in,out] v
   *        The array to be operated. The result after scale and shift
   *        operations is stored in this array.
   *
   * @param [in] s
   *        The input constant to scale the array v
   *
   * @param [in] sf
   *        The input constant to scale the array sv
   *
   * @param [in] sfv
   *        The input array as the scale factor for array sv
   *
   * @param [in] sv
   *        The input array to be scaled
   *
   * @param [in] nscaleshift
   *        The number of elements to be operated.
   *
   * @param [in] offset
   *        The starting place in vector v for the composite operation.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] sfoffset
   *        The starting place in vector sfv related to scale operation.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] soffset
   *        The starting place in vector sv related to scale operation.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] step
   *        The spacing between elements in vector v to be operated.
   *        Defaultly, there are no spacing (step is one)
   *
   * @param [in] sfstep
   *        The spacing between elements in vector sfv in scale operation.
   *        Defaultly, there are no spacing (step is one).
   *
   * @param [in] sstep
   *        The spacing between elements in vector sv related to scale
   *        operation. Defaultly, there are no spacing (step is one).
   */
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

  /**
   * @brief swap the content of two arrays with generic type of data
   *
   * The elements in two input arrays are swapped one by one. This is
   * valid for generic type of data.
   *
   * \a T
   *    The type of data in vector
   *
   * @param [in,out] va
   *        An array to be swapped
   *
   * @param [in,out] vb
   *        Another array to be swapped
   *
   * @param [in] nswap
   *        The number of elements to be swapped.
   *
   * @param [in] aoffset
   *        The starting place in array va related to swap operation.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] astep
   *        The spacing between elements in array va related to swap
   *        operation. Defaultly, there are no spacing (step is one).
   *
   * @param [in] boffset
   *        The starting place in array vb related to swap operation.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] bstep
   *        The spacing between elements in array vb related to swap
   *        operation. Defaultly, there are no spacing (step is one).
   */
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

  /**
   * @brief swap the content of two arrays with \c double type of data
   *
   * It is implemented with dswap_() operation. The contents are swapped.
   *
   * @param [in,out] va
   *        An array to be swapped
   *
   * @param [in,out] vb
   *        Another array to be swapped
   *
   * @param [in] nswap
   *        The number of elements to be swapped.
   *
   * @param [in] aoffset
   *        The starting place in array va related to swap operation.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] astep
   *        The spacing between elements in array va related to swap
   *        operation. Defaultly, there are no spacing (step is one).
   *
   * @param [in] boffset
   *        The starting place in array vb related to swap operation.
   *        Defaultly, it starts from head (the first element).
   *
   * @param [in] bstep
   *        The spacing between elements in array vb related to swap
   *        operation. Defaultly, there are no spacing (step is one).
   */
  void vector_swap(double* va, double* vb, long nswap,
                   int aoffset=iZero, int boffset=iZero,
                   long astep=lOne, long bstep=lOne) {
    dswap_(&nswap,va+aoffset,&astep,vb+boffset,&bstep);
  }

}

#endif
