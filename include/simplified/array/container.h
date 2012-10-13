
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
      typedef typename ParentType::value_type value_type;
      typedef unsigned int size_type;

      ArrayContainer() : ParentType() {}
      ArrayContainer(size_type size) : ArrayContainer() { allocate(size); }
      ArrayContainer(const Type&) = delete;
      virtual ~ArrayContainer() { this->reset(); }

      virtual void allocate(size_type size) override {
        this->reset();
        this->_pdata.reset(new value_type[size],operator delete[]);
        this->_ndata=size;
      }

  };

}

#include "memory/aligned-memory.h"

namespace mysimulator {

  template <typename T>
  class ArrayContainer<Intrinsic<T>,ArrayFormat::Data>
      : public ArrayContainerBase<Intrinsic<T>,ArrayFormat::Data> {

    public:

      typedef ArrayContainer<Intrinsic<T>,ArrayFormat::Data>    Type;
      typedef ArrayContainerBase<Intrinsic<T>,ArrayFormat::Data>   ParentType;
      typedef typename ParentType::value_type value_type;
      typedef unsigned int size_type;
      typedef value_type* pointer;

    private:

      unsigned int _n128;

    public:

      ArrayContainer() : ParentType(),_n128(0U) {}
      ArrayContainer(size_type size) : ArrayContainer() { allocate(size); }
      ArrayContainer(const Type&) = delete;
      virtual ~ArrayContainer() { this->reset(); }

      virtual void allocate(size_type size) override {
        this->reset();
        size_type byte_size=size*sizeof(value_type);
        size_type alloc_size=
          (byte_size&(~0xFU))+((byte_size&0xFU)==0?0:0x10U-(byte_size&0xFU));
        _n128=((byte_size&0xFU)==0?0:1)+(byte_size>>4);
        this->_pdata.reset(
            reinterpret_cast<pointer>(__aligned_malloc(alloc_size)),
            __aligned_free);
        this->_ndata=size;
      }
      unsigned int size128() const { return _n128; }

  };

  static const unsigned int ArrayByteBoundary=400;

  template <typename T>
  class ArrayContainer<T,ArrayFormat::ShortData>
      : public ArrayContainer<T,ArrayFormat::Data> {

    public:

      typedef ArrayContainer<T,ArrayFormat::ShortData>  Type;
      typedef ArrayContainer<T,ArrayFormat::Data> ParentType;
      typedef unsigned int size_type;

      ArrayContainer() : ParentType() {}
      ArrayContainer(size_type size) : ArrayContainer() { allocate(size); }
      ArrayContainer(const Type&) = delete;
      ~ArrayContainer() { this->reset(); }

      virtual void allocate(size_type size) override {
        assert(size<=ArrayByteBoundary);
        ParentType::allocate(size);
      }

  };

  template <typename T>
  class ArrayContainer<T,ArrayFormat::LargeData>
      : public ArrayContainer<T,ArrayFormat::Data> {

    public:

      typedef ArrayContainer<T,ArrayFormat::LargeData>  Type;
      typedef ArrayContainer<T,ArrayFormat::Data> ParentType;
      typedef unsigned int size_type;

      ArrayContainer() : ParentType() {}
      ArrayContainer(size_type size) : ArrayContainer() { allocate(size); }
      ArrayContainer(const Type&) = delete;
      ~ArrayContainer() { this->reset(); }

      virtual void allocate(size_type size) {
        assert(size>ArrayByteBoundary);
        ParentType::allocate(size);
      }

  };

}

#endif

