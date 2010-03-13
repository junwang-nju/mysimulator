
/**
 * @file property-list.h
 * @brief list structure of property
 *
 * This file defines a fundamental type for simulation package. This type
 * is the basic object to be operated by various procedures. This kind of
 * definition enables various kinds of methods to access the content for
 * efficiency. This format increases the flexibility to use this API and
 * to develop in future.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Property_List_H_
#define _Property_List_H_

#include "var-vector.h"
#include "ref-vector.h"

namespace std {

  /**
   * @brief the list type containing various properties
   *
   * This type is a variant of vector-like object. The internal data
   * are re-arranged in a linear vector. This kind of organization
   * enables various accessments to the data, through the vector of
   * units or through the vector of the values. These interfaces are
   * used for various applications based on the consideration of efficiency.
   * The internal types are defined with template types to provide
   * flexibility. Besides, some methods for vectors are re-defined to
   * include the operations for internal vectors of values.
   *
   * \a ListType
   *    The template type of list. This describes the type of vectors
   *    containing the units. Defaultly, varVector is used.
   *
   * \a PropertyType
   *    The template type containing properties. The unit of property
   *    is assumed as a vector of certain data. This gives out the
   *    type of vector to define the property. As a part of internal
   *    data, it takes refVector as the default type.
   *
   * \a DataType
   *    The type of data in the unit of property. It takes a default
   *    type of \c double.
   *
   * \a DataVecType
   *    The template type containing values. This gives out the type of
   *    vector to contain the values. This type is used internally. It
   *    takes varVector as the default type.
   */
	template <template <typename> class ListType=varVector,
            template <typename> class PropertyType=refVector,
            typename DataType=double,
            template <typename> class DataVecType=varVector>
	class PropertyList : public ListType<PropertyType<DataType> >{
    public:
      /**
       * @brief alias of the type for list of property
       */
      typedef PropertyList<ListType,PropertyType,DataType,DataVecType>  
                                                            Type;
      /**
       * @brief alias of the type for vector of units (type of parent class)
       */
      typedef ListType<PropertyType<DataType> >             ParentType;
      /**
       * @brief alias for the type of property
       */
      typedef PropertyType<DataType>                        Property;
      /**
       * @brief declaration of the internal list containing the values
       */
      DataVecType<DataType> PropertyData;

      /**
       * @brief default initiator
       *
       * Just initiate the parent class and list of internal data with
       * no parameters.
       */
      PropertyList() : ParentType(), PropertyData() {}
      /**
       * @brief initiator with another list of property
       *
       * This is prohibited by just popping up an error.
       *
       * @param [in] PL
       *        The input list of properties.
       */
      PropertyList(const Type& PL) {
        myError("copier for property list is prohibited!");
      }
      
      /**
       * @brief build up the structure based on size information
       *
       * The structure is defined as the relation between vector of
       * units of property and vector of internal values. The size
       * information describes the sizes of vectors containing units
       * or internal values. This function sets up the size of two
       * kinds of vectors, and sets up the relations with refer() method
       * of vector.
       *
       * @param [in] ShapeOffset
       *        The starting location of data of unit in vector of values
       *
       * @param [in] ShapeSize
       *        The size of the data of unit
       *
       * @return the reference to the present object
       *
       * @note There are some redundancy for the input size information.
       */
      Type& BuildStructure(const VectorBase<uint>& ShapeOffset,
                           const VectorBase<uint>& ShapeSize) {
        uint n=ShapeSize.size();
        assert(this->size()==n);
        assert(ShapeOffset.size()==n);
        uint num=ShapeOffset[n-1]+ShapeSize[n-1];
        PropertyData.allocate(num);
        for(uint i=0;i<n;++i)
          this->operator[](i).refer(PropertyData,ShapeOffset[i],ShapeSize[i]);
      	return *this;
      }
      /**
       * @brief swap with another list of property
       *
       * Just swap the vectors of units and of values.
       *
       * @param [in,out] PL
       *        The list of property to be swapped.
       */
      void swap(Type& PL) {
        static_cast<ParentType*>(this)->swap(static_cast<ParentType&>(PL));
        PropertyData.swap(PL.PropertyData);
      }
      /**
       * @brief clear the internal data and structure
       *
       * Just clear the vectors of units and of the values.
       */
      void clear() {
        PropertyData.clear();
        static_cast<ParentType*>(this)->clear();
      }

      /**
       * @brief copier from another list of property
       *
       * It is implemented with assign() method.
       *
       * @param [in] vb
       *        The input list of property
       *
       * @return the reference to the present object
       */
      Type& operator=(const Type& vb) { return assign(vb); }

      /**
       * @brief copier from an \a inputT type object
       *
       * It is implemented with assign() method.
       *
       * \a inputT
       *    The type of the input object
       *
       * @param [in] v
       *        The input \a inputT type object
       *
       * @return the reference to the present object
       */
      template <typename inputT>
      Type& operator=(const inputT& v) { return assign(v); }

      /**
       * @brief scale with an \a inputT type object
       *
       * It is implemented with scale() method.
       *
       * \a inputT
       *    The type of the input object
       *
       * @param [in] v
       *        The input \a inputT type object
       *
       * @return the reference to the present object
       */
      template <typename inputT>
      Type& operator*=(const inputT& v) { return scale(v); }

      /**
       * @brief shift with an \a inputT type object
       *
       * It is implemented with shift() method.
       *
       * \a inputT
       *    The type of the input object
       *
       * @param [in] v
       *        The input \a inputT type object
       *
       * @return the reference to the present object
       */
      template <typename inputT>
      Type& operator+=(const inputT& v) { return shift(v); }

      /**
       * @brief assign part from an array
       *
       * Just assign the internal vector of values with the input array.
       *
       * @param [in] v
       *        The input array
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
       *        The spacing between the two elements in input array. It takes
       *        the default value one (namely all elements are read)
       *
       * @param [in] offset
       *        The shift for the first element to accept the input array.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between elements accepting the input. It takes
       *        the default value one (namely all elements are written)
       *
       * @return the reference to present object
       */
      Type& assign(const DataType* v, long ncopy, int voffset=iZero,
                   long vstep=lOne, int offset=iZero, long step=lOne) {
        PropertyData.assign(v,ncopy,voffset,vstep,offset,step);
        return *this;
      }

      /**
       * @brief assign part from a VectorBase object
       *
       * Just assign the internal vector of values with the input VectorBase
       * object.
       *
       * @param [in] v
       *        The input VectorBase object.
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
       *        The spacing between the two elements in input array. It takes
       *        the default value one (namely all elements are read)
       *
       * @param [in] offset
       *        The shift for the first element to accept the input array.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between elements accepting the input. It takes
       *        the default value one (namely all elements are written)
       *
       * @return the reference to present object
       */
      Type& assign(const VectorBase<DataType>& v, long ncopy,
                   int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        PropertyData.assign(v,ncopy,voffset,vstep,offset,step);
        return *this;
      }

      /**
       * @brief assign part from a list of properties
       *
       * Just assign the internal vector of values with the internal
       * vector of values of the input list of property.
       *
       * @param [in] v
       *        The input VectorBase object.
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
       *        The spacing between the two elements in input array. It takes
       *        the default value one (namely all elements are read)
       *
       * @param [in] offset
       *        The shift for the first element to accept the input array.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between elements accepting the input. It takes
       *        the default value one (namely all elements are written)
       *
       * @return the reference to present object
       * @note this assignment is not based on the level of units, but
       *       is based on the level of internal values.
       */
      Type& assign(const Type& v, long ncopy,
                   int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        PropertyData.assign(v.PropertyData,ncopy,voffset,vstep,offset,step);
        return *this;
      }

      /**
       * @brief assign with a VectorBase object
       *
       * It is implemented with the assign() method of the internal vector
       * of the values.
       *
       * @param [in] v
       *        The input VectorBase object
       *
       * @return the reference to the present object
       */
      Type& assign(const VectorBase<DataType>& v) {
        PropertyData.assign(v);
        return *this;
      }

      /**
       * @brief assign from another list of property
       *
       * It is implemented with the assign() method of the internal vector
       * of the values. The corresponding vector of input object is transfered
       * into this method as parameter.
       *
       * @param [in] v
       *        The input list of property
       *
       * @return the reference to the present object
       * @note It is assumed that these two lists share the same structure
       *       and their structures have been set up.
       */
      Type& assign(const Type& v) {
        PropertyData.assign(v.PropertyData);
        return *this;
      }

      /**
       * @brief assign part of contents with a \a DataType type value
       *
       * It is implemented with the method assign() of internal vector
       * of values.
       *
       * @param [in] value
       *        The input value
       *
       * @param [in] ncopy
       *        The number of the elements to be copied
       *
       * @param [in] offset
       *        The shift for the first element to accept the input array.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between elements accepting the input. It takes
       *        the default value one (namely all elements are written)
       *
       * @return the reference to the present object
       */
      Type& assign(const DataType& value, long ncopy,
                   int offset=iZero, long step=lOne) {
        PropertyData.assign(value,ncopy,offset,step);
        return *this;
      }
      
      /**
       * @brief assign with a \a DataType type value
       *
       * It is implemented with the method assign() of internal vector
       * of values.
       *
       * @param [in] value
       *        The input value
       *
       * @return the reference to the present object
       */
      Type& assign(const DataType& value) {
        PropertyData.assign(value);
        return *this;
      }

      /**
       * @brief scale part of content with an array
       *
       * It is implemented with the scale() method of the internal vector
       * of values.
       *
       * @param [in] v
       *        The input array containing the scaling factors
       *
       * @param nscale
       *        The number of the elements to be scaled.
       *
       * @param [in] voffset
       *        The shift for the first element used for scaling in input array.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] vstep
       *        The spacing between the two elements in input array. It takes
       *        the default value one (namely all elements are read)
       *
       * @param [in] offset
       *        The shift for the first element to accept the input array.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between elements accepting the input. It takes
       *        the default value one (namely all elements are written)
       *
       * @return the reference to the present object
       */
      Type& scale(const DataType* v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        PropertyData.scale(v,nscale,voffset,vstep,offset,step);
        return *this;
      }

      /**
       * @brief scale part of content with a \a DataType value
       *
       * It just scales the internal vector of values with the input
       * parameters.
       *
       * @param [in] d
       *        The input value as the scale factor
       *
       * @param [in] nscale
       *        The number of the elements to be scaled
       *
       * @param [in] offset
       *        The shift for the first element to accept the input array.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between elements accepting the input. It takes
       *        the default value one (namely all elements are written)
       *
       * @return the reference to the present object
       */
      Type& scale(const DataType& d, long nscale,
                  int offset=iZero, long step=lOne) {
        PropertyData.scale(d,nscale,offset,step);
        return *this;
      }

      /**
       * @brief scale with a \a DataType type value
       *
       * It is implemented with the scale() method of the internal vector
       * of values.
       *
       * @param [in] d
       *        The input value as scaling factor
       *
       * @return the reference to the present object
       */
      Type& scale(const DataType& d) {
        PropertyData.scale(d);
        return *this;
      }

      /**
       * @brief scale part of content with a VectorBase object
       *
       * It is implemented with the scale() method of the internal vector
       * of values.
       *
       * @param [in] v
       *        The input VectorBase object containing the scaling factors
       *
       * @param nscale
       *        The number of the elements to be scaled.
       *
       * @param [in] voffset
       *        The shift for first element used for scaling in input vector.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] vstep
       *        The spacing between the two elements in input vector. It takes
       *        the default value one (namely all elements are read)
       *
       * @param [in] offset
       *        The shift for the first element to accept the input.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between elements accepting the input. It takes
       *        the default value one (namely all elements are written)
       *
       * @return the reference to the present object
       */
      Type& scale(const VectorBase<DataType>& v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        PropertyData.scale(v,nscale,voffset,vstep,offset,step);
        return *this;
      }

      /**
       * @brief scale part of content with a list of property
       *
       * It is implemented with the scale() method of the internal vector
       * of values. The corresponding internal vector of the input object
       * is used as the input parameter for the above method.
       *
       * @param [in] v
       *        The input list of property
       *
       * @param nscale
       *        The number of the elements to be scaled.
       *
       * @param [in] voffset
       *        The shift for the first element used for scaling in input list.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] vstep
       *        The spacing between the two elements in input list. It takes
       *        the default value one (namely all elements are read)
       *
       * @param [in] offset
       *        The shift for the first element to accept the input.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between elements accepting the input. It takes
       *        the default value one (namely all elements are written)
       *
       * @return the reference to the present object
       * @note This method practically operates the internal vectors of
       *       values. It does not operate the units, and does not touch
       *       the internal structures.
       */
      Type& scale(const Type& v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        PropertyData.scale(v.PropertyData,nscale,voffset,vstep,offset,step);
        return *this;
      }

      /**
       * @brief scale with a VectorBase object
       *
       * It is implemented with the scale() method of the internal vector
       * of values.
       *
       * @param [in] v
       *        The input VectorBase object
       *
       * @return the reference to the present object
       */
      Type& scale(const VectorBase<DataType>& v) {
        PropertyData.scale(v);
        return *this;
      }

      /**
       * @brief scale with another list of property
       *
       * It is implemented with the scale() method of the internal vector
       * of values. The internal vector of values in input list is used
       * as the parameter of the above mentioned method.
       *
       * @param [in] v
       *        The input list of property
       *
       * @return the reference to the present object
       */
      Type& scale(const Type& v) {
        PropertyData.scale(v.PropertyData);
        return *this;
      }

      /**
       * @brief shift part of content with \a ScaleT type object and an array
       *
       * It is implemented with the shift() method of the internal vector
       * of values.
       *
       * \a ScaleT
       *    The type of the input object to scale the input array
       *
       * @param [in] sv
       *        The input \a ScaleT type object to scale input array v
       *
       * @param [in] v
       *        The input array containing the shift direction
       *
       * @param [in] nshift
       *        The number of elements to be shifted.
       *
       * @param [in] soffset
       *        The shift for the first element as scaling factor for the
       *        input array. It takes the default value zero (namely starting
       *        from the first element)
       *
       * @param [in] sstep
       *        The spacing between the two elements in input object. It takes
       *        the default value one (namely all elements are read)
       *
       * @param [in] voffset
       *        The shift for the first element as shift direction in the
       *        input array. It takes the default value zero (namely starting
       *        from the first element)
       *
       * @param [in] vstep
       *        The spacing between the two elements in input array. It takes
       *        the default value one (namely all elements are read)
       *
       * @param [in] offset
       *        The shift for the first element to accept the input.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between elements accepting the input. It takes
       *        the default value one (namely all elements are written)
       *
       * @return the reference to the present object
       */
      template <typename ScaleT>
      Type& shift(const ScaleT& sv, const DataType* v, long nshift,
                  int soffset=iZero, long sstep=lOne,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        PropertyData.shift(sv,v,nshift,soffset,sstep,voffset,vstep,
                           offset,step);
        return *this;
      }

      /**
       * @brief shift part of content with constant and VectorBase object
       *
       * It is implemented with the shift() method of the internal vector
       * of values.
       *
       * @param [in] value
       *        The input constant to scale the vector v
       *
       * @param [in] v
       *        The input VectorBase object indicating the shift direction
       *
       * @param [in] nshift
       *        The number of elements to be shifted.
       *
       * @param [in] voffset
       *        The shift for the first element as shift direction in the
       *        input vector. It takes the default value zero (namely starting
       *        from the first element)
       *
       * @param [in] vstep
       *        The spacing between the two elements in input vector. It takes
       *        the default value one (namely all elements are read)
       *
       * @param [in] offset
       *        The shift for the first element to accept the input.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between elements accepting the input. It takes
       *        the default value one (namely all elements are written)
       *
       * @return the reference to the present object
       */
      Type& shift(const DataType& value, const VectorBase<DataType>& v,
                  long nshift, int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        PropertyData.shift(value,v,nshift,voffset,vstep,offset,step);
        return *this;
      }

      /**
       * @brief shift part of content with constant and list of property
       *
       * It is implemented with the shift() method of the internal vector
       * of values. The internal vector of values in input list is used
       * as the parameter of internal shift operation.
       *
       * @param [in] value
       *        The input constant to scale the list v
       *
       * @param [in] v
       *        The input list of property
       *
       * @param [in] nshift
       *        The number of elements to be shifted.
       *
       * @param [in] voffset
       *        The shift for the first element as shift direction in the
       *        input list. It takes the default value zero (namely starting
       *        from the first element)
       *
       * @param [in] vstep
       *        The spacing between the two elements in input list. It takes
       *        the default value one (namely all elements are read)
       *
       * @param [in] offset
       *        The shift for the first element to accept the input.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between elements accepting the input. It takes
       *        the default value one (namely all elements are written)
       *
       * @return the reference to the present object
       */
      Type& shift(const DataType& value, const Type& v,
                  long nshift, int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        PropertyData.shift(value,v,PropertyData,nshift,
                           voffset,vstep,offset,step);
        return *this;
      }
      
      /**
       * @brief shift with constant and VectorBase object
       *
       * It is implemented with the shift() method of the internal vector
       * of values.
       *
       * @param [in] value
       *        The input constant to scale the vector v
       *
       * @param [in] v
       *        The input VectorBase object indicating the shift direction
       *
       * @return the reference to the present object
       */
      Type& shift(const DataType& value, const VectorBase<DataType>& v) {
        PropertyData.shift(value,v);
        return *this;
      }

      /**
       * @brief shift with constant and list of property
       *
       * It is implemented with the shift() method of the internal vector
       * of values.
       *
       * @param [in] value
       *        The input constant to scale the list v
       *
       * @param [in] v
       *        The input list of property
       *
       * @return the reference to the present object
       */
      Type& shift(const DataType& value, const Type& v) {
        PropertyData.shift(value,v.PropertyData);
        return *this;
      }
      
      /**
       * @brief shift part of content with a constant
       *
       * It is implemented with the shift() method of the internal vector
       * of values.
       *
       * @param [in] value
       *        The input constant to shift the component of internal vector
       *
       * @param [in] offset
       *        The shift for the first element to accept the input.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between elements accepting the input. It takes
       *        the default value one (namely all elements are written)
       *
       * @return the reference to the present object
       */
      Type& shift(const DataType& value, int offset=iZero, long step=lOne) {
        PropertyData.shift(value,offset,step);
        return *this;
      }

      /**
       * @brief shift with VectorBase object
       *
       * It is implemented with the shift() method for part of content.
       * The constant related to the shift is set as one.
       *
       * @param [in] v
       *        The input VectorBase object indicating the shift direction
       *
       * @return the reference to the present object
       */
      Type& shift(const VectorBase<DataType>& v) { return shift(dOne,v); }

      /**
       * @brief shift with list of property
       *
       * It is implemented with the shift() method for part of content.
       * The constant related to the shift is set as one.
       *
       * @param [in] v
       *        The input list of property. 
       *
       * @return the reference to the present object
       */
      Type& shift(const Type& v) { return shift(dOne,v); }

      /**
       * @brief shift with two vector-like objects
       *
       * It is implemented with the shift() method with a constant
       * and two vector-like objects. The concerned constant is set as one.
       *
       * \a vTypeA
       *    The type of vector for the factor to scale the direction
       *
       * \a vTypeB
       *    The type of vector discribing the shift direction
       *
       * @param [in] ShiftFv
       *        The vector object as the factor to scale the vector v
       *
       * @param [in] v
       *        The vector object describing the direction of shift
       *
       * @return the reference to the present object
       */
      template <typename vTypeA, typename vTypeB>
      Type& shift(const vTypeA& ShiftFv, const vTypeB& v) {
        return shift(dOne,ShiftFv,v);
      }

      /**
       * @brief shift with a constant and two vector-like objects
       *
       * It is implemented with the scaleshift() method of the internal
       * vector of values. The factor to scale the internal vector is
       * set as one.
       *
       * \a vTypeA
       *    The type of vector for the factor to scale the direction
       *
       * \a vTypeB
       *    The type of vector discribing the shift direction
       *
       * @param [in] ShiftF
       *        The input constant to scale the vector v
       *
       * @param [in] ShiftFv
       *        The input vector object to scale the vector v
       *
       * @param [in] v
       *        The input vector indicating the shift direction
       *
       * @return the reference to the present object
       */
      template <typename vTypeA, typename vTypeB>
      Type& shift(const DataType& ShiftF,
                  const vTypeA& ShiftFv, const vTypeB& v) {
        PropertyData.scaleshift(dOne,ShiftF,ShiftFv,v);
        return *this;
      }

      /**
       * @brief composite operation of scale and shift for part of content with two constants and two arrays
       *
       * It is implemented with the scaleshift() method of the internal
       * vector of values. 
       *
       * @param [in] ScaleF
       *        The input constant to scale the internal vector of values
       *
       * @param [in] ShiftF
       *        The input constant to scale the array v
       *
       * @param [in] ShiftFv
       *        The input array to scale the array v
       *
       * @param [in] v
       *        The input array describing the shift direction
       *
       * @param [in] nscaleshift
       *        The number of elements related to the operation
       *
       * @param [in] sfoffset
       *        The shift for the first element of array containing the
       *        scaling factor for the input array v. It takes the default
       *        value zero (namely starting from the first element)
       *
       * @param [in] sfstep
       *        The spacing between the two elements in input object. It takes
       *        the default value one (namely all elements are read)
       *
       * @param [in] voffset
       *        The shift for the first element of array describing the
       *        searching direction. It takes the default value zero (namely
       *        starting from the first element)
       *
       * @param [in] vstep
       *        The spacing between the two elements in input object. It takes
       *        the default value one (namely all elements are read)
       *
       * @param [in] offset
       *        The shift for the first element of object to accept input.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between the two elements to accept inputs. It
       *        takes the default value one (namely all elements are read)
       *
       * @return the reference to the present object
       */
      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const DataType* ShiftFv, const DataType* v,
                       long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        PropertyData.scaleshift(ScaleF,ShiftF,ShiftFv,v,nscaleshift,
                                sfoffset,sfstep,voffset,vstep,offset,step);
        return *this;
      }

      /**
       * @brief composite operation of scale and shift for part of content with two constants and two VectorBase objects
       *
       * It is implemented with the scaleshift() method of the internal
       * vector of values. 
       *
       * @param [in] ScaleF
       *        The input constant to scale the internal vector of values
       *
       * @param [in] ShiftF
       *        The input constant to scale the vector v
       *
       * @param [in] ShiftFv
       *        The input VectorBase objec to scale the vector v
       *
       * @param [in] v
       *        The input VectorBase object describing the shift direction
       *
       * @param [in] nscaleshift
       *        The number of elements related to the operation
       *
       * @param [in] sfoffset
       *        The shift for the first element of vector containing the
       *        scaling factor for the input vector v. It takes the default
       *        value zero (namely starting from the first element)
       *
       * @param [in] sfstep
       *        The spacing between the two elements in input object. It takes
       *        the default value one (namely all elements are read)
       *
       * @param [in] voffset
       *        The shift for the first element of vector describing the
       *        searching direction. It takes the default value zero (namely
       *        starting from the first element)
       *
       * @param [in] vstep
       *        The spacing between the two elements in input object. It takes
       *        the default value one (namely all elements are read)
       *
       * @param [in] offset
       *        The shift for the first element of object to accept input.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between the two elements to accept inputs. It
       *        takes the default value one (namely all elements are read)
       *
       * @return the reference to the present object
       */
      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const VectorBase<DataType>& ShiftFv,
                       const VectorBase<DataType>& v,long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        PropertyData.scaleshift(ScaleF,ShiftF,ShiftFv,v,nscaleshift,
                                sfoffset,sfstep,voffset,vstep,offset,step);
        return *this;
      }

      /**
       * @brief composite operation of scale and shift for part of content with two constants, a VectorBase object, and a list of property
       *
       * It is implemented with the scaleshift() method of the internal
       * vector of values. 
       *
       * @param [in] ScaleF
       *        The input constant to scale the internal vector of values
       *
       * @param [in] ShiftF
       *        The input constant to scale the vector v
       *
       * @param [in] ShiftFv
       *        The input VectorBase objec to scale the vector v
       *
       * @param [in] v
       *        The input list of property. The internal vector describes
       *        the shift direction
       *
       * @param [in] nscaleshift
       *        The number of elements related to the operation
       *
       * @param [in] sfoffset
       *        The shift for the first element of vector containing the
       *        scaling factor for the input vector v. It takes the default
       *        value zero (namely starting from the first element)
       *
       * @param [in] sfstep
       *        The spacing between the two elements in input object. It takes
       *        the default value one (namely all elements are read)
       *
       * @param [in] voffset
       *        The shift for the first element of list describing the
       *        searching direction. It takes the default value zero (namely
       *        starting from the first element)
       *
       * @param [in] vstep
       *        The spacing between the two elements in input object. It takes
       *        the default value one (namely all elements are read)
       *
       * @param [in] offset
       *        The shift for the first element of object to accept input.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between the two elements to accept inputs. It
       *        takes the default value one (namely all elements are read)
       *
       * @return the reference to the present object
       */
      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const VectorBase<DataType>& ShiftFv,
                       const Type& v,long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        PropertyData.scaleshift(ScaleF,ShiftF,ShiftFv,v.PropertyData,
                                nscaleshift,
                                sfoffset,sfstep,voffset,vstep,offset,step);
        return *this;
      }

      /**
       * @brief composite operation of scale and shift for part of content with two constants, a list of property and a VectorBase object
       *
       * It is implemented with the scaleshift() method of the internal
       * vector of values. 
       *
       * @param [in] ScaleF
       *        The input constant to scale the internal vector of values
       *
       * @param [in] ShiftF
       *        The input constant to scale the vector v
       *
       * @param [in] ShiftFv
       *        The input list of property. The internal vector of this list
       *        is used to scale the vector v
       *
       * @param [in] v
       *        The input VectorBase object describing the shift direction
       *
       * @param [in] nscaleshift
       *        The number of elements related to the operation
       *
       * @param [in] sfoffset
       *        The shift for the first element of list containing the
       *        scaling factor for the input vector v. It takes the default
       *        value zero (namely starting from the first element)
       *
       * @param [in] sfstep
       *        The spacing between the two elements in input object. It takes
       *        the default value one (namely all elements are read)
       *
       * @param [in] voffset
       *        The shift for the first element of vector describing the
       *        searching direction. It takes the default value zero (namely
       *        starting from the first element)
       *
       * @param [in] vstep
       *        The spacing between the two elements in input object. It takes
       *        the default value one (namely all elements are read)
       *
       * @param [in] offset
       *        The shift for the first element of object to accept input.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between the two elements to accept inputs. It
       *        takes the default value one (namely all elements are read)
       *
       * @return the reference to the present object
       */
      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const Type& ShiftFv,
                       const VectorBase<DataType>& v,long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        PropertyData.scaleshift(ScaleF,ShiftF,ShiftFv.PropertyData,v,
                                nscaleshift,
                                sfoffset,sfstep,voffset,vstep,offset,step);
        return *this;
      }

      /**
       * @brief composite operation of scale and shift for part of content with two constants and two lists of property
       *
       * It is implemented with the scaleshift() method of the internal
       * vector of values. 
       *
       * @param [in] ScaleF
       *        The input constant to scale the internal vector of values
       *
       * @param [in] ShiftF
       *        The input constant to scale the vector v
       *
       * @param [in] ShiftFv
       *        The input list of property. The internal vector is used
       *        to scale the list v
       *
       * @param [in] v
       *        The input list of property. The internal vector describes
       *        the shift direction
       *
       * @param [in] nscaleshift
       *        The number of elements related to the operation
       *
       * @param [in] sfoffset
       *        The shift for the first element of list containing the
       *        scaling factor for the input vector v. It takes the default
       *        value zero (namely starting from the first element)
       *
       * @param [in] sfstep
       *        The spacing between the two elements in input object. It takes
       *        the default value one (namely all elements are read)
       *
       * @param [in] voffset
       *        The shift for the first element of list describing the
       *        searching direction. It takes the default value zero (namely
       *        starting from the first element)
       *
       * @param [in] vstep
       *        The spacing between the two elements in input object. It takes
       *        the default value one (namely all elements are read)
       *
       * @param [in] offset
       *        The shift for the first element of object to accept input.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between the two elements to accept inputs. It
       *        takes the default value one (namely all elements are read)
       *
       * @return the reference to the present object
       */
      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const Type& ShiftFv,const Type& v,long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        PropertyData.scaleshift(ScaleF,ShiftF,
                                ShiftFv.PropertyData,v.PropertyData,
                                nscaleshift,
                                sfoffset,sfstep,voffset,vstep,offset,step);
        return *this;
      }
      
      /**
       * @brief composite operation of scale and shift with two constants and two lists of property
       *
       * It is implemented with the scaleshift() method of the internal
       * vector of values. 
       *
       * @param [in] ScaleF
       *        The input constant to scale the internal vector of values
       *
       * @param [in] ShiftF
       *        The input constant to scale the vector v
       *
       * @param [in] ShiftFv
       *        The input list of property. The internal vector is used
       *        to scale the list v
       *
       * @param [in] v
       *        The input list of property. The internal vector describes
       *        the shift direction
       *
       * @return the reference to the present object
       */
      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const Type& ShiftFv, const Type& v) {
        PropertyData.scaleshift(ScaleF,ShiftF,
                                ShiftFv.PropertyData,v.PropertyData);
        return *this;
      }

      /**
       * @brief composite operation of scale and shift with two constants, a VectorBase object and a list of property
       *
       * It is implemented with the scaleshift() method of the internal
       * vector of values.
       *
       * @param [in] ScaleF
       *        The input constant to scale the internal vector of values
       *
       * @param [in] ShiftF
       *        The input constant to scale the vector v
       *
       * @param [in] ShiftFv
       *        The input VectorBase objec to scale the vector v
       *
       * @param [in] v
       *        The input list of property. The internal vector describes
       *        the shift direction
       *
       * @return the reference to the present object
       */
      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const VectorBase<DataType>& ShiftFv, const Type& v) {
        PropertyData.scaleshift(ScaleF,ShiftF,ShiftFv,v.PropertyData);
        return *this;
      }

      /**
       * @brief composite operation of scale and shift with two constants, a list of property and a VectorBase object
       *
       * It is implemented with the scaleshift() method of the internal
       * vector of values.
       *
       * @param [in] ScaleF
       *        The input constant to scale the internal vector of values
       *
       * @param [in] ShiftF
       *        The input constant to scale the vector v
       *
       * @param [in] ShiftFv
       *        The input list of property. The internal vector is used
       *        to scale the list v
       *
       * @param [in] v
       *        The input VectorBase object describing the shift direction
       *
       * @return the reference to the present object
       */
      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const Type& ShiftFv, const VectorBase<DataType>& v) {
        PropertyData.scaleshift(ScaleF,ShiftF,ShiftFv.PropertyData,v);
        return *this;
      }

      /**
       * @brief composite operation of scale and shift with two constants and two VectorBase objects
       *
       * It is implemented with the scaleshift() method of the internal
       * vector of values.
       *
       * @param [in] ScaleF
       *        The input constant to scale the internal vector of values
       *
       * @param [in] ShiftF
       *        The input constant to scale the vector v
       *
       * @param [in] ShiftFv
       *        The input VectorBase objec to scale the vector v
       *
       * @param [in] v
       *        The input VectorBase object describing the shift direction
       *
       * @return the reference to the present object
       */
      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const VectorBase<DataType>& ShiftFv,
                       const VectorBase<DataType>& v) {
        PropertyData.scaleshift(ScaleF,ShiftF,ShiftFv,v);
        return *this;
      }

      /**
       * @brief composite operation of scale and shift for part of content with two constants and a VectorBase object
       *
       * It is implemented with the combination of scale() and shift()
       * method of the internal vector of values.
       *
       * @param [in] ScaleF
       *        The input constant to scale the internal vector of values
       *
       * @param [in] ShiftF
       *        The input constant to scale the vector v
       *
       * @param [in] v
       *        The input VectorBase object describing the shift direction
       *
       * @param [in] nscaleshift
       *        The number of elements related to the operation
       *
       * @param [in] voffset
       *        The shift for the first element of vector describing the
       *        searching direction. It takes the default value zero (namely
       *        starting from the first element)
       *
       * @param [in] vstep
       *        The spacing between the two elements in input object. It takes
       *        the default value one (namely all elements are read)
       *
       * @param [in] offset
       *        The shift for the first element of object to accept input.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between the two elements to accept inputs. It
       *        takes the default value one (namely all elements are read)
       *
       * @return the reference to the present object
       */
      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const VectorBase<DataType>& v, long nscaleshift,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        scale(ScaleF,nscaleshift,offset,step);
        PropertyData.shift(ShiftF,v,nscaleshift,
                           voffset,vstep,offset,step);
        return *this;
      }

      /**
       * @brief composite operation of scale and shift for part of content with two constants and a list of property
       *
       * It is implemented with the combination of scale() and shift()
       * method of the internal vector of values.
       *
       * @param [in] ScaleF
       *        The input constant to scale the internal vector of values
       *
       * @param [in] ShiftF
       *        The input constant to scale the vector v
       *
       * @param [in] v
       *        The input list of property. The internal vector describes
       *        the shift direction
       *
       * @param [in] nscaleshift
       *        The number of elements related to the operation
       *
       * @param [in] voffset
       *        The shift for the first element of list describing the
       *        searching direction. It takes the default value zero (namely
       *        starting from the first element)
       *
       * @param [in] vstep
       *        The spacing between the two elements in input object. It takes
       *        the default value one (namely all elements are read)
       *
       * @param [in] offset
       *        The shift for the first element of object to accept input.
       *        It takes the default value zero (namely starting from the
       *        first element)
       *
       * @param [in] step
       *        The spacing between the two elements to accept inputs. It
       *        takes the default value one (namely all elements are read)
       *
       * @return the reference to the present object
       */
      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const Type& v, long nscaleshift,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        scale(ScaleF,nscaleshift,offset,step);
        PropertyData.shift(ShiftF,v.PropertyData,nscaleshift,
                           voffset,vstep,offset,step);
        return *this;
      }

      /**
       * @brief composite operation of scale and shift with two constants and a VectorBase object
       *
       * It is implemented with the scaleshift() method of the internal vector
       * of values.
       *
       * @param [in] ScaleF
       *        The input constant to scale the internal vector of values
       *
       * @param [in] ShiftF
       *        The input constant to scale the vector v
       *
       * @param [in] v
       *        The input VectorBase object describing the shift direction
       *
       * @return the reference to the present object
       */
      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const VectorBase<DataType>& v) {
        PropertyData.scaleshift(ScaleF,ShiftF,v);
        return *this;
      }

      /**
       * @brief composite operation of scale and shift with two constants and a list of property
       *
       * It is implemented with the scaleshift() method of the internal vector
       * of values.
       *
       * @param [in] ScaleF
       *        The input constant to scale the internal vector of values
       *
       * @param [in] ShiftF
       *        The input constant to scale the vector v
       *
       * @param [in] v
       *        The input list of property. The internal vector describes
       *        the shift direction
       *
       * @return the reference to the present object
       */
      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const Type& v) {
        PropertyData.scaleshift(ScaleF,ShiftF,v.PropertyData);
        return *this;
      }

  };

  /**
   * @brief establish reference relation between two lists of property
   *
   * To keep the flexibility, the refer() function of the list of property
   * is not replaced. However, that method does not operate the internal
   * vector. The present method established the reference relation including
   * both the parent class and the internal vector.
   *
   * \a PropertyType
   *    The template type for the property
   *
   * \a DataType
   *    The type for the data in the internal vector of the list of property
   *
   * \a SListType
   *    The template type for the source list
   *
   * \a SDataVecType
   *    The template type for internal vector in source list
   *
   * @param [out] dPL
   *        The destinate list of property. It would be used to refer to
   *        the source list.
   *
   * @param [in] sPL
   *        The source list of property.
   */
  template <template <typename> class PropertyType, typename DataType,
            template <typename> class SListType,
            template <typename> class SDataVecType>
  void refer(PropertyList<refVector,PropertyType,DataType,refVector>& dPL,
       const PropertyList<SListType,PropertyType,DataType,SDataVecType>& sPL) {
    dPL.refer(sPL);
    dPL.PropertyData.refer(sPL.PropertyData);
  }

  /**
   * @brief swap two lists of property
   *
   * It is implemented with the swap() method of the list of property.
   * This funciton is used to provide unique interface.
   *
   * \a ListType
   *    The template type for the lists
   *
   * \a PropertyType
   *    The template type for the property
   *
   * \a DataType
   *    The type of the data in the internal vector.
   *
   * @param [in,out] pl1
   *        One list of property to be swapped
   *
   * @param [in,out] pl2
   *        Another list of property to be swapped
   */
  template <template <typename> class ListType,
            template <typename> class PropertyType, typename DataType>
  void swap(PropertyList<ListType,PropertyType,DataType>& pl1,
            PropertyList<ListType,PropertyType,DataType>& pl2) {
    pl1.swap(pl2);
  }

  /**
   * @brief activate all the mask flags
   *
   * Just assign the vector of flags as one.
   *
   * @param [out] MaskObj
   *        The object storing flags
   */
  void Activate(VectorBase<uint>& MaskObj) { MaskObj=1; }

  /**
   * @brief deactivate all the mask flags
   *
   * Just assign the vector offlags with zero
   *
   * @param [out] MaskObj
   *        The object storing flags
   */
  void DeActivate(VectorBase<uint>& MaskObj) { MaskObj=0; }

  /**
   * @brief activate flag of a certain dimension
   *
   * Just assign the certain flag with one.
   *
   * @param [out] MaskObj
   *        The object storing flags
   *
   * @param [in] I
   *        The index for the dimension to be changed
   */
  void Activate(VectorBase<uint>& MaskObj, const uint& I) { MaskObj[I]=1; }

  /**
   * @brief deactivate flag of a certain dimension
   *
   * Just assign the certain flag with zero.
   *
   * @param [out] MaskObj
   *        The object storing flags
   *
   * @param [in] I
   *        The index for the dimension to be changed
   */
  void DeActivate(VectorBase<uint>& MaskObj, const uint& I) { MaskObj[I]=0; }

  /**
   * @brief activate all the mask flags including \c double type flags
   *
   * Assign the flags with one of corresponding type.
   *
   * @param [out] MaskObj
   *        The object storing \c unsigned \c int flags.
   *
   * @param [out] DMaskObj
   *        The object storing \c double flags.
   */
  void Activate(VectorBase<uint>& MaskObj, VectorBase<double>& DMaskObj) {
    MaskObj=1;  DMaskObj=1.;
  }

  /**
   * @brief deactivate all the mask flags including \c double type flags
   *
   * Assign the flags with zero of corresponding type.
   *
   * @param [out] MaskObj
   *        The object storing \c unsigned \c int flags.
   *
   * @param [out] DMaskObj
   *        The object storing \c double flags.
   */
  void DeActivate(VectorBase<uint>& MaskObj, VectorBase<double>& DMaskObj) {
    MaskObj=0;  DMaskObj=0.;
  }

  /**
   * @brief activate flag of a certain dimension including \c double type flags
   *
   * Just assign the certain flag with one.
   *
   * @param [out] MaskObj
   *        The object storing \c unsigned \c int flags.
   *
   * @param [out] DMaskObj
   *        The object storing \c double flags.
   *
   * @param [in] I
   *        The index for the dimension to be changed
   */
  void Activate(VectorBase<uint>& MaskObj, VectorBase<double>& DMaskObj,
                const uint& I) {
    MaskObj[I]=1;  DMaskObj[I]=1.;
  }

  /**
   * @brief deactivate flag of a certain dimension including \c double flags
   *
   * Just assign the certain flag with zero.
   *
   * @param [out] MaskObj
   *        The object storing \c unsigned \c int flags.
   *
   * @param [out] DMaskObj
   *        The object storing \c double flags.
   *
   * @param [in] I
   *        The index for the dimension to be changed
   */
  void DeActivate(VectorBase<uint>& MaskObj, VectorBase<double>& DMaskObj,
                  const uint& I) {
    MaskObj[I]=0;  DMaskObj[I]=0.;
  }
}

#endif

