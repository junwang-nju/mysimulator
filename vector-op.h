
/**
 * @file vector-op.h
 * @brief Operations for vectors
 *
 * This file contains a series of operations for vectors (mainly with
 * \c double type data). This is similar as the file vector-impl.h to
 * provide interfaces between background library and classes in our
 * package.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Vector_Operation_H_
#define _Vector_Operation_H_

#include "var-vector.h"
#include "fix-vector.h"
#include <iostream>

namespace std {

  /**
   * @brief dot product for part of two external arrays
   *
   * The dot product is implemented with the BLAS ddot_() operation.
   * The part of arraysare selected with offset/step protocol.
   *
   * @param [in] va
   *        The input array containing \c double data
   *
   * @param [in] vb
   *        The input array containing \c double data
   *
   * @param [in] ndot
   *        The number of elements in dot product operation
   *
   * @param [in] aoffset
   *        The shift for the first element to be copied in input array va,
   *        It takes the default value zero (namely starting from the
   *        first element)
   *
   * @param [in] astep
   *        The spacing between the two elements in input array va.
   *        It takes the default value one (namely all elements are
   *        read)
   *
   * @param [in] boffset
   *        The shift for the first element to be copied in input array vb,
   *        It takes the default value zero (namely starting from the
   *        first element)
   *
   * @param [in] bstep
   *        The spacing between the two elements in input array vb.
   *        It takes the default value one (namely all elements are
   *        read)
   *
   * @return the dot product for the part of the input arrays.
   */
  double dot(const double* va, const double* vb, long ndot,
             int aoffset=iZero, long astep=lOne,
             int boffset=iZero, long bstep=lOne) {
    return ddot_(&ndot,const_cast<double*>(va)+aoffset,&astep,
                       const_cast<double*>(vb)+boffset,&bstep);
  }

  /**
   * @brief dot product for part of two external vectors
   *
   * The dot product is implemented with the dot() operation for arrays.
   * The part of arraysare selected with offset/step protocol.
   *
   * @param [in] va
   *        The input vector containing \c double data
   *
   * @param [in] vb
   *        The input vector containing \c double data
   *
   * @param [in] ndot
   *        The number of elements in dot product operation
   *
   * @param [in] aoffset
   *        The shift for the first element to be copied in input vector va,
   *        It takes the default value zero (namely starting from the
   *        first element)
   *
   * @param [in] astep
   *        The spacing between the two elements in input vector va.
   *        It takes the default value one (namely all elements are
   *        read)
   *
   * @param [in] boffset
   *        The shift for the first element to be copied in input vector vb,
   *        It takes the default value zero (namely starting from the
   *        first element)
   *
   * @param [in] bstep
   *        The spacing between the two elements in input vector vb.
   *        It takes the default value one (namely all elements are
   *        read)
   *
   * @return the dot product for the part of the input vectors.
   */
  double dot(const VectorBase<double>& va, const VectorBase<double>& vb,
             long ndot,
             int aoffset=iZero, long astep=lOne,
             int boffset=iZero, long bstep=lOne) {
    assert(static_cast<uint>(aoffset+astep*ndot)<=va.size());
    assert(static_cast<uint>(boffset+bstep*ndot)<=vb.size());
    return dot(va.data(),vb.data(),ndot,aoffset,astep,boffset,bstep);
  }

  /**
   * @brief dot product for two external vectors
   *
   * This is a simplification for dot product of two vectors. It is
   * implemented with the dot() operation for part of vectors. The
   * smaller size of the input vectors is used.
   *
   * @param [in] va
   *        The input vector containing \c double data
   *
   * @param [in] vb
   *        The input vector containing \c double data
   *
   * @return the dot product for the input vectors.
   */
  double dot(const VectorBase<double>& va, const VectorBase<double>& vb) {
    long n=(va.size()<vb.size()?va.size():vb.size());
    return dot(va,vb,n);
  }

  /**
   * @brief the square of the norm of a vector
   *
   * It is implemented as the dot product between the input vector and itself.
   *
   * @param [in] v
   *        The input VectorBase object
   *
   * @return the square of the Eulidean norm of input vector
   */
  double normSQ(const VectorBase<double>& v) { return dot(v,v); }

  /**
   * @brief the norm of part of input array
   *
   * This is defined as the absolute value of the square root of the squares
   * of elements. It is implemented with BLAS dnrm2_() operation. The result
   * equals to the Eulidean length of the concerned spatial vector.
   *
   * @param [in] v
   *        The input array containing \c double data
   *
   * @param [in] nnorm
   *        The number of the elements related to the norm calculation
   *
   * @param [in] offset
   *        The shift for the first element to be copied in input array v,
   *        It takes the default value zero (namely starting from the
   *        first element)
   *
   * @param [in] step
   *        The spacing between the two elements in input array v.
   *        It takes the default value one (namely all elements are
   *        read)
   *
   * @return the norm of the input array.
   */
  double norm(const double* v, long nnorm, int offset=iZero, long step=lOne) {
    return dnrm2_(&nnorm,const_cast<double*>(v)+offset,&step);
  }

  /**
   * @brief the norm of part of input vector
   *
   * This is defined as the absolute value of the square root of the squares
   * of elements. It is implemented with norm() operation for input array.
   * The result equals to the Eulidean length of the concerned spatial vector.
   *
   * @param [in] v
   *        The input vector containing \c double data
   *
   * @param [in] nnorm
   *        The number of the elements related to the norm calculation
   *
   * @param [in] offset
   *        The shift for the first element to be copied in input vector v,
   *        It takes the default value zero (namely starting from the
   *        first element)
   *
   * @param [in] step
   *        The spacing between the two elements in input vector v.
   *        It takes the default value one (namely all elements are
   *        read)
   *
   * @return the norm of the input vector
   */
  double norm(const VectorBase<double>& v, long nnorm,
              int offset=iZero, long step=lOne) {
    assert(static_cast<uint>(offset+step*nnorm)<=v.size());
    return norm(v.data(),nnorm,offset,step);
  }

  double norm(const VectorBase<double>& v) { return norm(v,v.size()); }

  double sumABS(const double* v, long nsum, int offset=iZero, long step=lOne) {
    return dasum_(&nsum,const_cast<double*>(v)+offset,&step);
  }

  double sumABS(const VectorBase<double>& v, long nsum,
                int offset=iZero, long step=lOne) {
    assert(static_cast<uint>(offset+step*nsum)<=v.size());
    return sumABS(v.data(),nsum,offset,step);
  }

  double sumABS(const VectorBase<double>& v) { return sumABS(v,v.size()); }

  void cross_prod(const double* va, const double* vb, double* v,
                  int aoffset=iZero, long astep=lOne,
                  int boffset=iZero, long bstep=lOne,
                  int offset=iZero, long step=lOne) {
    double *p=v+offset;
    double *pa=const_cast<double*>(va)+aoffset;
    double *pb=const_cast<double*>(vb)+boffset;
    p[0]        =pa[astep]      *pb[bstep+bstep]
                -pa[astep+astep]*pb[step];
    p[step]     =pa[astep+astep]*pb[0]
                -pa[0]          *pb[bstep+bstep];
    p[step+step]=pa[0]          *pb[bstep]
                -pa[astep]      *pb[0];
  }

  void cross_prod(const VectorBase<double>& va,
                  const VectorBase<double>& vb,
                  VectorBase<double>& v,
                  int aoffset=iZero, long astep=lOne,
                  int boffset=iZero, long bstep=lOne,
                  int offset=iZero, long step=lOne) {
    assert(static_cast<uint>(aoffset+astep*3)<=va.size());
    assert(static_cast<uint>(boffset+bstep*3)<=vb.size());
    assert(static_cast<uint>(offset+step*3)<=v.size());
    cross_prod(va.data(),vb.data(),v.data(),
               aoffset,astep,boffset,bstep,offset,step);
  }

}

#endif

