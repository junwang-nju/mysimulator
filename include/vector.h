
/**
 * @file vector.h
 * @brief vector-like object and operation
 *
 * This file contains a declaration for vector-like data
 * and some interfaces related to the operations on the
 * this kind of data.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Vector_H_
#define _Vector_H_

#include "vector-impl.h"
#include "storage-state-name.h"
#include "error-proc.h"

namespace std {

  /**
   * @brief vector-like object
   *
   * This is an encapsulation of array. The size information is
   * included. This may ease the interface to use data. It is
   * simple than vector in STL, and generally used for simulation.
   *
   * T is the type of data in the internal data.
   */
  template <typename T>
  struct Vector {

    /**
     * @brief abbreviation for Vector type
     */
    typedef Vector<T>   Type;

    /**
     * @brief pointer to data array
     */
    T* data;
    /**
     * @brief the number of elements in concerned array
     */
    unsigned int size;
    /**
     * @brief the state of the internal data
     */
    unsigned int state;

    /**
     * @brief default initiator
     *
     * initialize the data with NULL-type data, and mark the state as
     * Unused.
     */
    Vector() : data(NULL), size(uZero), state(Unused) {}
    /**
     * @brief copy constructor
     *
     * It is prohiited to avoid implicit allocate temporary object
     *
     * @param [in] v The input Vector-type object
     */
    Vector(const Type& v) { myError("Cannot create from Vector"); }
    /**
     * @brief copy operator
     *
     * it is implemented with assign operation
     *
     * @param [in] V the input Vector-type object
     * @return the reference to the output Vector object
     */
    Type& operator=(const Type& V) { assign(*this,V); return *this; }
    /**
     * @brief destructor
     *
     * it is implemented with release function.
     */
    ~Vector() { release(*this); }

    /**
     * @brief access the pointer
     *
     * This gives a way to access the internal pointer to data to
     * be compatible with some regular procedures (such as BLAS).
     *
     * @return the reference to the internal pointer.
     */
    T*& operator()() { return data; }
    /**
     * @brief visit the pointer
     *
     * This is a way to visit the internal pointer. Through the operator,
     * the internal elements cannot be modified.
     *
     * @return the const version of the internal pointer
     */
    const T* operator()() const { return data; }
    /**
     * @brief access the element
     *
     * This operator is used to access the Ith element in the internal
     * array. This provides the compatibility with regular array.
     *
     * @param [in] I the index for the array
     * @return the reference to the Ith element
     */
    T& operator[](const int I) { return data[I]; }
    /**
     * @brief vist the element
     *
     * This operator is used to vist the Ith element in the internal
     * array. The element cannot be modified. This provides the
     * compatibility with regular array.
     *
     * @param [in] I the index for the array
     * @return the const reference to the Ith element
     */
    const T& operator[](const int I) const { return data[I]; }

  };

  /**
   * @brief the flag of availability
   *
   * This program gives out the flag that indicates if the data in
   * the concerned vector is available. It is implemented by checking
   * the availability of the pointer to the data.
   *
   * T is the type of data for vector.
   *
   * @param [in] v the vector to be checked
   * @return the flag indicating the availability of input vector.
   */
  template <typename T>
  inline bool IsAvailable(const Vector<T>& v){ return IsAvailable(v()); }

  /**
   * @brief allocate Vector with expected size
   *
   * The array in vector object is allocated with input size. The size
   * information is updated. The state is assigned as Allocated. The
   * previous data in the vector object is cleared.
   *
   * T is the type of data for vector.
   *
   * @param [in] v the vector object to be allocated.
   * @param [in] vsize the size to be allocated.
   * @return nothing.
   * @todo No signal returned for success of allocation
   */
  template <typename T>
  inline void allocate(Vector<T>& v, const unsigned int vsize) {
    release(v);
    allocate(v(),vsize);
    v.size=vsize;
    v.state=Allocated;
  }

  /**
   * @brief release the data in Vector object
   *
   * If the internal data is allocated, the internal data is released.
   * It the internal structure is referenced, just clear the reference.
   * The state is restored as Unused.
   *
   * T is the type of data for vector.
   *
   * @param [in] v the vector object to be released.
   * @return nothing.
   * @todo the status of the release operation is not implemented.
   */
  template <typename T>
  inline void release(Vector<T>& v) {
    if(v.state==Allocated)  release(v());
    else v()=NULL;
    v.size=0;
    v.state=Unused;
  }

  /**
   * @brief refer to another Vector object
   *
   * Just copy the pointer and size information from source to
   * destination to realize another entry for data. The previous
   * data in destination object is cleared before reference
   * operation.
   *
   * T is the type of data for vector.
   *
   * @param [out] dest the destination Vector object
   * @param [in] src the source Vector object
   * @return nothing
   * @todo the status of operation is not implemented.
   */
  template <typename T>
  inline void refer(Vector<T>& dest, const Vector<T>& src) {
    assert(IsAvailable(src));
    release(dest);
    dest()=const_cast<T*>(src());
    dest.size=src.size;
    dest.state=Reference;
  }

  /**
   * @brief refer to an array
   *
   * The operation provides some flexibility to refer some part of array.
   * The starting point of the data in Vector is specified with offset.
   * The other operation is similar as above refer operation. 
   *
   * T is the type of data for vector.
   *
   * @param [out] dest the destination Vector object
   * @param [in] src the pointer of input array
   * @param [in] size the size of data in Vector object
   * @param [in] off the start offset in input array
   * @return nothing.
   * @todo the status of operation is not implemented.
   * @todo refer to the data with interlacing between elements is not
   *       implemented.
   * @note Since the external array do not have size information, the
   *       validity of the vector data should be ensured by users.
   */
  template <typename T>
  inline void refer(Vector<T>& dest, const T* src, const unsigned int size,
                    const unsigned int off=uZero) {
    assert(IsAvailable(src));
    release(dest);
    dest()=const_cast<T*>(src)+off;
    dest.size=size;
    dest.state=Reference;
  }

  /**
   * @brief assign Vector object with another Vector object
   *
   * This operation is implemented with the method for two arrays.
   * The number of elements related to the operation takes the
   * minimum of two concerned Vectors.
   *
   * T is the type of data for vector.
   *
   * @param [out] dest the destination Vector object
   * @param [in] src the source Vector object
   * @return nothing
   * @todo no flags is returned to report if this operation is successful.
   */
  template <typename T>
  inline void assign(Vector<T>& dest, const Vector<T>& src) {
    unsigned int n=(dest.size<src.size?dest.size:src.size);
    assign(dest(),src(),n);
  }

  /**
   * @brief assign Vector with a value
   *
   * It is implemented with corresponding operation to assign array
   * with value.
   *
   * T is the type of data for vector.
   *
   * @param [out] v the Vector object to be assigned
   * @param [in] value the reference to a T-type value
   * @return nothing
   * @note this generic operation requires that the type of value
   *       match exactly with element in vector.
   */
  template <typename T>
  inline void assign(Vector<T>& v, const T& value){ assign(v(),value,v.size); }

  /**
   * @brief assign unsigned-int-type Vector with unsigned-int value
   *
   * It is almost the same as the generic operator except that the
   * value is not the reference. This enable the implicit conversion
   * of data. This is a specification for generic type.
   *
   * @param [out] v the Vector to store unsigned-int data
   * @param [in] value the unsigned-int value
   * @return nothing.
   * @note this may ease the use of constant. The user need not to
   *       assign the type of constant explicitly.
   */
  inline void assign(Vector<unsigned int>& v, const unsigned int value) {
    assign(v(),value,v.size);
  }

  /**
   * @brief assign int-type Vector with int value
   *
   * It is almost the same as the generic operator except that the
   * value is not the reference. This enable the implicit conversion
   * of data. This is a specification for generic type.
   *
   * @param [out] v the Vector to store int data
   * @param [in] value the int value
   * @return nothing.
   * @note this may ease the use of constant. The user need not to
   *       assign the type of constant explicitly.
   */
  inline void assign(Vector<int>& v, const int value) {
    assign(v(),value,v.size);
  }

  /**
   * @brief assign double-type Vector with double value
   *
   * It is almost the same as the generic operator except that the
   * value is not the reference. This enable the implicit conversion
   * of data. This is a specification for generic type.
   *
   * @param [out] v the Vector to store double data
   * @param [in] value the double value
   * @return nothing.
   * @note this may ease the use of constant. The user need not to
   *       assign the type of constant explicitly.
   */
  inline void assign(Vector<double>& v, const double value) {
    assign(v(),value,v.size);
  }

  /**
   * @brief scale Vector object with a value
   *
   * it is implemented with the corresponding operation for array.
   *
   * T is the type of data for vector.
   *
   * @param [in,out] v The Vector object to be scaled
   * @param [in] value the scale factor
   * @return nothing
   * @todo specification for int, unsigned int, double are not implemented.
   */
  template <typename T>
  inline void scale(Vector<T>& v, const T& value) { scale(v(),value,v.size); }

  /**
   * @brief scale Vector object with another Vector object
   *
   * It is implemented with the corresponding operation for array. The
   * number of element involved in this operation is the minimum of the
   * size of two vectors.
   *
   * T is the type of data for vector.
   *
   * @param [in,out] v The Vector object to be scaled
   * @param [in] vf The Vector object as the scale factor
   * @return nothing
   */
  template <typename T>
  inline void scale(Vector<T>& v, const Vector<T>& vf) {
    unsigned int n=(v.size<vf.size?v.size:vf.size);
    scale(v(),vf(),n);
  }

  /**
   * @brief shift Vector along certain direction with certain step
   *
   * It is implemented with the corresponding operation for array. The
   * number of elements involved in this operation is the minimum of the
   * size of two concerned vectors.
   *
   * T is the type of elements in vectors
   *
   * @param v [in,out] the Vector object to be shifted
   * @param fac [in] the size factor along the direction to be shifted
   * @param vfac [in] the Vector object indicating the direction to shift
   * @return nothing
   */
  template <typename T>
  inline void shift(Vector<T>& v, const T& fac, const Vector<T>& vfac) {
    unsigned int n=(v.size<vfac.size?v.size:vfac.size);
    shift(v(),fac,vfac(),n);
  }

  /**
   * @brief shift Vector along direction with unit step
   *
   * It is implemented with the corresponding operation for array. The
   * number of elements involved in this operation is the minimum of the
   * size of two concerned vectors.
   *
   * T is the type of elements in vectors
   *
   * @param v [in,out] the Vector object to be shifted
   * @param vfac [in] the Vector object indicating the direction to shift
   * @return nothing
   */
  template <typename T>
  inline void shift(Vector<T>& v, const Vector<T>& vfac) {
    unsigned int n=(v.size<vfac.size?v.size:vfac.size);
    shift(v(),vfac(),n);
  }

  /**
   * @brief shift components of Vector with a constant
   *
   * It is implemented by the corresponding operation for array. The number
   * of elements to be operated is the number of elements in Vector object.
   *
   * T is the type of data in vectors.
   *
   * @param v [in,out] the Vector object to be shifted.
   * @param fac [in] the factor used in shifting elements of Vector.
   * @return nothing
   */ 
  template <typename T>
  inline void shift(Vector<T>& v, const T& fac) { shift(v(),fac,v.size); }

  /**
   * @brief shift Vector along certain direction with certain step (different parameter order)
   *
   * This is a version to match different order of parameters. It is
   * implemented with another shift function with direction and step
   * as parameters.
   *
   * T is the type of data in vectors.
   *
   * @param v [in,out] the Vector object to be shifted
   * @param vfac [in] the Vector object indicating the direction to shift
   * @param fac [in] the size factor along the direction to be shifted
   * @return nothing
   */
  template <typename T>
  inline void shift(Vector<T>& v, const Vector<T>& vfac, const T& fac) {
    shift(v,fac,vfac);
  }

  /**
   * @brief composite of scale and shift operations with heterogeneous shifting step.
   *
   * This is implemented with the corresponding operation for array.
   * This operation scales the Vector and then shifts it along a
   * direction with a step. The number of elements involved in this
   * operation is the minimum of all three concerned Vector objects.
   *
   * T is the type of data in vectors.
   *
   * @param v [in,out] the Vector to be scaled and shifted.
   * @param dfac [in] the factor to scale the Vector object v.
   * @param fac [in] the factor indicating the step to shift
   * @param sfac [in] the Vector object as the heterogeneous scale factor
   *                  for Vector object vfac
   * @param vfac [in] the Vector object as the direction to shift.
   * @return nothing
   */
  template <typename T>
  inline void scaleshift(Vector<T>& v, const T& dfac, const T& fac,
                  const Vector<T>& sfac, const Vector<T>& vfac) {
    unsigned int n=(v.size<vfac.size?v.size:vfac.size);
    n=(n<sfac.size?n:sfac.size);
    scaleshift(v(),dfac,fac,sfac(),vfac(),n);
  }

  /**
   * @brief composite of scale and shift operations with isotropic shifting step.
   *
   * It is implemented with the corresponding operation for array. The
   * factor indicating the step of shifting is just a constant. The number
   * of elements involved in this operation is the minimum of the numbers
   * of the elements in concerned vectors.
   *
   * T is the type of data in vectors.
   *
   * @param v [in,out] the Vector to be scaled and shifted.
   * @param dfac [in] the factor to scale the Vector object v.
   * @param fac [in] the factor indicating the step to shift
   * @param vfac [in] the Vector object as the direction to shift.
   * @return nothing
   */
  template <typename T>
  inline void scaleshift(Vector<T>& v, const T& dfac, const T& fac,
                  const Vector<T>& vfac) {
    unsigned int n=(v.size<vfac.size?v.size:vfac.size);
    scaleshift(v(),dfac,fac,vfac(),n);
  }

  /**
   * @brief shift Vector along a direction with heterogeneous steps
   *
   * It is implemented with the corresponding operation for array.
   * The number of elements involved in this operation is the minimum
   * of the numbers of elements in concerned vectors.
   *
   * T is the type of data in vectors.
   *
   * @param v [in,out] the Vector to be scaled and shifted.
   * @param fac [in] the factor indicating the step to shift
   * @param sfac [in] the Vector object as the heterogeneous scale factor
   *                  for Vector object vfac
   * @param vfac [in] the Vector object as the direction to shift.
   * @return nothing
   */
  template <typename T>
  inline void shift(Vector<T>& v, const T& fac, const Vector<T>& sfac,
             const Vector<T>& vfac) {
    unsigned int n=(v.size<vfac.size?v.size:vfac.size);
    n=(n<sfac.size?n:sfac.size);
    shift(v(),fac,sfac(),vfac(),n);
  }

  /**
   * @brief exchange contents of two vectors
   *
   * It is implemented with the corresponding operation for array. The number
   * of the elements involved in this operation is the minimum of the number
   * of elements in concerned vectors.
   *
   * T is the type of data in vectors
   *
   * @param va,vb [in,out] the Vector objects to be exchanged.
   * @return nothing
   */ 
  template <typename T>
  inline void exchange(Vector<T>& va, Vector<T>& vb) {
    unsigned int n=(va.size<vb.size?va.size:vb.size);
    exchange(va(),vb(),n);
  }

  /**
   * @brief swap two vectors
   *
   * This operation swaps the storages of two Vector objects. It is implemented
   * by exchanging the pointers and the properties. This is efficient than
   * exchange operation when the storage is large. This operation is also
   * independent of the sizes of storages.
   *
   * T is the type of data in vectors.
   *
   * @param va,vb [in,out] the Vector objects to be swapped.
   * @return nothing
   */
  template <typename T>
  inline void swap(Vector<T>& va, Vector<T>& vb) {
    swap(va.data,vb.data);
    swap(va.size,vb.size);
    swap(va.state,vb.state);
  }

  /**
   * @brief dot product of two Vector objects
   *
   * It is implemented with the corresponding operation for array.
   * The number of elements involved in this operation is the minimum of
   * the numbers of elements in concerned vectors.
   *
   * T is the type of data in vectors
   *
   * @param va,vb [in] the Vector objects to carry out dot product.
   * @return the dot product of the input Vector objects.
   */
  template <typename T>
  inline T dot(const Vector<T>& va, const Vector<T>& vb) {
    unsigned int n=(va.size<vb.size?va.size:vb.size);
    return dot(va(),vb(),n);
  }

  /**
   * @brief the square of the norm of a Vector object
   *
   * It is implemented with the corresponding operation for array. The
   * number of elements involved in this operation is the number of
   * elements of concerned Vector object.
   *
   * T is the type of data in Vector object.
   *
   * @param v [in] the input Vector object
   * @return the square of the norm of the input Vector object.
   */
  template <typename T>
  inline T normSQ(const Vector<T>& v) { return normSQ(v(),v.size); }

  /**
   * @brief the square of the norm of a Vector object with \c double elements
   *
   * This is a specification of normSQ operation for the Vector object with
   * \c double elements. It is implemented with the corresponding operation
   * for array. The number of the elements involved in this operation is
   * the size of the Vector object.
   *
   * @param v [in] the Vector object with \c double elements
   * @return the  \c double value of the square of the norm of the input
   *         Vector object.
   */
  double norm(const Vector<double>& v) { return norm(v(),v.size); }

  /**
   * @brief the summation of the absolute values of elements of Vector object
   *
   * It is implemented with the corresponding operation for array. The number
   * of the elements involved in this operation is the size of the concerned
   * Vector object.
   *
   * T is the type of data in vectors.
   *
   * @param v [in] the input Vector object.
   * @return the summation result of the absolute values of elements in
   *         the input Vector object.
   */
  template <typename T>
  inline T asum(const Vector<T>& v) { return asum(v(),v.size); }

  /**
   * @brief output Vector object to ostream
   *
   * The elements are written to ostream with tab as their separations.
   * The input Vector object is required to be available before using.
   *
   * T is the type of data in vector.
   *
   * @param os [in,out] the ostream to output
   * @param v [in] the Vector object to be output.
   * @return the ostream after output operation
   */
  template <typename T>
  ostream& operator<<(ostream& os, const Vector<T>& v) {
    assert(IsAvailable(v));
    os<<v[0];
    for(unsigned int i=1;i<v.size;++i)  os<<"\t"<<v[i];
    return os;
  }

  /**
   * @brief read Vector object from istream
   *
   * The elements of the concerned Vector object are read one by one from
   * istream. The concerned Vector object is checked for its availability
   * before read operations.
   *
   * T is the type of data in vector.
   *
   * @param is [in,out] the istream to provide data source
   * @param v [out] the Vector object storing input data
   * @return the istream after read operation
   */
  template <typename T>
  istream& operator>>(istream& is, Vector<T>& v) {
    assert(IsAvailable(v));
    for(unsigned int i=0;i<v.size;++i)  is>>v[i];
    return is;
  }

  /**
   * @brief cross product of vectors with offsets and steps for elements
   *
   * It is implemented with the corresponding operation for array. The
   * numbers of elements of the concerned vectors are used as parameters
   * indicating the sizes of the concerned arrays.
   *
   * @param va,vb [in] the Vector objects to be multiplied for cross product
   * @param v [out] the Vector object storing the output of cross product
   * @param aoff,boff,off [in] the offsets for the first used element in
                               the Vector objects va, vb, v.
   *                           They takes the default value iZero.
   * @param astep,bstep,step [in] the steps between the used elements in
   *                              the Vector objects va, vb, v.
   *                              They takes the default value lOne.
   * @return nothing
   * @note cross product only works for 3-dimensional space. That is, only
   *       three elements are used.
   */
  void crossProd(const Vector<double>& va, const Vector<double>& vb,
                 Vector<double>& v,
                 const unsigned int aoff=iZero, const unsigned int astep=lOne,
                 const unsigned int boff=iZero, const unsigned int bstep=lOne,
                 const unsigned int off=iZero, const unsigned int step=lOne) {
    crossProd(va(),vb(),v(),va.size,vb.size,v.size,
              aoff,astep,boff,bstep,off,step);
  }

}

#endif

