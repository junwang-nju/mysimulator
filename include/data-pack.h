
#ifndef _Data_Pack_H_
#define _Data_Pack_H_

#include "ref-vector.h"

namespace std {
  template <typename T, template<typename> class DataVecType,
                        template<typename> class StructVecType,
                        template<typename> class InfVecType>
  class DataPack {
    public:
      typedef T DataType;
      typedef refVector<T>  LineType;
      typedef DataPack<T,DataVecType,StructVecType,InfVecType>  Type;
    protected:
      DataVecType<T> Data;
      StructVecType<LineType> Struct;
      InfVecType<int> Info;
    public:
      DataPack() : Data(), Struct(), Info() {
        assert(DataVecType<T>::IsVector);
        assert(StructVecType<LineType>::IsVector);
        assert(InfVecType<int>::IsVector);
      }
      DataPack(const Type& DP) { myError("Cannot create from data pack"); }
      virtual ~DataPack() {}
      Type& operator=(const Type& DP) { return *this; }
      void clear();
      virtual const char* type() = 0;
  };
}

#endif

