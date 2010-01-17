
/**
 * @file property-list-op.h
 * @brief the operation for list of property
 *
 * This file includes some operations for property list. These operations
 * are similar to those for regular vectors. These operations are defined
 * to make the type of property list being compatible with regular vectors.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Property_List_Operation_H_
#define _Property_List_Operation_H_

#include "property-list.h"
#include "vector-op.h"

namespace std {

  /**
   * @brief dot product between list of property and vector
   *
   * It is implemented as the dot product of the internal vector in list of property and the input
   * vector.
   *
   * \a vType
   *    The template type used in definition of the list
   *
   * @param [in] P
   *        The input list of property
   *
   * @param [in] v
   *        The input VectorBase object
   *
   * @return the dot product of two input objects
   */
  template <template <typename> class vType>
  double dot(const PropertyList<vType>& P, const VectorBase<double>& v) {
    assert(vType<int>::IsVector);
    return dot(P.PropertyData,v);
  }

  /**
   * @brief dot product between vector and list of property
   *
   * It is implemented as the dot product of the internal vector in list of
   * property and the input vector.
   *
   * \a vType
   *    The template type used in definition of the list
   *
   * @param [in] v
   *        The input VectorBase object
   *
   * @param [in] P
   *        The input list of property
   *
   * @return the dot product of two input objects
  */
  template <template <typename> class vType>
  double dot(const VectorBase<double>& v, const PropertyList<vType>& P) {
    assert(vType<int>::IsVector);
    return dot(P.PropertyData,v);
  }

  /**
   * @brief dot product between two lista of property
   *
   * It is implemented as the dot product of the internal vectors in the
   * input lists of property.
   *
   * \a vTypeA
   *    The template type used in definition of the list Pa
   *
   * \a vTypeB
   *    The template type used in definition of the list Pb
   *
   * @param [in] Pa
   *        The input list of property
   *
   * @param [in] Pb
   *        The input list of property
   *
   * @return the dot product of two input objects
  */
  template <template <typename> class vTypeA,
            template <typename> class vTypeB>
  double dot(const PropertyList<vTypeA>& Pa, const PropertyList<vTypeB>& Pb){
    assert((vTypeA<int>::IsVector)&&(vTypeB<int>::IsVector));
    return dot(Pa.PropertyData,Pb.PropertyData);
  }

  /**
   * @brief the norm of the list of property
   *
   * It is implemented as the norm of the internal vector of the input
   * list of property.
   *
   * \a vType
   *    The template type used in definition of the list
   *
   * @param [in] P
   *        The input list of property
   *
   * @return the norm of the list of property
   */
  template <template <typename> class vType>
  double norm(const PropertyList<vType>& P) {
    assert(vType<int>::IsVector);
    return norm(P.PropertyData);
  }

  /**
   * @brief the square of norm of the list of property
   *
   * It is implemented as the square of the norm of the internal vector
   * of the input list of property.
   *
   * \a vType
   *    The template type used in definition of the list
   *
   * @param [in] P
   *        The input list of property
   *
   * @return the square of the norm of the list of property
   */
  template <template <typename> class vType>
  double normSQ(const PropertyList<vType>& P) {
    assert(vType<int>::IsVector);
    return normSQ(P.PropertyData);
  }

  /**
   * @brief the summation of the absolute values of list of property
   *
   * It is implemented as the square of the summation of the absolute
   * values in the internal vector of the input list of property.
   *
   * \a vType
   *    The template type used in definition of the list
   *
   * @param [in] P
   *        The input list of property
   *
   * @return the summation of the absolute values of elements in the
   *         list of property
   */
  template <template <typename> class vType>
  double sumABS(const PropertyList<vType>& P) {
    assert(vType<int>::IsVector);
    return sumABS(P.PropertyData);
  }

}

#endif

