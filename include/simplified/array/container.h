
#ifndef _Array_Container_H_
#define _Array_Container_H_

#include "array/container-base.h"

namespace mysimulator {

  template <typename T>
  class ArrayContainer : public ArrayContainerBase<T> {
    
    public:

      typedef ArrayContainer<T>        Type;
      typedef ArrayContainerBase<T>    ParentType;
      typedef typename ParentType::value_type value_type;
      typedef unsigned int size_type;

      ArrayContainer() : ParentType() {}
      ArrayContainer(size_type size) : ArrayContainer() { allocate(size); }
      ArrayContainer(const Type&) = delete;
      ArrayContainer(Type&&) = delete;
      virtual ~ArrayContainer() { this->reset(); }

      virtual void allocate(size_type size) override {
        this->reset();
        this->_pdata.reset(new value_type[size],_delete_array<T>);
        this->_ndata=size;
      }

  };

}

#include "memory/aligned-memory.h"

namespace mysimulator {

  template <typename T>
  class ArrayContainer<Intrinsic<T>> : public ArrayContainerBase<Intrinsic<T>> {

    public:

      typedef ArrayContainer<Intrinsic<T>>    Type;
      typedef ArrayContainerBase<Intrinsic<T>>   ParentType;
      typedef typename ParentType::value_type value_type;
      typedef unsigned int size_type;
      typedef value_type* pointer;

    private:

      unsigned int _n128;

    public:

      ArrayContainer() : ParentType(),_n128(0U) {}
      ArrayContainer(size_type size) : ArrayContainer() { allocate(size); }
      ArrayContainer(const Type&) = delete;
      ArrayContainer(Type&&) = delete;
      virtual ~ArrayContainer() { this->reset(); }

      virtual void allocate(size_type size) override {
        this->reset();
        size_type byte_size=size*sizeof(value_type);
        size_type alloc_size=
          (byte_size&(~0xFU))+((byte_size&0xFU)==0?0:0x10U);
        _n128=((byte_size&0xFU)==0?0:1)+(byte_size>>4);
        this->_pdata.reset(
            reinterpret_cast<pointer>(__aligned_malloc(alloc_size)),
            __aligned_free);
        this->_ndata=size;
      }
      unsigned int size128() const { return _n128; }

      void refer(const Type& AC) { ParentType::_refer_align16(AC); }
      void refer(const Type& AC,size_type bg,size_type num) {
        ParentType::_refer_align16(AC,bg,num);
      }
      void swap(Type& AC) {
        ParentType::swap(static_cast<ParentType&>(AC));
        std::swap(_n128,AC._n128);
      }

  };

}

namespace std {

  template <typename T>
  void swap(mysimulator::ArrayContainer<T>& AC1,
            mysimulator::ArrayContainer<T>& AC2) {
    AC1.swap(AC2);
  }

}

#endif

