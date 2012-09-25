
#ifndef _Array_VarArray_Interface_H_
#define _Array_VarArray_Interface_H_

#include "array/base/interface.h"
#include "memory/aligned-memory.h"
#include <memory>

namespace mysimulator {

  template <typename T>
  class VarArray : public ArrayBase<T,std::shared_ptr<T>> {

    public:

      typedef VarArray<T>   Type;
      typedef ArrayBase<T,std::shared_ptr<T>>  ParentType;

      VarArray() : ParentType() {}
      VarArray(unsigned int size) : ParentType() { Allocate(size); }
      VarArray(const Type&) = delete;
      ~VarArray() { ParentType::Clear(); }

      void Allocate(unsigned int size) {
        ParentType::Clear();
        ParentType::_pdata=std::shared_ptr<double>(new double[size]);
        ParentType::_ndata=size;
      }
      Type& operator=(const Type& A) {
        ParentType::operator=(A);
        for(unsigned int i=0;i<ParentType::Size();++i)
          ParentType::operator[](i)=A[i];
        return *this;
      }
      Type& Refer(Type& A) {
        ParentType::_pdata=A._pdata;
        ParentType::_ndata=A._ndata;
        return *this;
      }

  };

}

#endif

