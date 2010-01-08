
/**
 * @file vector-base.h
 * @brief the base class for Vector object
 *
 * This file contains the definition of the base class of vector-like object.
 * Some common methods are also defined. This gives the basic interface for
 * vector-like objects. This is an important class for the data storage
 * in this package.
 *
 * @author Jun Wang (junwang.nju@gamil.com)
 */

#ifndef _Vector_Base_H_
#define _Vector_Base_H_

#include "vector-impl.h"

namespace std {

  /**
   * @brief the base class of vector-like object
   *
   * This class defines the common data and methods for vector-like objects.
   * It contains the pointers to the data, the size information and interface
   * to access the elements. Generally, this class is an encapsulation for
   * arrays of data. This encapsulation eases various applications, and
   * simplifies the interface of the related subroutines. This class is
   * declared as a class with pure virtual functions, and thus cannot be
   * instanced in practice.
   *
   * \a T
   *    the type of the elements of the internal data
   */
  template <typename T>
  class VectorBase {

    protected:

      /**
       * @brief The pointer to the storage of data
       *
       * This is the common interface to access the data.
       */
      T* Data;

      /**
       * @brief The size of the storage of data
       */
      uint nData;

      /**
       * @brief the pointer to the head of data storage
       *
       * This variable is used to store the head of storage. With this
       * variable, it is not necessary to recalculate it when we would like
       * to access the head of the data storage.
       */
      T* head_ptr;

      /**
       * @brief the pointer to the tail of data storage
       *
       * This variable is used to store the tail of storage. It points to
       * the location just after the last element of storage. With this
       * variable, it is not necessary to recalculate it when we would like
       * to access the tail of the data storage.
       */
      T* tail_ptr;

    public:

      /**
       * @brief alias for template type \a T
       */
      typedef T               DataType;

      /**
       * @brief the alias for the present class
       */
      typedef VectorBase<T>   Type;

      /**
       * @brief flag for objects as a vector
       *
       * This variable is defined to check if the concerned object is
       * vector-like. Since it is common for all instances of vector-like
       * object, this flag is defined as a \a static \a const.
       */
      static const uint IsVector;

      /**
       * @brief default initiator
       *
       * This initiator assigns all the properties as null values. After
       * this initiation, this object cannot be used.
       */
      VectorBase() : Data(NULL), nData(0), head_ptr(NULL), tail_ptr(NULL) {}

      /**
       * @brief initiator from another VectorBase object
       *
       * This is prohibited to avoid the creation of temporary object.
       * An error message is pop up.
       *
       * @param [in] VB
       *        The input VectorBase object
       */
      VectorBase(const Type& VB) { myError("vector copier is prohibited!"); }

      /**
       * @brief destructor
       *
       * This destructor just clear the data with clear() method.
       * This is defined as a virtual function since this class contains
       * a pure virtual function.
       */
      virtual ~VectorBase() { clear(); }

      /**
       * @brief clear up the data
       *
       * All the pointers and data are assigned with null values.
       * This is used in destructor.
       */
      void clear() { Data=NULL; nData=0; head_ptr=NULL; tail_ptr=NULL; }

      /**
       * @brief set up the pointers for head and tail
       *
       * The pointers for head and tail of storage are assigned. The
       * head pointer points to the first element, and the tail pointer
       * refers to the position after the last element. This function
       * should be used after the storage has been set up.
       */
      void set_HeadTail() { head_ptr=Data; tail_ptr=Data+nData; }

      /**
       * @brief copier from another VectorBase object
       *
       * It is implemented with assign() function.
       *
       * @param [in] vb
       *        the input VectorBase object
       *
       * @return the reference to present object.
       */
      Type& operator=(const Type& vb) { return assign(vb); }

