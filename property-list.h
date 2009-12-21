
#ifndef _Property_List_H_
#define _Property_List_H_

#include "var-vector.h"
#include "ref-vector.h"

namespace std {

	template <template <typename> class ListType=varVector,
            template <typename> class PropertyType=refVector,
            typename DataType=double>
	class PropertyList : public ListType<PropertyType<DataType> >{
    public:
      typedef PropertyList<ListType,PropertyType,DataType>  Type;
      typedef ListType<PropertyType<DataType> >             ParentType;
      typedef PropertyType<DataType>                        Property;
      varVector<DataType> PropertyData;

      PropertyList() : ParentType(), PropertyData() {}
      PropertyList(const Type& PL) {
        myError("copier for property list is prohibited!");
      }
      
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
      void swap(Type& PL) {
        static_cast<ParentType*>(this)->swap(static_cast<ParentType&>(PL));
        PropertyData.swap(PL.PropertyData);
      }

  };

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

