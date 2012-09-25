
#ifndef _Array_VarArray_Interface_H_
#define _Array_VarArray_Interface_H_

#include "array/base/interface.h"
#include <memory>

namespace mysimulator {

  template <typename T>
  class VarArray : public ArrayBase<T,std::shared_ptr<T>> {

    public:

      typedef VarArray<T>   Type;
      typedef ArrayBase<T,std::shared_ptr<T>>  ParentType;

      VarArray() : ParentType() {}
      VarArray(unsigned int size) : ParentType() { Allocate(size); }
      ~VarArray() { ParentType::Clear(); }

      void Allocate(unsigned int size) {
        ParentType::_pdata=std::make_shared<T>(size);
        ParentType::_ndata=size;
      }

  };

}

#endif

