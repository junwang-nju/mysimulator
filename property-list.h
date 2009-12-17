
#ifndef _Property_List_H_
#define _Property_List_H_

#include "property.h"

namespace std {

	template <template <typename> class ListType=varVector,
            typename DataType=double>
	class PropertyList : public ListType<PropertyComponent<refVector,DataType> > {
    public:
      typedef PropertyList<ListType,DataType>         Type;
      typedef ListType<PropertyComponent<refVector,DataType> >  ParentType;
      varVector<DataType> PropertyData;

      PropertyList() : ParentType(), PropertyData() {}
      PropertyList(const Type& PL) { myError("copier for property list is prohibited!"); }
      
      Type& allocate(const VectorBase<uint>& ShapeList) {
      	return *this;
      }

  };

}

#endif
