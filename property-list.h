
#ifndef _Property_List_H_
#define _Property_List_H_

#include "property.h"

namespace std {

	template <template <typename> class ListType=varVector,
            typename DataType=double>
	class PropertyList : public ListType<PropertyComponent<refVector,DataType> >{
    public:
      typedef PropertyList<ListType,DataType>         Type;
      typedef ListType<PropertyComponent<refVector,DataType> >  ParentType;
      varVector<DataType> PropertyData;

      PropertyList() : ParentType(), PropertyData() {}
      PropertyList(const Type& PL) {
        myError("copier for property list is prohibited!");
      }
      
      Type& allocate(const VectorBase<uint>& ShapeOffset,
                     const VectorBase<uint>& ShapeSize) {
        uint n=ShapeSize.size();
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