      /**
       * @brief copier from an \a inputT type object
       *
       * It is implemented with assign() function. This is used for the data
       * with various kinds of input types except the VectorBase type. The
       * copier for VectorBase type data is a basic requirement of class,
       * and cannot be replaced by this function.
       *
       * \a inputT
       *    The type of the input object
       *
       * @param [in] v
       *        The input object with \a inputT type.
       *
       * @return the reference to present object.
       */
      template <typename inputT>
      Type& operator=(const inputT& v) { return assign(v); }

      /**
       * @brief the multiply-and-assign operator 
       *
       * It is implemented with scale() function.
       *
       * \a inputT
       *    The type of the input object
       *
       * @param [in] v
       *        The input object with \a inputT type.
       *
       * @return the reference to present object.
       */
      template <typename inputT>
      Type& operator*=(const inputT& v) { return scale(v); }

      /**
       * @brief the plus-and-assign operator
       *
       * It is implemented with shift() function.
       *
       * \a inputT
       *    The type of the input object.
       *
       * @param [in] v
       *        The input object with \a inputT type.
       *
       * @return the reference to present object.
       */
      template <typename inputT>
      Type& operator+=(const inputT& v) { return shift(v); }

      /**
       * @brief assign from part of external array
       *
       * It is implemented with vector_assign(). The size requirements for
       * array and present object are checked at first with assert().
       *
       * @param [in] v
       *        the pointer to the input array
       *
       * @param [in] ncopy
       *        The number of the elements to be copied
       *
       * @param [in] voffset
       *        The shift for the first element to be copied in input array.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] vstep
       *        The spacing between the two elements in input array.
       *        It takes the default value one (namely all elements are
       *        read)
       *
       * @param [in] offset
       *        The shift for the first element to accept input. It takes
       *        the default value zero (namely starting from the head)
       *
       * @param [in] step
       *        The spacing between elements accepting the input. It takes
       *        the default value one (namely all elements are written)
       *
       * @return the reference to present object.
       */
      Type& assign(const T* v, long ncopy, int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(offset+step*ncopy)<=nData);
        vector_assign(Data,v,ncopy,offset,voffset,step,vstep);
        return *this;
      }

