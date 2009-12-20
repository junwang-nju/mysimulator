
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

}

#endif

