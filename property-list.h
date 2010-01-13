
/**
 * @file property-list.h
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

      Type& assign(const Type& v, long ncopy,
                   int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        PropertyData.assign(v.PropertyData,ncopy,voffset,vstep,offset,step);
        return *this;
      }

      Type& assign(const VectorBase<DataType>& v) {
        PropertyData.assign(v);
        return *this;
      }

      Type& assign(const Type& v) {
        PropertyData.assign(v.PropertyData);
        return *this;
      }

      Type& assign(const DataType& value, long ncopy,
                   int offset=iZero, long step=lOne) {
        PropertyData.assign(value,ncopy,offset,step);
        return *this;
      }
      
      Type& assign(const DataType& value) {
        PropertyData.assign(value);
        return *this;
      }

      Type& scale(const DataType* v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        PropertyData.scale(v,nscale,voffset,vstep,offset,step);
        return *this;
      }

      Type& scale(const DataType& d, long nscale,
                  int offset=iZero, long step=lOne) {
        PropertyData.scale(d,nscale,offset,step);
        return *this;
      }

      Type& scale(const DataType& d) {
        PropertyData.scale(d);
        return *this;
      }

      Type& scale(const VectorBase<DataType>& v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        PropertyData.scale(v,nscale,voffset,vstep,offset,step);
        return *this;
      }

      Type& scale(const Type& v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        PropertyData.scale(v.PropertyData,nscale,voffset,vstep,offset,step);
        return *this;
      }

      Type& scale(const VectorBase<DataType>& v) {
        PropertyData.scale(v);
        return *this;
      }

      Type& scale(const Type& v) {
        PropertyData.scale(v.PropertyData);
        return *this;
      }

      template <typename ScaleT>
      Type& shift(const ScaleT& sv, const DataType* v, long nshift,
                  int soffset=iZero, long sstep=lOne,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        PropertyData.shift(sv,v,nshift,soffset,sstep,voffset,vstep,
                           offset,step);
        return *this;
      }

      Type& shift(const DataType& value, const VectorBase<DataType>& v,
                  long nshift, int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        PropertyData.shift(value,v,nshift,voffset,vstep,offset,step);
        return *this;
      }
      
      Type& shift(const DataType& value, const Type& v,
                  long nshift, int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        PropertyData.shift(value,v,PropertyData,nshift,
                           voffset,vstep,offset,step);
        return *this;
      }
      
      Type& shift(const DataType& value, const VectorBase<DataType>& v) {
        PropertyData.shift(value,v);
        return *this;
      }

      Type& shift(const DataType& value, const Type& v) {
        PropertyData.shift(value,v.PropertyData);
        return *this;
      }
      
      Type& shift(const DataType& value, int offset=iZero, long step=lOne) {
        PropertyData.shift(value,offset,step);
        return *this;
      }

      Type& shift(const VectorBase<DataType>& v) { return shift(dOne,v); }

      Type& shift(const Type& v) { return shift(dOne,v); }

      template <typename vTypeA, typename vTypeB>
      Type& shift(const vTypeA& ShiftFv, const vTypeB& v) {
        return shift(dOne,ShiftFv,v);
      }

      template <typename vTypeA, typename vTypeB>
      Type& shift(const DataType& ShiftF,
                  const vTypeA& ShiftFv, const vTypeB& v) {
        PropertyData.scaleshift(dOne,ShiftF,ShiftFv,v);
        return *this;
      }

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
      
      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const Type& ShiftFv, const Type& v) {
        PropertyData.scaleshift(ScaleF,ShiftF,
                                ShiftFv.PropertyData,v.PropertyData);
        return *this;
      }

      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const VectorBase<DataType>& ShiftFv, const Type& v) {
        PropertyData.scaleshift(ScaleF,ShiftF,ShiftFv,v.PropertyData);
        return *this;
      }

      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const Type& ShiftFv, const VectorBase<DataType>& v) {
        PropertyData.scaleshift(ScaleF,ShiftF,ShiftFv.PropertyData,v);
        return *this;
      }

      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const VectorBase<DataType>& ShiftFv,
                       const VectorBase<DataType>& v) {
        PropertyData.scaleshift(ScaleF,ShiftF,ShiftFv,v);
        return *this;
      }

      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const VectorBase<DataType>& v, long nscaleshift,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        scale(ScaleF,nscaleshift,offset,step);
        PropertyData.shift(ShiftF,v,nscaleshift,
                           voffset,vstep,offset,step);
        return *this;
      }
      
      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const Type& v, long nscaleshift,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        scale(ScaleF,nscaleshift,offset,step);
        PropertyData.shift(ShiftF,v.PropertyData,nscaleshift,
                           voffset,vstep,offset,step);
        return *this;
      }
      
      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const VectorBase<DataType>& v) {
        PropertyData.scaleshift(ScaleF,ShiftF,v);
        return *this;
      }

      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const Type& v) {
        PropertyData.scaleshift(ScaleF,ShiftF,v.PropertyData);
        return *this;
      }

  };

  template <template <typename> class PropertyType, typename DataType,
            template <typename> class SListType,
            template <typename> class SDataVecType>
  void refer(PropertyList<refVector,PropertyType,DataType,refVector>& dPL,
       const PropertyList<SListType,PropertyType,DataType,SDataVecType>& sPL) {
    dPL.refer(sPL);
    dPL.PropertyData.refer(sPL.PropertyData);
  }

  template <template <typename> class ListType,
            template <typename> class PropertyType, typename DataType>
  void swap(PropertyList<ListType,PropertyType,DataType>& pl1,
            PropertyList<ListType,PropertyType,DataType>& pl2) {
    pl1.swap(pl2);
  }

  void Activate(VectorBase<uint>& MaskObj) { MaskObj=1; }

  void DeActivate(VectorBase<uint>& MaskObj) { MaskObj=0; }

  void Activate(VectorBase<uint>& MaskObj, const uint& I) { MaskObj[I]=1; }

  void DeActivate(VectorBase<uint>& MaskObj, const uint& I) { MaskObj[I]=0; }

  void Activate(VectorBase<uint>& MaskObj, VectorBase<double>& DMaskObj) {
    MaskObj=1;  DMaskObj=1.;
  }

  void DeActivate(VectorBase<uint>& MaskObj, VectorBase<double>& DMaskObj) {
    MaskObj=0;  DMaskObj=0.;
  }

  void Activate(VectorBase<uint>& MaskObj, VectorBase<double>& DMaskObj,
                const uint& I) {
    MaskObj[I]=1;  DMaskObj[I]=1.;
  }

  void DeActivate(VectorBase<uint>& MaskObj, VectorBase<double>& DMaskObj,
                  const uint& I) {
    MaskObj[I]=0;  DMaskObj[I]=0.;
  }
}

#endif