      /**
       * @brief assign from part of another VectorBase object
       *
       * It is implemented with the assign() for explicit array.
       * The size of input vector is also checked.
       *
       * @param [in] v
       *        the VectorBase type object as input
       *
       * @param [in] ncopy
       *        The number of the elements to be copied
       *
       * @param [in] voffset
       *        The shift for the first element to be copied in input vector.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] vstep
       *        The spacing between the two elements in input vector.
       *        It takes the default value one (namely all elements are
       *        read)
       *
       * @param [in] offset
       *        The shift for the first element to accept input. It takes
       *        the default value zero (namely starting from the head)
       *
       * @param [in] step
       *        The spacing between elements accepting the input. It takes
       *        the default value one (namely all elements are written)
       *
       * @return the reference to present object.
       */
      Type& assign(const Type& v, long ncopy,
                   int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(voffset+vstep*ncopy)<=v.nData);
        return assign(v.data(),ncopy,voffset,vstep,offset,step);
      }

      /**
       * @brief assign from another VectorBase object
       *
       * This is a simplification for assign operation, just duplicating
       * the contents of input VectorBase object. When two VectorBase
       * objects have different sizes, the small one is picked. It is
       * implemented with the assign() related to the operation for
       * part of VectorBase object.
       *
       * @param [in] v
       *        The input VectorBase object
       *
       * @return the reference to present object.
       */
      Type& assign(const Type& v) {
        long n=(nData<v.nData?nData:v.nData);
        return assign(v,n);
      }

      /**
       * @brief assign value to part of content
       *
       * It is implemented with assign() operation for extern array. The
       * spacing between input elements is set as zero to read only one
       * element.
       *
       * @param [in] value
       *        The input value
       *
       * @param [in] ncopy
       *        The number of elements to be assigned
       *
       * @param [in] offset
       *        The shift for the first element to accept input. It takes
       *        the default value zero (namely starting from the head)
       *
       * @param [in] step
       *        The spacing between elements accepting the input. It takes
       *        the default value one (namely all elements are written)
       *
       * @return the reference to present object.
       */
      Type& assign(const T& value, long ncopy,
                   int offset=iZero, long step=lOne) {
        return assign(&value,ncopy,iZero,lZero,offset,step);
      }
      
      Type& assign(const T& value) { return assign(value,nData); }

      /**
       * @brief scale with part of external array
       *
       * It is implemented with vector_scale() operation. The size of
       * the internal VectorBase object is checked at first.
       *
       * @param [in] v
       *        the pointer to the input array
       *
       * @param [in] nscale
       *        The number of the elements to be scaled.
       *
       * @param [in] voffset
       *        The shift for the first element to be used in input array.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] vstep
       *        The spacing between the two elements in input array.
       *        It takes the default value one (namely all elements are
       *        read)
       *
       * @param [in] offset
       *        The shift for the first element for internal vector. It takes
       *        the default value zero (namely starting from the head)
       *
       * @param [in] step
       *        The spacing between elements for internal vector. It takes
       *        the default value one (namely all elements are written)
       *
       * @return the reference to present object.
       */
      Type& scale(const T* v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(offset+step*nscale)<=nData);
        vector_scale(Data,v,nscale,offset,voffset,step,vstep);
        return *this;
      }

      /**
       * @brief scale with a constant for part of internal vector
       *
       * It is implemented with vector_scale() operation. The size of
       * the internal VectorBase object is checked at first.
       *
       * @param [in] d
       *        the constant to scale the VectorBase object
       *
       * @param [in] nscale
       *        The number of the elements to be scaled.
       *
       * @param [in] offset
       *        The shift for the first element for internal vector. It takes
       *        the default value zero (namely starting from the head)
       *
       * @param [in] step
       *        The spacing between elements for internal vector. It takes
       *        the default value one (namely all elements are written)
       *
       * @return the reference to present object.
       */
      Type& scale(const T& d, long nscale,
                  int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(offset+step*nscale)<=nData);
        vector_scale(Data,d,nscale,offset,iZero,step,lZero);
        return *this;
      }

      /**
       * @brief scale with a constant
       *
       * It is a simplificaton for the scale operation with a constant factor.
       * it is implemented with scale() operation for part of internal
       * vector. All the elements in the internal object are all scaled.
       * That is, the number of the elements to be scaled equals to the
       * size of the internal vector.
       *
       * @param [in] d
       *        The input value
       *
       * @return the reference to present object.
       */
      Type& scale(const T& d) { return scale(d,nData); }

      /**
       * @brief scale with a VectorBase object for part of elements
       *
       * It is implemented with scale() operation for part of elements.
       * The size of the input VectorBase object is also checked.
       *
       * @param [in] v
       *        the input VectorBase object
       *
       * @param [in] nscale
       *        The number of the elements to be scaled.
       *
       * @param [in] voffset
       *        The shift for the first element to be used in input object.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] vstep
       *        The spacing between the two elements in input object.
       *        It takes the default value one (namely all elements are
       *        read)
       *
       * @param [in] offset
       *        The shift for the first element for internal vector. It takes
       *        the default value zero (namely starting from the head)
       *
       * @param [in] step
       *        The spacing between elements for internal vector. It takes
       *        the default value one (namely all elements are written)
       *
       * @return the reference to present object.
       */
      Type& scale(const Type& v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(voffset+vstep*nscale)<=v.nData);
        return scale(v.data(),nscale,voffset,vstep,offset,step);
      }

      /**
       * @brief scale with another VectorBase object
       *
       * It is a simplificaton for the operation to scale with another
       * VectorBase object. It is implemented with the scale() operation
       * for part of elements. Since there might be differences between
       * two concerned VectorBase objects, the smaller size is employed
       * in scale operation.
       *
       * @param [in] v
       *        The input VectorBase object
       *
       * @return the reference to present object.
       */
      Type& scale(const Type& v) {
        long n=(nData<v.nData?nData:v.nData);
        return scale(v,n);
      }

      /**
       * @brief generic format for shift operation
       *
       * This is a generic interface to scale internal object with
       * input array and \c ScaleT type object. It is assumed that
       * part of elements are involved in the shift operation. It is
       * implemented with vector_shift() operation. The size of the
       * internal VectorBase object is checked.
       *
       * \a ScaleT
       *    The type of quantity for scale operation
       *
       * @param [in] sv
       *        The quantity of \a ScaleT type for scale operation
       *
       * @param [in] v
       *        The array for scale operation
       *
       * @param [in] nshift
       *        The number of elements related to the shift operation.
       *
       * @param [in] soffset
       *        The shift for the first element for the object sv.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] sstep
       *        The spacing between the two elements in the object sv.
       *        It takes the default value one (namely all elements are
       *        read)
       *
       * @param [in] voffset
       *        The shift for the first element for the object v.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] vstep
       *        The spacing between the two elements in the object v.
       *        It takes the default value one (namely all elements are
       *        read)
       *
       * @param [in] offset
       *        The shift for the first element for the internal object.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between the two elements in the internal object.
       *        It takes the default value one (namely all elements are
       *        read)
       *
       * @return the reference to present object.
       */
      template <typename ScaleT>
      Type& shift(const ScaleT& sv, const T* v, long nshift,
                  int soffset=iZero, long sstep=lOne,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(offset+step*nshift)<=nData);
        vector_shift(Data,sv,v,nshift,offset,soffset,voffset,step,sstep,vstep);
        return *this;
      }

      /**
       * @brief shift with constant and VectorBase object for part of elements
       *
       * This is a typical case for shift operation. The input constant
       * and the input vector are multiplied at first. The resultant
       * vector is addeed to the internal vector. The size of the input
       * vector is checked.
       *
       * @param [in] value
       *        The input constant
       *
       * @param [in] v
       *        The input VectorBase object.
       *
       * @param [in] nshift
       *        The number of elements related to the shift operation.
       *
       * @param [in] voffset
       *        The shift for the first element for the object v.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] vstep
       *        The spacing between the two elements in the object v.
       *        It takes the default value one (namely all elements are
       *        read)
       *
       * @param [in] offset
       *        The shift for the first element for the internal object.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between the two elements in the internal object.
       *        It takes the default value one (namely all elements are
       *        read)
       *
       * @return the reference to present object.
       */
      Type& shift(const T& value, const Type& v, long nshift,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(voffset+vstep*nshift)<=v.nData);
        return shift(value,v.Data,nshift,
                     iZero,lZero,voffset,vstep,offset,step);
      }
      
      /**
       * @brief shift with a constant and a VectorBase object
       *
       * This is a simplification for the operation to shift with
       * a constant and a VectorBase object. It is implemented with
       * the shift() operation for part of the intermal vector.
       * Since the sizes for input vector and the internal vectort
       * may be different, the smaller one is chosen.
       *
       * @param [in] value
       *        The input constant
       *
       * @param [in] v
       *        The input VectorBase object
       *
       * @return the reference to present object.
       */
      Type& shift(const T& value, const Type& v) {
        long n=(nData<v.nData?nData:v.nData);
        return shift(value,v,n);
      }
      
      /**
       * @brief shift with a constant
       *
       * This operation shifts the concerned elements with a constant.
       * It is implemented with shift() operation for external array.
       * The constant is used as an array with spacing between elements
       * being zero.
       *
       * @param [in] value
       *        The input constant
       *
       * @param [in] offset
       *        The shift for the first element for the internal object.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between the two elements in the internal object.
       *        It takes the default value one (namely all elements are
       *        read)
       *
       * @return the reference to present object.
       */
      Type& shift(const T& value, int offset=iZero, long step=lOne) {
        return shift(value,&dOne,nData,iZero,lZero,iZero,lZero,offset,step);
      }

      /**
       * @brief shift with a VectorBase object
       *
       * This is a simplification for shift() operation with a VectorBase
       * object. It is implemented with shift() for a constant and a
       * VectorBase object. The constant is assigned with \c double type
       * one.
       *
       * @param [in] v
       *        The input VectorBase object
       *
       * @return the reference to present object.
       */
      Type& shift(const Type& v) { return shift(dOne,v); }

      /**
       * @brief shift with two VectorBase object
       *
       * It is a simplification of shift operation with two VectorBase
       * objects. It is implemented with scaleshift() operation
       * with the concerned constants being \c double type one.
       *
       * @param [in] ShiftFv
       *        The input VectorBase object to shift the vector v.
       *
       * @param [in] v
       *        The input VectorBase object related to shift operation.
       *
       * @return the reference to present object.
       */
      Type& shift(const Type& ShiftFv, const Type& v) {
        return scaleshift(dOne,dOne,ShiftFv,v);
      }

      /**
       * @brief shift with a constant and two VectorBase objects
       *
       * It is a simplification for shift operation with two VectorBase
       * objects and a constant. The scale constant for the internal
       * VectorBase object is set as \c double type one. It is implemented
       * with scaleshift() operation for two constants and two VectorBase
       * objects.
       *
       * @param [in] ShiftF
       *        The input constant as the factor to shift the vector v
       *
       * @param [in] ShiftFv
       *        The input VectorBase object to shift the vector v
       *
       * @param [in] v
       *        The input VectorBase object related to shift operation.
       *
       * @return the reference to present object.
       */
      Type& shift(const T& ShiftF, const Type& ShiftFv, const Type& v) {
        return scaleshift(dOne,ShiftF,ShiftFv,v);
      }

      /**
       * @brief the composite operation of scale and shift with external array
       *
       * This is a composite operation. One of the input array is scaled with
       * another input array and an input constant. At the same time, the
       * internal object is also scaled with another input costant. These
       * two scaled data are added together, and finally stored internally.
       * It is implemented with vector_scaleshift() operation. The size of
       * the internal object is checked.
       *
       * @param [in] ScaleF
       *        The constant to scale the internal object
       *
       * @param [in] ShiftF
       *        The constanr to scale the vector v
       *
       * @param [in] ShiftFv
       *        The input array to shift the vector v
       *
       * @param [in] v
       *        The input array related to the shift operation
       *
       * @param [in] nscaleshift
       *        The number of elements related to this operation
       *
       * @param [in] sfoffset
       *        The shift for the first element for the object ShiftFv.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] sfstep
       *        The spacing between the two elements in the object ShiftFv.
       *        It takes the default value one (namely all elements are
       *        read)
       *
       * @param [in] voffset
       *        The shift for the first element for the object v.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] vstep
       *        The spacing between the two elements in the object v.
       *        It takes the default value one (namely all elements are
       *        read)
       *
       * @param [in] offset
       *        The shift for the first element for the internal object.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between the two elements in the internal object.
       *        It takes the default value one (namely all elements are
       *        read)
       *
       * @return the reference to present object.
       */
      Type& scaleshift(const T& ScaleF, const T& ShiftF, const T* ShiftFv,
                       const T* v, long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(offset+step*nscaleshift)<=nData);
        vector_scaleshift(Data,ScaleF,ShiftF,ShiftFv,v,nscaleshift,
                          offset,sfoffset,voffset,step,sfstep,vstep);
        return *this;
      }

      /**
       * @brief composite operation of scale and shift with external vectors
       *
       * It is implemented with the scaleshift() operation related to external
       * arrays. The sizes of input vectors are checked.
       *
       * @param [in] ScaleF
       *        The constant to scale the internal object
       *
       * @param [in] ShiftF
       *        The constanr to scale the vector v
       *
       * @param [in] ShiftFv
       *        The input vector to shift the vector v
       *
       * @param [in] v
       *        The input vector related to the shift operation
       *
       * @param [in] nscaleshift
       *        The number of elements related to this operation
       *
       * @param [in] sfoffset
       *        The shift for the first element for the object ShiftFv.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] sfstep
       *        The spacing between the two elements in the object ShiftFv.
       *        It takes the default value one (namely all elements are
       *        read)
       *
       * @param [in] voffset
       *        The shift for the first element for the object v.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] vstep
       *        The spacing between the two elements in the object v.
       *        It takes the default value one (namely all elements are
       *        read)
       *
       * @param [in] offset
       *        The shift for the first element for the internal object.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between the two elements in the internal object.
       *        It takes the default value one (namely all elements are
       *        read)
       *
       * @return the reference to present object.
       */
      Type& scaleshift(const T& ScaleF, const T& ShiftF, const Type& ShiftFv,
                       const Type& v, long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(sfoffset+sfstep*nscaleshift)<=ShiftFv.nData);
        assert(static_cast<uint>(voffset+vstep*nscaleshift)<=v.nData);
        return scaleshift(ScaleF,ShiftF,ShiftFv.Data,v.Data,nscaleshift,
                          sfoffset,sfstep,voffset,vstep,offset,step);
      }
      
      Type& scaleshift(const T& ScaleF, const T& ShiftF, const Type& ShiftFv,
                       const Type& v) {
        long n;
        n=(nData<ShiftFv.nData?nData:ShiftFv.nData);
        n=(static_cast<uint>(n)<v.nData?n:v.nData);
        return scaleshift(ScaleF,ShiftF,ShiftFv,v,n);
      }

      Type& scaleshift(const T& ScaleF, const T& ShiftF, const Type& v,
                       long nscaleshift,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        scale(ScaleF,nscaleshift,offset,step);
        return shift(ShiftF,v,nscaleshift,voffset,vstep,offset,step);
      }
      
      Type& scaleshift(const T& ScaleF, const T& ShiftF, const Type& v) {
        long n=(nData<v.nData?nData:v.nData);
        return scaleshift(ScaleF,ShiftF,v,n);
      }

      T* data() { return Data; }

      const T* data() const { return Data; }

      /**
       * @brief head to this object
       *
       * Just give the head pointer for the internal array
       *
       * @return the constant pointer to the head of internal array.
       */
      const T* begin() const { return head_ptr; }

      const T* end() const { return tail_ptr; }

      const uint& size() const { return nData; }

      T& operator[](const uint i) {
        assert(i<nData);
        return *(Data+i);
      }

      const T& operator[](const uint i) const {
        assert(i<nData);
        return *(Data+i);
      }

      Type& exchange(T* v, long nswap, int voffset=iZero, long vstep=lOne,
                     int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(offset+step*nswap)<=nData);
        vector_swap(Data,v,nswap,offset,voffset,step,vstep);
        return *this;
      }

      Type& exchange(Type& v, long nswap,
                     int voffset=iZero, long vstep=lOne,
                     int offset=iZero, long step=lOne) {
        assert(static_cast<uint>(voffset+vstep*nswap)<=v.nData);
        return exchange(v.Data,nswap,voffset,vstep,offset,step);
      }

      Type& exchange(Type& v) {
        long n=(nData<v.nData?nData:v.nData);
        return exchange(v,n);
      }

      bool isAvailable() const { return Data!=NULL; }

      virtual const char* type() = 0;

  };

  template <typename T>
  void exchange(VectorBase<T>& va, VectorBase<T>& vb) {
    va.exchange(vb);
  }

  template <typename T>
  const uint VectorBase<T>::IsVector=1;

  template <typename T>
  ostream& operator<<(ostream& os, const VectorBase<T>& v) {
    uint n=v.size();
    assert(n>0);
    os<<v[0];
    for(uint i=1;i<n;++i) os<<"\t"<<v[i];
    return os;
  }

}

#endif

