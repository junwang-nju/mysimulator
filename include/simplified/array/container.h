
#ifndef _Array_Container_H_
#define _Array_Container_H_

#include "array/container-base.h"

namespace mysimulator {

  template <typename T,ArrayFormat AF>
  class ArrayContainer {
    public:
      ArrayContainer() = delete;
  };

  template <typename T>
  class ArrayContainer<T,ArrayFormat::Regular>
      : public ArrayContainerBase<T,ArrayFormat::Regular> {
    
    public:

      typedef ArrayContainer<T,ArrayFormat::Regular>        Type;
      typedef ArrayContainerBase<T,ArrayFormat::Regular>    ParentType;
      typedef unsigned int size_type;

      ArrayContainer() : ParentType() {}
      ArrayContainer(size_type size) : ParentType(size) {}
      ArrayContainer(const Type&) = delete;
      virtual ~ArrayContainer() { ParentType::reset(); }

      virtual void allocate(size_type size) override {
        printf("------------R-------------\n");
        this->reset();
        this->_pdata.reset(new T[size],operator delete[]);
        this->_ndata=size;
      }

  };

}

#include "memory/aligned-memory.h"

namespace mysimulator {

  template <typename T>
  class ArrayContainer<T,ArrayFormat::Data>
      : public ArrayContainerBase<T,ArrayFormat::Data> {

    public:

      typedef ArrayContainer<T,ArrayFormat::Data>    Type;
      typedef ArrayContainerBase<T,ArrayFormat::Data>   ParentType;
      typedef unsigned int size_type;
      typedef T* pointer;

      ArrayContainer() : ParentType() {}
      ArrayContainer(size_type size) : ParentType(size) {}
      ArrayContainer(const Type&) = delete;
      virtual ~ArrayContainer() { ParentType::reset(); }

      virtual void allocate(size_type size) override {
        printf("------------D-------------\n");
        this->reset();
        size_type byte_size=size*sizeof(T);
        size_type alloc_size=
          (byte_size&(~0xFU))+((byte_size&0xFU)==0?0:0xFU-(byte_size&0xFU));
        this->_pdata.reset(
            reinterpret_cast<pointer>(__aligned_malloc(alloc_size)),
            __aligned_free);
        this->_ndata=size;
      }

  };


}

#endif

