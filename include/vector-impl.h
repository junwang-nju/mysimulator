
/**
 * @file vector-impl.h
 * @brief procedures related to array operation for vector object
 *
 * This file contains a series of procedures to operate arrays. These
 * procedures are used as implementations of vector operation.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Vector_Implementation_H_
#define _Vector_Implementation_H_

#include "constant.h"
#include "blas.h"
#include "memory.h"
#include "util.h"
#include <cassert>
#include <cstdlib>

namespace std {

  /**
   * @brief allocate a pointer pointing to a number of elements
   *
   * This is a wrapper for classical allocation (new operator). Several
   * checks are carried out for memory management.
   * The pointer is required to be NULL before allocation to avoid to
   * overwite existent storage (namely leak of memory). The input
   * expected number of elements is also required to be larger than
   * zero, which makes the allocation is not trivial. Then the allocation
   * is implementated with new operator.
   *
   * T is the type of data pointed by the concerned pointer.
   *
   * @param dest [in,out] the reference to the pointer to T-type data
   * @param N [in] the expected number of elements
   * @return nothing
   */
  template <typename T>
  inline void allocate(T* &dest, const unsigned int N) {
    assert(dest==NULL);
    if(N==0)  return;
    dest=new T[N];
  }

  /**
   * @brief release storage pointed by a pointer
   *
   * This is implementated by the function safe_delete_array for pointer
   * to some storage. The resultant pointer would have the value NULL.
   *
   *  T is the type of data pointed by the input pointer.
   *
   * @param dest [in,out] the pointer of storage to be freed.
   * @return nothing
   */
  template <typename T>
  inline void release(T* &dest) { safe_delete_array(dest); }

  /**
   * @brief assign an array from another array with offsets and steps
   *
   * This is a generic form of assign operation. The elements in the
   * source array src are copied into the destination array dest one by one.
   * The copy action is started from the elements indicated by offsets,
   * and the neighboring elements have the separation of steps. Before
   * this operation, the availability of the concerned pointers are checked
   * at first.
   *
   * T is the type of data in the arrays.
   *
   * @param dest [out] the pointer to the array storing data after copy
   * @param src [in] the pointer to the array storing data used for copy
   * @param ncopy [in] the number of elements involved in copy operation
   * @param soff,doff [in] the offsets indicating the first elements in
   *                       array src and dest. They take the default value
   *                       iZero.
   * @param sstep,dstep [in] the separations between neighbor elements used
   *                         for copy action in array src and dest.  They
   *                         takes the default value lOne.
   * @return nothing.
   */
  template <typename T>
  inline void assign(T* dest, const T* src, const long ncopy,
              const int soff=iZero, const long sstep=lOne,
              const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    assert(src!=NULL);
    T* dPtr=dest+doff, *sPtr=const_cast<T*>(src)+soff;
    for(unsigned int i=0;i<static_cast<unsigned int>(ncopy);++i,++dPtr,++sPtr)
      *dPtr=*sPtr;
  }

  /**
   * @brief copy \c double array with offsets and steps.
   *
   * It is implementated with BLAS function dcopy_. The pointers
   * of input and output arrays are checked for their availability
   * before this operation.
   *
   * @param dest [out] the \c double array to accept input
   * @param src [in] the \c double array containing the input
   * @param ncopy [in] the number of elements to be copied
   * @param soff,doff [in] the offsets indicating the first elements in
   *                       array src and dest. They take the default value
   *                       iZero.
   * @param sstep,dstep [in] the separations between neighbor elements used
   *                         for copy action in array src and dest.  They
   *                         takes the default value lOne.
   * @return nothing.
   * @todo the comparison between efficiency of this procedure and the generic
   *       procedure is needed.
   */
  inline void assign(double* dest, const double* src, const long ncopy,
              const int soff=iZero, const long sstep=lOne,
              const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    assert(src!=NULL);
    dcopy_(const_cast<long*>(&ncopy),const_cast<double*>(src)+soff,
           const_cast<long*>(&sstep),dest+doff,const_cast<long*>(&dstep));
  }

  /**
   * @brief copy \c int array with offsets and steps.
   *
   * It is implementated with BLAS function scopy_. The pointers
   * of input and output arrays are checked for their availability
   * before this operation. The compatibility of the sizes of
   * the \c int data and the internal \c float format is also checked.
   *
   * @param dest [out] the \c int array to accept input
   * @param src [in] the \c int array containing the input
   * @param ncopy [in] the number of elements to be copied
   * @param soff,doff [in] the offsets indicating the first elements in
   *                       array src and dest. They take the default value
   *                       iZero.
   * @param sstep,dstep [in] the separations between neighbor elements used
   *                         for copy action in array src and dest.  They
   *                         takes the default value lOne.
   * @return nothing.
   * @todo the comparison between efficiency of this procedure and the generic
   *       procedure is needed.
   */
  inline void assign(int* dest, const int* src, const long ncopy,
              const int soff=iZero, const long sstep=lOne,
              const int doff=iZero, const long dstep=lOne) {
    assert(sizeof(float)==sizeof(int));
    assert(dest!=NULL);
    assert(src!=NULL);
    scopy_(const_cast<long*>(&ncopy),
           reinterpret_cast<float*>(const_cast<int*>(src))+soff,
           const_cast<long*>(&sstep),
           reinterpret_cast<float*>(dest)+doff,const_cast<long*>(&dstep));
  }

  /**
   * @brief copy \c unsigned \c int array with offsets and steps.
   *
   * It is implementated with BLAS function scopy_. The pointers
   * of input and output arrays are checked for their availability
   * before this operation. The compatibility of the sizes of
   * the \c unsigned \c int data and the internal \c float format is
   * also checked.
   *
   * @param dest [out] the \c unsigned \c int array to accept input
   * @param src [in] the \c unsigned \c int array containing the input
   * @param ncopy [in] the number of elements to be copied
   * @param soff,doff [in] the offsets indicating the first elements in
   *                       array src and dest. They take the default value
   *                       iZero.
   * @param sstep,dstep [in] the separations between neighbor elements used
   *                         for copy action in array src and dest.  They
   *                         takes the default value lOne.
   * @return nothing.
   * @todo the comparison between efficiency of this procedure and the generic
   *       procedure is needed.
   */
  inline void assign(unsigned int* dest, const unsigned int* src,
                     const long ncopy,
                     const int soff=iZero, const long sstep=lOne,
                     const int doff=iZero, const long dstep=lOne) {
    assert(sizeof(unsigned int)==sizeof(float));
    assert(dest!=NULL);
    assert(src!=NULL);
    scopy_(const_cast<long*>(&ncopy),
           reinterpret_cast<float*>(const_cast<unsigned int*>(src))+soff,
           const_cast<long*>(&sstep),reinterpret_cast<float*>(dest)+doff,
           const_cast<long*>(&dstep));
  }

  /**
   * @brief copy a constant to an array with offset and step
   *
   * It is implementated with the assign operation between arrays.
   *
   * T is the type of the input data
   *
   * @param dest [out] the array to accept input
   * @param value [in] the input constant
   * @param ncopy [in] the number of elements to be copied
   * @param doff [in] the offset of the first element in array dest.
   *                  It takes the default value iZero
   * @param dstep [in] the separation between the used elements in array dest.
   *                   It takes the default value lOne.
   * @return nothing
   */
  template <typename T>
  inline void assign(T* dest, const T& value, const long ncopy,
                     const int doff=iZero, const long dstep=lOne) {
    assign(dest,&value,ncopy,iZero,lZero,doff,dstep);
  }

  /**
   * @brief copy \c unsigned \c int constant to array with offset and step
   *
   * It is implementated with assign operation for \c unsigned \c int array.
   *
   * @param dest [out] the array to accept input
   * @param value [in] the input \c unsigned \c int constant
   * @param ncopy [in] the number of elements to be copied
   * @param doff [in] the offset of the first element in array dest.
   *                  It takes the default value iZero
   * @param dstep [in] the separation between the used elements in array dest.
   *                   It takes the default value lOne.
   * @return nothing
   * @note This interface is used to enable the input of \c unsigned \c int
   *       value (rather than the reference). This enables the implicit
   *       conversion of the input value.
   */
  inline void assign(unsigned int* dest, const unsigned int value,
                     const long ncopy, 
                     const int doff=iZero, const long dstep=lOne) {
    assign(dest,&value,ncopy,iZero,lZero,doff,dstep);
  }

  /**
   * @brief copy \c double constant to array with offset and step
   *
   * It is implementated with assign operation for \c double array.
   *
   * @param dest [out] the array to accept input
   * @param value [in] the input \c double constant
   * @param ncopy [in] the number of elements to be copied
   * @param doff [in] the offset of the first element in array dest.
   *                  It takes the default value iZero
   * @param dstep [in] the separation between the used elements in array dest.
   *                   It takes the default value lOne.
   * @return nothing
   * @note This interface is used to enable the input of \c double
   *       value (rather than the reference). This enables the implicit
   *       conversion of the input value.
   */
  inline void assign(double* dest, const double value, const long ncopy,
                     const int doff=iZero, const long dstep=lOne) {
    assign(dest,&value,ncopy,iZero,lZero,doff,dstep);
  }

  /**
   * @brief scale \c int array by a constant considering offset and step
   *
   * It is implemented by looping all the concerned elements in array.
   * The concerned array is checked for its availability before this operation.
   *
   * @param dest [in,out] the array to accept input
   * @param factor [in] the input \c int factor for scale operation
   * @param nscale [in] the number of elements to be scaled
   * @param doff [in] the offset of the first element in array dest.
   *                  It takes the default value iZero
   * @param dstep [in] the separation between the used elements in array dest.
   *                   It takes the default value lOne.
   * @return nothing
   */
  inline void scale(int* dest, const int factor, const long nscale,
                    const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    int *dPtr=dest+doff;
    for(unsigned int i=0;i<static_cast<unsigned int>(nscale);++i,dPtr+=dstep)
      *dPtr*=factor;
  }

  /**
   * @brief scale \c unsigned \c int array by a constant considering offset and step
   *
   * It is implemented by looping all the concerned elements in array.
   * The concerned array is checked for its availability before this operation.
   *
   * @param dest [in,out] the array to accept input
   * @param factor [in] the input \c unsigned \c int factor for scale operation
   * @param nscale [in] the number of elements to be scaled
   * @param doff [in] the offset of the first element in array dest.
   *                  It takes the default value iZero
   * @param dstep [in] the separation between the used elements in array dest.
   *                   It takes the default value lOne.
   * @return nothing
   */
  inline void scale(unsigned int* dest, const unsigned int factor,
                    const long nscale,
                    const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    unsigned int* dPtr=dest+doff;
    for(unsigned int i=0;i<static_cast<unsigned int>(nscale);++i,dPtr+=dstep)
      *dPtr*=factor;
  }

  /**
   * @brief scale \c double array by a constant considering offset and step
   *
   * It is implemented by dscale operation in BLAS.
   * The concerned array is checked for its availability before this operation.
   *
   * @param dest [in,out] the array to accept input
   * @param factor [in] the input \c double factor for scale operation
   * @param nscale [in] the number of elements to be scaled
   * @param doff [in] the offset of the first element in array dest.
   *                  It takes the default value iZero
   * @param dstep [in] the separation between the used elements in array dest.
   *                   It takes the default value lOne.
   * @return nothing
   */
  inline void scale(double* dest, const double factor, const long nscale,
                    const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    dscal_(const_cast<long*>(&nscale),const_cast<double*>(&factor),
           dest+doff,const_cast<long*>(&dstep));
  }

  /**
   * @brief scale \c int array by another \c int array offsets and steps
   *
   * It is implementated by looping over all the elements. The concerned
   * arrays are checked for their availability before this operation.
   *
   * @param dest [in,out] the array to be scaled
   * @param vfactor [in] the array containing the scale factor
   * @param nscale [in] the number of elements related to scale operation
   * @param voff, doff [in] the offsets of the first elements in arrays
   *                        vfactor and dest. They take the default value iZero
   * @param vstep, dstep [in] the separations between used elements in arrays
   *                          vfactor, dest. They take default value lOne.
   * @return nothing
   */
  inline void scale(int* dest, const int* vfactor,const long nscale,
             const int voff=iZero, const long vstep=lOne,
             const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    assert(vfactor!=NULL);
    int* dPtr=dest+doff, *vPtr=const_cast<int*>(vfactor)+voff;
    for(unsigned int i=0;i<static_cast<unsigned int>(nscale);
                     ++i,dPtr+=dstep,vPtr+=vstep)
      *dPtr*=*vPtr;
  }

  /**
   * @brief scale \c unsigned \c int array by another \c int array offsets and steps
   *
   * It is implementated by looping over all the elements. The concerned
   * arrays are checked for their availability before this operation.
   *
   * @param dest [in,out] the array to be scaled
   * @param vfactor [in] the array containing the scale factor
   * @param nscale [in] the number of elements related to scale operation
   * @param voff, doff [in] the offsets of the first elements in arrays
   *                        vfactor and dest. They take the default value iZero
   * @param vstep, dstep [in] the separations between used elements in arrays
   *                          vfactor, dest. They take default value lOne.
   * @return nothing
   */
  inline void scale(unsigned int* dest, const unsigned int* vfactor,
                    const long nscale,
                    const int voff=iZero, const long vstep=lOne,
                    const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    assert(vfactor!=NULL);
    unsigned int* dPtr=dest+doff,*vPtr=const_cast<unsigned int*>(vfactor)+voff;
    for(unsigned int i=0;i<static_cast<unsigned int>(nscale);
                     ++i,dPtr+=dstep,vPtr+=vstep)
      *dPtr*=*vPtr;
  }

  /**
   * @brief scale \c int array by another \c int array offsets and steps
   *
   * It is implementated by looping over all the elements. The concerned
   * arrays are checked for their availability before this operation.
   *
   * @param dest [in,out] the array to be scaled
   * @param vfactor [in] the array containing the scale factor
   * @param nscale [in] the number of elements related to scale operation
   * @param voff, doff [in] the offsets of the first elements in arrays
   *                        vfactor and dest. They take the default value iZero
   * @param vstep, dstep [in] the separations between used elements in arrays
   *                          vfactor, dest. They take default value lOne.
   * @return nothing
   */
  inline void scale(double* dest, const double* vfactor, const long nscale,
                    const int voff=iZero, const long vstep=lOne,
                    const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    assert(vfactor!=NULL);
    static char flag[]="LNN";
    dtbmv_(flag,flag+1,flag+2,const_cast<long*>(&nscale),
           const_cast<long*>(&lZero), const_cast<double*>(vfactor)+voff,
           const_cast<long*>(&vstep),dest+doff,const_cast<long*>(&dstep));
  }

  /**
   * @brief shift \c int array by constant and another array with offsets and steps
   *
   * It is implemented by looping over all the elements in arrays. The
   * concerned arrays are checked for their availability before this operation.
   *
   * @param dest [in,out] the array to be shifted
   * @param factor [in] the constant factor for shift operation.
   * @param vfactor [in] the array containing the factors for shift operation
   * @param nshift [in] the number of elements related to shift operation
   * @param voff, doff [in] the offsets of the first elements in arrays
   *                        vfactor and dest. They take the default value iZero
   * @param vstep, dstep [in] the separations between used elements in arrays
   *                          vfactor, dest. They take default value lOne.
   * @return nothing
   */
  inline void shift(int* dest, const int factor, const int* vfactor,
                    const long nshift,
                    const int voff=iZero, const long vstep=lOne,
                    const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    assert(vfactor!=NULL);
    int *dPtr=dest+doff, *vPtr=const_cast<int*>(vfactor)+voff;
    for(unsigned int i=0;i<static_cast<unsigned int>(nshift);
                     ++i,dPtr+=dstep,vPtr+=vstep)
      *dPtr+=factor*(*vPtr);
  }

  /**
   * @brief shift \c unsigned \c int array by constant and another array with offsets and steps
   *
   * It is implemented by looping over all the elements in arrays. The
   * concerned arrays are checked for their availability before this operation.
   *
   * @param dest [in,out] the array to be shifted
   * @param factor [in] the constant factor for shift operation.
   * @param vfactor [in] the array containing the factors for shift operation
   * @param nshift [in] the number of elements related to shift operation
   * @param voff, doff [in] the offsets of the first elements in arrays
   *                        vfactor and dest. They take the default value iZero
   * @param vstep, dstep [in] the separations between used elements in arrays
   *                          vfactor, dest. They take default value lOne.
   * @return nothing
   */
  inline void shift(unsigned int* dest, const unsigned int factor,
                    const unsigned int* vfactor, const long nshift,
                    const int voff=iZero, const long vstep=lOne,
                    const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    assert(vfactor!=NULL);
    unsigned int *dPtr=dest+doff;
    unsigned int *vPtr=const_cast<unsigned int*>(vfactor)+voff;
    for(unsigned int i=0;i<static_cast<unsigned int>(nshift);
                     ++i,dPtr+=dstep,vPtr+=vstep)
      *dPtr+=factor*(*vPtr);
  }

  /**
   * @brief shift \c double array by constant and another array with offsets and steps
   *
   * It is implemented by daxpy operation in BLAS. The concerned arrays are
   * checked for their availability before this operation.
   *
   * @param dest [in,out] the array to be shifted
   * @param factor [in] the constant factor for shift operation.
   * @param vfactor [in] the array containing the factors for shift operation
   * @param nshift [in] the number of elements related to shift operation
   * @param voff, doff [in] the offsets of the first elements in arrays
   *                        vfactor and dest. They take the default value iZero
   * @param vstep, dstep [in] the separations between used elements in arrays
   *                          vfactor, dest. They take default value lOne.
   * @return nothing
   */
  inline void shift(double* dest, const double factor, const double* vfactor,
                    const long nshift,
                    const int voff=iZero, const long vstep=lOne,
                    const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    assert(vfactor!=NULL);
    daxpy_(const_cast<long*>(&nshift),const_cast<double*>(&factor),
           const_cast<double*>(vfactor)+voff,const_cast<long*>(&vstep),
           dest+doff,const_cast<long*>(&dstep));
  }

  /**
   * @brief shift \c int array with another one considering offsets and steps
   *
   * It is implementated with the shift operation with constant factor iOne
   * and variable factor in input array.
   *
   * @param dest [in,out] the array to be shifted
   * @param vfactor [in] the array containing the factors for shift operation
   * @param nshift [in] the number of elements related to shift operation
   * @param voff, doff [in] the offsets of the first elements in arrays
   *                        vfactor and dest. They take the default value iZero
   * @param vstep, dstep [in] the separations between used elements in arrays
   *                          vfactor, dest. They take default value lOne.
   * @return nothing
   */
  inline void shift(int* dest, const int* vfactor, const long nshift,
                    const int voff=iZero, const long vstep=lOne,
                    const int doff=iZero, const long dstep=lOne) {
    shift(dest,iOne,vfactor,nshift,voff,vstep,doff,dstep);
  }

  /**
   * @brief shift \c unsigned \c int array with another one considering offsets and steps
   *
   * It is implementated with the shift operation with constant factor iOne
   * and variable factor in input array.
   *
   * @param dest [in,out] the array to be shifted
   * @param vfactor [in] the array containing the factors for shift operation
   * @param nshift [in] the number of elements related to shift operation
   * @param voff, doff [in] the offsets of the first elements in arrays
   *                        vfactor and dest. They take the default value iZero
   * @param vstep, dstep [in] the separations between used elements in arrays
   *                          vfactor, dest. They take default value lOne.
   * @return nothing
   */
  inline void shift(unsigned int* dest, const unsigned int* vfactor,
                    const long nshift,
                    const int voff=iZero, const long vstep=lOne,
                    const int doff=iZero, const long dstep=lOne) {
    shift(dest,uOne,vfactor,nshift,voff,vstep,doff,dstep);
  }

  /**
   * @brief shift \c double array with another one considering offsets and steps
   *
   * It is implementated with the shift operation with constant factor iOne
   * and variable factor in input array.
   *
   * @param dest [in,out] the array to be shifted
   * @param vfactor [in] the array containing the factors for shift operation
   * @param nshift [in] the number of elements related to shift operation
   * @param voff, doff [in] the offsets of the first elements in arrays
   *                        vfactor and dest. They take the default value iZero
   * @param vstep, dstep [in] the separations between used elements in arrays
   *                          vfactor, dest. They take default value lOne.
   * @return nothing
   */
  inline void shift(double* dest, const double* vfactor, const long nshift,
                    const int voff=iZero, const long vstep=lOne,
                    const int doff=iZero, const long dstep=lOne) {
    shift(dest,dOne,vfactor,nshift,voff,vstep,doff,dstep);
  }

  /**
   * @brief shift \c int array with a constant considering offset and step
   *
   * it is implementated with the shift operation with a constant as
   * the array factor.
   *
   * @param dest [in,out] the array to be shifted
   * @param factor [in] the constant as the factor for shift operation
   * @param nshift [in] the number of elements related to shift operation
   * @param doff [in] the offset of the first elements in array dest.
   *                  They take the default value iZero
   * @param dstep [in] the separation between used elements in array dest.
   *                   They take default value lOne.
   * @return nothing
   */
  inline void shift(int* dest, const int factor, const long nshift,
                    const int doff=iZero, const long dstep=lOne) {
    shift(dest,factor,&iOne,nshift,iZero,lZero,doff,dstep);
  }

  /**
   * @brief shift \c unsigned \c int array with a constant considering offset and step
   *
   * it is implementated with the shift operation with a constant as
   * the array factor.
   *
   * @param dest [in,out] the array to be shifted
   * @param factor [in] the constant as the factor for shift operation
   * @param nshift [in] the number of elements related to shift operation
   * @param doff [in] the offset of the first elements in array dest.
   *                  They take the default value iZero
   * @param dstep [in] the separation between used elements in array dest.
   *                   They take default value lOne.
   * @return nothing
   */
  inline void shift(unsigned int* dest, const unsigned int factor,
                    const long nshift,
                    const int doff=iZero, const long dstep=lOne) {
    shift(dest,factor,&uOne,nshift,iZero,lZero,doff,dstep);
  }

  /**
   * @brief shift \c double array with a constant considering offset and step
   *
   * it is implementated with the shift operation with a constant as
   * the array factor.
   *
   * @param dest [in,out] the array to be shifted
   * @param factor [in] the constant as the factor for shift operation
   * @param nshift [in] the number of elements related to shift operation
   * @param doff [in] the offset of the first elements in array dest.
   *                  They take the default value iZero
   * @param dstep [in] the separation between used elements in array dest.
   *                   They take default value lOne.
   * @return nothing
   */
  inline void shift(double* dest, const double factor, const long nshift,
                    const int doff=iZero, const long dstep=lOne) {
    shift(dest,factor,&dOne,nshift,iZero,lZero,doff,dstep);
  }

  /**
   * @brief the combination scale and shift operations for \c int array
   *
   * This operation is a combination of the scale and shift operations
   * for a certain array. It is implemented by looping over all the
   * elements in the concerned arrays. The concerned arrays are checked
   * for their availability before this operation.
   *
   * @param dest [in,out] the array to be operated
   * @param dfactor [in] the factor to scale the array dest
   * @param factor [in] the constant factor as shift step
   * @param sfactor [in] the array to scale the shift direction
   * @param vfactor [in] the array indicating shift direction
   * @param nscaleshift [in] the number of elements to be operated
   * @param soff, voff, doff [in] the offsets for the first elements in
   *                              the arrays sfactor, vfactor and dest.
   *                              They take default value iZero.
   * @param sstep, vstep, dstep [in] the separations between elements in
   *                                 the arrays sfactor, dfactor, and dest.
   *                                 They take default value lOne.
   * @return nothing
   */
  inline void scaleshift(int* dest, const int dfactor, const int factor,
                         const int* sfactor, const int* vfactor,
                         const long nscaleshift,
                         const int soff=iZero, const long sstep=lOne,
                         const int voff=iZero, const long vstep=lOne,
                         const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    assert(sfactor!=NULL);
    assert(vfactor!=NULL);
    int *dPtr=dest+doff;
    int *sPtr=const_cast<int*>(sfactor)+soff;
    int *vPtr=const_cast<int*>(vfactor)+voff;
    for(unsigned int i=0;i<static_cast<unsigned int>(nscaleshift);
                     ++i,dPtr+=dstep,sPtr+=sstep,vPtr+=vstep){
      *dPtr*=dfactor;
      *dPtr+=factor*(*sPtr)*(*vPtr);
    }
  }

  /**
   * @brief the combination scale and shift operations for \c int \c unsigned array
   *
   * This operation is a combination of the scale and shift operations
   * for a certain array. It is implemented by looping over all the
   * elements in the concerned arrays. The concerned arrays are checked
   * for their availability before this operation.
   *
   * @param dest [in,out] the array to be operated
   * @param dfactor [in] the factor to scale the array dest
   * @param factor [in] the constant factor as shift step
   * @param sfactor [in] the array to scale the shift direction
   * @param vfactor [in] the array indicating shift direction
   * @param nscaleshift [in] the number of elements to be operated
   * @param soff, voff, doff [in] the offsets for the first elements in
   *                              the arrays sfactor, vfactor and dest.
   *                              They take default value iZero.
   * @param sstep, vstep, dstep [in] the separations between elements in
   *                                 the arrays sfactor, dfactor, and dest.
   *                                 They take default value lOne.
   * @return nothing
   */
  inline void scaleshift(unsigned int* dest, const unsigned int dfactor,
                         const unsigned int factor, const unsigned int* sfactor,
                         const unsigned int* vfactor, const long nscaleshift,
                         const int soff=iZero, const long sstep=lOne,
                         const int voff=iZero, const long vstep=lOne,
                         const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    assert(sfactor!=NULL);
    assert(vfactor!=NULL);
    unsigned int *dPtr=dest+doff;
    unsigned int *sPtr=const_cast<unsigned int*>(sfactor)+soff;
    unsigned int *vPtr=const_cast<unsigned int*>(vfactor)+voff;
    for(unsigned int i=0;i<static_cast<unsigned int>(nscaleshift);
                         ++i,dPtr+=dstep,sPtr+=sstep,vPtr+=vstep){
      *dPtr*=dfactor;
      *dPtr+=factor*(*sPtr)*(*vPtr);
    }
  }

  /**
   * @brief the combination scale and shift operations for \c double array
   *
   * This operation is a combination of the scale and shift operations
   * for a certain array. It is implemented by dsbmv operation in BLAS.
   * The concerned arrays are checked for their availability before this
   * operation.
   *
   * @param dest [in,out] the array to be operated
   * @param dfactor [in] the factor to scale the array dest
   * @param factor [in] the constant factor as shift step
   * @param sfactor [in] the array to scale the shift direction
   * @param vfactor [in] the array indicating shift direction
   * @param nscaleshift [in] the number of elements to be operated
   * @param soff, voff, doff [in] the offsets for the first elements in
   *                              the arrays sfactor, vfactor and dest.
   *                              They take default value iZero.
   * @param sstep, vstep, dstep [in] the separations between elements in
   *                                 the arrays sfactor, dfactor, and dest.
   *                                 They take default value lOne.
   * @return nothing
   */
  inline void scaleshift(double* dest, const double dfactor,
                         const double factor,
                         const double* sfactor, const double* vfactor,
                         const long nscaleshift,
                         const int soff=iZero, const long sstep=lOne,
                         const int voff=iZero, const long vstep=lOne,
                         const int doff=iZero, const long dstep=lOne) {
    assert(dest!=NULL);
    assert(sfactor!=NULL);
    assert(vfactor!=NULL);
    static char flag[]="L";
    dsbmv_(flag,const_cast<long*>(&nscaleshift),const_cast<long*>(&lZero),
           const_cast<double*>(&factor), const_cast<double*>(sfactor)+soff,
           const_cast<long*>(&sstep), const_cast<double*>(vfactor)+voff,
           const_cast<long*>(&vstep),const_cast<double*>(&dfactor),dest+doff,
           const_cast<long*>(&dstep));
  }

  /**
   * @brief combination of scale and simple shift operation for \c int array
   *
   * It is implemented by actual combination of scale and shift operations.
   *
   * @param dest [in,out] the array to be operated
   * @param dfactor [in] the factor to scale the array dest
   * @param factor [in] the constant factor as shift step
   * @param vfactor [in] the array indicating shift direction
   * @param nscaleshift [in] the number of elements to be operated
   * @param voff, doff [in] the offsets for the first elements in
   *                        the arrays vfactor and dest.
   *                        They take default value iZero.
   * @param vstep, dstep [in] the separations between elements in
   *                          the arrays dfactor, and dest.
   *                          They take default value lOne.
   * @return nothing
   */
  inline void scaleshift(int* dest, const int dfactor, const int factor,
                         const int* vfactor, const long nscaleshift,
                         const int voff=iZero, const long vstep=lOne,
                         const int doff=iZero, const long dstep=lOne) {
    scale(dest,dfactor,nscaleshift,doff,dstep);
    shift(dest,factor,vfactor,nscaleshift,voff,vstep,doff,dstep);
  }

  /**
   * @brief combination of scale and simple shift operation for \c unsigned \c int array
   *
   * It is implemented by actual combination of scale and shift operations.
   *
   * @param dest [in,out] the array to be operated
   * @param dfactor [in] the factor to scale the array dest
   * @param factor [in] the constant factor as shift step
   * @param vfactor [in] the array indicating shift direction
   * @param nscaleshift [in] the number of elements to be operated
   * @param voff, doff [in] the offsets for the first elements in
   *                        the arrays vfactor and dest.
   *                        They take default value iZero.
   * @param vstep, dstep [in] the separations between elements in
   *                          the arrays dfactor, and dest.
   *                          They take default value lOne.
   * @return nothing
   */
  inline void scaleshift(unsigned int* dest, const unsigned int dfactor,
                         const unsigned int factor, const unsigned int* vfactor,
                         const long nscaleshift,
                         const int voff=iZero, const long vstep=lOne,
                         const int doff=iZero, const long dstep=lOne) {
    scale(dest,dfactor,nscaleshift,doff,dstep);
    shift(dest,factor,vfactor,nscaleshift,voff,vstep,doff,dstep);
  }

  /**
   * @brief combination of scale and simple shift operation for \c double array
   *
   * It is implemented by actual combination of scale and shift operations.
   *
   * @param dest [in,out] the array to be operated
   * @param dfactor [in] the factor to scale the array dest
   * @param factor [in] the constant factor as shift step
   * @param vfactor [in] the array indicating shift direction
   * @param nscaleshift [in] the number of elements to be operated
   * @param voff, doff [in] the offsets for the first elements in
   *                        the arrays vfactor and dest.
   *                        They take default value iZero.
   * @param vstep, dstep [in] the separations between elements in
   *                          the arrays dfactor, and dest.
   *                          They take default value lOne.
   * @return nothing
   */
  inline void scaleshift(double* dest, const double dfactor,const double factor,
                         const double* vfactor, const long nscaleshift,
                         const int voff=iZero, const long vstep=lOne,
                         const int doff=iZero, const long dstep=lOne) {
    scale(dest,dfactor,nscaleshift,doff,dstep);
    shift(dest,factor,vfactor,nscaleshift,voff,vstep,doff,dstep);
  }

  /**
   * @brief shift \c int array heterogeneously along various directions
   *
   * It is implemented with the combined scale with unit and heterogeneous
   * shift operations.
   *
   * @param dest [in,out] the array to be operated
   * @param factor [in] the constant factor as shift step
   * @param sfactor [in] the array to scale the shift direction
   * @param vfactor [in] the array indicating shift direction
   * @param nshift [in] the number of elements to be operated
   * @param soff, voff, doff [in] the offsets for the first elements in
   *                              the arrays sfactor, vfactor and dest.
   *                              They take default value iZero.
   * @param sstep, vstep, dstep [in] the separations between elements in
   *                                 the arrays sfactor, dfactor, and dest.
   *                                 They take default value lOne.
   * @return nothing
   */
  inline void shift(int* dest, const int factor, const int* sfactor,
                    const int* vfactor, const long nshift,
                    const int soff=iZero, const long sstep=lOne,
                    const int voff=iZero, const long vstep=lOne,
                    const int doff=iZero, const long dstep=lOne) {
    scaleshift(dest,iOne,factor,sfactor,vfactor,nshift,soff,sstep,voff,vstep,
               doff,dstep);
  }

  /**
   * @brief shift \c unsigned \c int array heterogeneously along various directions
   *
   * It is implemented with the combined scale with unit and heterogeneous
   * shift operations.
   *
   * @param dest [in,out] the array to be operated
   * @param factor [in] the constant factor as shift step
   * @param sfactor [in] the array to scale the shift direction
   * @param vfactor [in] the array indicating shift direction
   * @param nshift [in] the number of elements to be operated
   * @param soff, voff, doff [in] the offsets for the first elements in
   *                              the arrays sfactor, vfactor and dest.
   *                              They take default value iZero.
   * @param sstep, vstep, dstep [in] the separations between elements in
   *                                 the arrays sfactor, dfactor, and dest.
   *                                 They take default value lOne.
   * @return nothing
   */
  inline void shift(unsigned int* dest, const unsigned int factor,
                    const unsigned int* sfactor, const unsigned int* vfactor,
                    const long nshift,
                    const int soff=iZero, const long sstep=lOne,
                    const int voff=iZero, const long vstep=lOne,
                    const int doff=iZero, const long dstep=lOne) {
    scaleshift(dest,uOne,factor,sfactor,vfactor,nshift,soff,sstep,voff,vstep,
               doff,dstep);
  }

  /**
   * @brief shift \c double array heterogeneously along various directions
   *
   * It is implemented with the combined scale with unit and heterogeneous
   * shift operations.
   *
   * @param dest [in,out] the array to be operated
   * @param factor [in] the constant factor as shift step
   * @param sfactor [in] the array to scale the shift direction
   * @param vfactor [in] the array indicating shift direction
   * @param nshift [in] the number of elements to be operated
   * @param soff, voff, doff [in] the offsets for the first elements in
   *                              the arrays sfactor, vfactor and dest.
   *                              They take default value iZero.
   * @param sstep, vstep, dstep [in] the separations between elements in
   *                                 the arrays sfactor, dfactor, and dest.
   *                                 They take default value lOne.
   * @return nothing
   */
  inline void shift(double* dest, const double factor, const double* sfactor,
                    const double* vfactor, const long nshift,
                    const int soff=iZero, const long sstep=lOne,
                    const int voff=iZero, const long vstep=lOne,
                    const int doff=iZero, const long dstep=lOne) {
    scaleshift(dest,dOne,factor,sfactor,vfactor,nshift,soff,sstep,voff,vstep,
               doff,dstep);
  }

  /**
   * @brief exchange the content of two generic arrays with offsets and steps
   *
   * It is implemented by exchanging content of elements in the concerned
   * arrays by looping over all concerned elements. These arrays are checked
   * for their availability before this operation.
   *
   * T is the type of elements in the concerned arrays
   *
   * @param srcA, srcB [in,out] the arrays to be operated in exchange operation
   * @param nexchange [in] the number of elements to be exchanged.
   * @param aoff,boff [in] the offsets for the first element in arrays srcA,
   *                           srcB. They take default value of iZero.
   * @param astep,bstep [in] the separation between used elements in arrays
   *                         srcA, srcB.
   * @return nothing
   */
  template <typename T>
  inline void exchange(T* srcA, T* srcB, const long nexchange,
                       const int aoff=iZero, const long astep=lOne,
                       const int boff=iZero, const long bstep=lOne) {
    assert(srcA!=NULL);
    assert(srcB!=NULL);
    T tmT, *aPtr=srcA+aoff, *bPtr=srcB+boff;
    for(unsigned int i=0;i<nexchange;++i,aPtr+=astep,bPtr+=bstep) {
      tmT=*aPtr;  *aPtr=*bPtr;  *bPtr=tmT;
    }
  }

  /**
   * @brief exchange the content of two \c int arrays with offsets and steps
   *
   * It is implemented with sswap operation in BLAS. The concerned
   * arrays are checked for their availability before this operation.
   * The compatibility between sizes of \c int data and of \c float data
   * is also checked.
   *
   * @param srcA, srcB [in,out] the arrays to be operated in exchange operation
   * @param nexchange [in] the number of elements to be exchanged.
   * @param aoff,boff [in] the offsets for the first element in arrays srcA,
   *                           srcB. They take default value of iZero.
   * @param astep,bstep [in] the separation between used elements in arrays
   *                         srcA, srcB.
   * @return nothing
   */
  inline void exchange(int* srcA, int* srcB, const long nexchange,
                       const int aoff=iZero, const long astep=lOne,
                       const int boff=iZero, const long bstep=lOne) {
    assert(sizeof(int)==sizeof(float));
    assert(srcA!=NULL);
    assert(srcB!=NULL);
    sswap_(const_cast<long*>(&nexchange),
           reinterpret_cast<float*>(srcA)+aoff,const_cast<long*>(&astep),
           reinterpret_cast<float*>(srcB)+boff,const_cast<long*>(&bstep));
  }

  /**
   * @brief exchange the content of two \c unsigned \c int arrays with offsets and steps
   *
   * It is implemented with sswap operation in BLAS. The concerned
   * arrays are checked for their availability before this operation.
   * The compatibility between sizes of \c unsigned \c int data and
   * of \c float data is also checked.
   *
   * @param srcA, srcB [in,out] the arrays to be operated in exchange operation
   * @param nexchange [in] the number of elements to be exchanged.
   * @param aoff,boff [in] the offsets for the first element in arrays srcA,
   *                           srcB. They take default value of iZero.
   * @param astep,bstep [in] the separation between used elements in arrays
   *                         srcA, srcB.
   * @return nothing
   */
  inline void exchange(unsigned int* srcA, unsigned int* srcB,
                       const long nexchange,
                       const int aoff=iZero, const long astep=lOne,
                       const int boff=iZero, const long bstep=lOne) {
    assert(sizeof(unsigned int)==sizeof(float));
    assert(srcA!=NULL);
    assert(srcB!=NULL);
    sswap_(const_cast<long*>(&nexchange),
           reinterpret_cast<float*>(srcA)+aoff,const_cast<long*>(&astep),
           reinterpret_cast<float*>(srcB)+boff,const_cast<long*>(&bstep));
  }

  /**
   * @brief exchange the content of two \c double arrays with offsets and steps
   *
   * It is implemented with dswap operation in BLAS. The concerned
   * arrays are checked for their availability before this operation.
   *
   * @param srcA, srcB [in,out] the arrays to be operated in exchange operation
   * @param nexchange [in] the number of elements to be exchanged.
   * @param aoff,boff [in] the offsets for the first element in arrays srcA,
   *                           srcB. They take default value of iZero.
   * @param astep,bstep [in] the separation between used elements in arrays
   *                         srcA, srcB.
   * @return nothing
   */
  inline void exchange(double* srcA, double* srcB, const long nexchange,
                       const int aoff=iZero, const long astep=lOne,
                       const int boff=iZero, const long bstep=lOne) {
    assert(srcA!=NULL);
    assert(srcB!=NULL);
    dswap_(const_cast<long*>(&nexchange),srcA+aoff,
           const_cast<long*>(&astep),srcB+boff,const_cast<long*>(&bstep));
  }

  /**
   * @brief dot product for \c int arrays
   *
   * It is implemented by calculating summation of the corresponding
   * products. The arrays are checked for their availability before
   * this operation.
   *
   * @param srcA, srcB [in] the arrays to calculate dot product
   * @param ndot [in] the number of elements for dot product
   * @param aoff, boff [in] the offsets for the first elements in
   *                        the arrays srcA, srcB. They take the default
   *                        value of iZero.
   * @param astep, bstep [in] the steps between elements in the arrays
   *                          srcA, srcB. They take the default value lOne.
   * @return the dot product of the concerned arrays.
   */
  inline int dot(const int* srcA, const int* srcB, const long ndot,
                 const int aoff=iZero, const long astep=lOne,
                 const int boff=iZero, const long bstep=lOne) {
    assert(srcA!=NULL);
    assert(srcB!=NULL);
    int *aPtr=const_cast<int*>(srcA)+aoff, *bPtr=const_cast<int*>(srcB)+boff;
    int s=0;
    for(unsigned int i=0;i<static_cast<unsigned int>(ndot);
                     ++i,aPtr+=astep,bPtr+=bstep)
      s+=(*aPtr)*(*bPtr);
    return s;
  }

  /**
   * @brief dot product for \c unsigned \c int arrays
   *
   * It is implemented by calculating summation of the corresponding
   * products. The arrays are checked for their availability before
   * this operation.
   *
   * @param srcA, srcB [in] the arrays to calculate dot product
   * @param ndot [in] the number of elements for dot product
   * @param aoff, boff [in] the offsets for the first elements in
   *                        the arrays srcA, srcB. They take the default
   *                        value of iZero.
   * @param astep, bstep [in] the steps between elements in the arrays
   *                          srcA, srcB. They take the default value lOne.
   * @return the dot product of the concerned arrays.
   */
  inline unsigned int dot(const unsigned int* srcA, const unsigned int* srcB,
                          const long ndot,
                          const int aoff=iZero, const long astep=lOne,
                   const int boff=iZero, const long bstep=lOne) {
    assert(srcA!=NULL);
    assert(srcB!=NULL);
    unsigned int *aPtr=const_cast<unsigned int*>(srcA)+aoff;
    unsigned int *bPtr=const_cast<unsigned int*>(srcB)+boff;
    unsigned int s=0;
    for(unsigned int i=0;i<static_cast<unsigned int>(ndot);
                     ++i,aPtr+=astep,bPtr+=bstep)
      s+=(*aPtr)*(*bPtr);
    return s;
  }

  /**
   * @brief dot product for \c double arrays
   *
   * It is implemented by BLAS operation ddot_. The arrays are checked
   * for their availability before this operation.
   *
   * @param srcA, srcB [in] the arrays to calculate dot product
   * @param ndot [in] the number of elements for dot product
   * @param aoff, boff [in] the offsets for the first elements in
   *                        the arrays srcA, srcB. They take the default
   *                        value of iZero.
   * @param astep, bstep [in] the steps between elements in the arrays
   *                          srcA, srcB. They take the default value lOne.
   * @return the dot product of the concerned arrays.
   */
  inline double dot(const double* srcA, const double* srcB, const long ndot,
                    const int aoff=iZero, const long astep=lOne,
                    const int boff=iZero, const long bstep=lOne) {
    assert(srcA!=NULL);
    assert(srcB!=NULL);
    return ddot_(const_cast<long*>(&ndot),const_cast<double*>(srcA)+aoff,
                 const_cast<long*>(&astep),const_cast<double*>(srcB)+boff,
                 const_cast<long*>(&bstep));
  }

  /**
   * @brief the square of norm of \c int array
   *
   * It is implemented with dot operation.
   *
   * @param src [in] the array for the norm calculation
   * @param nnormsq [in] the number of elements in concerned calculation
   * @param off [in] the offset for the first element in array src. It takes
   *                 the default value iZero.
   * @param step [in] the step between elements in array src. It takes
   *                  the default value lOne.
   * @return the square of the norm of the input array.
   */
  inline int normSQ(const int* src, const long nnormsq,
                    const int off=iZero, const long step=lOne) {
    return dot(src,src,nnormsq,off,step,off,step);
  }

  /**
   * @brief the square of norm of \c unsigned \c int array
   *
   * It is implemented with dot operation.
   *
   * @param src [in] the array for the norm calculation
   * @param nnormsq [in] the number of elements in concerned calculation
   * @param off [in] the offset for the first element in array src. It takes
   *                 the default value iZero.
   * @param step [in] the step between elements in array src. It takes
   *                  the default value lOne.
   * @return the square of the norm of the input array.
   */
  inline unsigned int normSQ(const unsigned int* src, const long nnormsq,
                             const int off=iZero, const long step=lOne) {
    return dot(src,src,nnormsq,off,step,off,step);
  }

  /**
   * @brief the square of norm of \c double array
   *
   * It is implemented with dot operation.
   *
   * @param src [in] the array for the norm calculation
   * @param nnormsq [in] the number of elements in concerned calculation
   * @param off [in] the offset for the first element in array src. It takes
   *                 the default value iZero.
   * @param step [in] the step between elements in array src. It takes
   *                  the default value lOne.
   * @return the square of the norm of the input array.
   */
  inline double normSQ(const double* src, const long nnormsq,
                       const int off=iZero, const long step=lOne) {
    return dot(src,src,nnormsq,off,step,off,step);
  }

  /**
   * @brief norm of \c double array
   *
   * It is implemented with BLAS operation dnrm2_. The array is checked
   * for the availability before this operation.
   *
   * @param src [in] the array for norm calculation
   * @param nnorm [in] the number of elements in calculation
   * @param soff [in] the offset for the first element in array src. It takes
   *                  the default value iZero.
   * @param sstep [in] the step between elements in array src. It takes
   *                   the default value lOne.
   * @return the norm of the input array
   * @note For the norm, the result is probably not integer even when the
   *       input array is composed of integers. Therefore, this procedure
   *       is only used for \c double data.
   */
  inline double norm(const double* src, const long nnorm,
                     const int soff=iZero, const long sstep=lOne) {
    assert(src!=NULL);
    return dnrm2_(const_cast<long*>(&nnorm),const_cast<double*>(src)+soff,
                  const_cast<long*>(&sstep));
  }

  inline int asum(const int* src, const long nasum,
                  const int off=iZero, const long step=lOne) {
    assert(src!=NULL);
    int *Ptr=const_cast<int*>(src)+off;
    int s=0;
    for(unsigned int i=0;i<static_cast<unsigned int>(nasum);++i,Ptr+=step)
      s+=abs(*Ptr);
    return s;
  }

  inline unsigned int asum(const unsigned int* src, const long nasum,
                           const int off=iZero, const long step=lOne) {
    assert(src!=NULL);
    unsigned int *Ptr=const_cast<unsigned int*>(src)+off;
    unsigned int s=0;
    for(unsigned int i=0;i<static_cast<unsigned int>(nasum);++i,Ptr+=step)
      s+=*Ptr;
    return s;
  }

  inline double asum(const double* src, const long nasum,
                     const int off=iZero, const long step=lOne) {
    assert(src!=NULL);
    return dasum_(const_cast<long*>(&nasum),const_cast<double*>(src)+off,
                  const_cast<long*>(&step));
  }

  void crossProd(const double* va, const double* vb, double* v,
                 const unsigned int asize, const unsigned int bsize,
                 const unsigned int size,
                 const unsigned int aoff=iZero, const unsigned int astep=lOne,
                 const unsigned int boff=iZero, const unsigned int bstep=lOne,
                 const unsigned int off=iZero, const unsigned int step=lOne) {
    assert(aoff+astep*2<=asize);
    assert(boff+bstep*2<=bsize);
    assert(off+step*2<=size);
    double *pa=const_cast<double*>(va)+aoff, *pb=const_cast<double*>(vb)+boff;
    double *p=v+off;
    unsigned int dastep=astep+astep, dbstep=bstep+bstep, dstep=step+step;
    p[0]    = pa[astep] *pb[dbstep] -pa[dastep] *pb[bstep];
    p[step] = pa[dastep]*pb[0]      -pa[0]      *pb[dbstep];
    p[dstep]= pa[0]     *pb[bstep]  -pa[astep]  *pb[0];
  }

}

#endif

