
#ifndef _Data_Pack_H_
#define _Data_Pack_H_

#include "ref-vector.h"
#include "fix-vector.h"

namespace std {

  template <typename T, template<typename> class DataVecType,
                        template<typename> class StructVecType,
                        unsigned int NInf>
  class DataPack {

    public:

      typedef refVector<T>  LineType;

      typedef DataPack<T,DataVecType,StructVecType,NInf>  Type;

    protected:

      DataVecType<T> Data;

      StructVecType<LineType> Struct;

      fixVector<int,NInf> Info;

    public:

      DataPack() : Data(), Struct(), Info() {
        assert(DataVecType<T>::IsVector);
        assert(StructVecType<LineType>::IsVector);
      }

      DataPack(const Type& DP) { myError("Cannot create from data pack"); }

      virtual ~DataPack() { clear(); }

      Type& operator=(const Type& DP) { return *this; }

      void clear() { Data.clear(); Struct.clear(); }

      DataVecType<T>& data() { return Data; }

      const DataVecType<T>& data() const { return Data; }

      StructVecType<LineType>& structure() { return Struct; }

      const StructVecType<LineType>& structure() const { return Struct; }

      fixVector<int,NInf>& info() { return Info; }

      const fixVector<int,NInf>& info() const { return Info; }

      virtual const char* type() const = 0;

  };

}

#endif

