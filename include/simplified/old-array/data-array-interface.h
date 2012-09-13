
#ifndef _Array_DataArray_Interface_H_
#define _Array_DataArray_Interface_H_

#include "array/interface.h"
#include "memory/aligned-memory.h"

namespace mysimulator {

  template <typename T>
  class DataArray : public Array<T> {

    public:

      typedef DataArray<T>    Type;
      typedef Array<T>    ParentType;

      DataArray() : ParentType() {}
      DataArray(unsigned int size) : DataArray() { allocate(size); }
      DataArray(const Type&) = delete;
      virtual ~DataArray() { ParentType::~Array(); }

      virtual void allocate(unsigned int size) override {
        this->~DataArray();
        unsigned int byte_size=size*sizeof(T);
        unsigned int run_byte=(byte_size&(~0xFU))+
                             ((byte_size&0xFU)==0?0:0xFU-(byte_size&0xFU));
        this->_pdata.reset((T*)__aligned_malloc(run_byte));
        this->_pdata.set_deleter(__aligned_free);
        this->_ndata=size;
      }

  };

}

#endif

