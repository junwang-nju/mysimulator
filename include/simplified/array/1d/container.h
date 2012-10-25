
#ifndef _Array_1D_Container_H_
#define _Array_1D_Container_H_

#include "array/1d/container-base.h"

namespace mysimulator {

  template <typename T>
  class ArrayContainer : public ArrayContainerBase<T> {
    
    public:

      typedef ArrayContainer<T>        Type;
      typedef ArrayContainerBase<T>    ParentType;
      typedef typename ParentType::monomer_type monomer_type;
      typedef unsigned int size_type;

      ArrayContainer() : ParentType() {}
      ArrayContainer(size_type size) : ArrayContainer() { allocate(size); }
      ArrayContainer(const Type&) = delete;
      ArrayContainer(Type&&) = delete;
      virtual ~ArrayContainer() { this->reset(); }

      virtual void allocate(size_type size) override {
        this->reset();
        this->_pdata.reset(new monomer_type[size],_delete_array<T>);
        this->_ndata=size;
      }

  };

}

#include "memory/aligned-memory.h"
#include "basic/intrinsic.h"

namespace mysimulator {

  template <typename T>
  class ArrayContainer<Intrinsic<T>> : public ArrayContainerBase<Intrinsic<T>> {

    public:

      typedef ArrayContainer<Intrinsic<T>>    Type;
      typedef ArrayContainerBase<Intrinsic<T>>   ParentType;
      typedef typename ParentType::monomer_type monomer_type;
      typedef unsigned int size_type;
      typedef monomer_type* pointer;

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
        size_type byte_size=size*sizeof(monomer_type);
        size_type alloc_size=
          (byte_size&(~0xFU))+((byte_size&0xFU)==0?0:0x10U);
        _n128=((byte_size&0xFU)==0?0:1)+(byte_size>>4);
        this->_pdata.reset(
            reinterpret_cast<pointer>(__aligned_malloc(alloc_size)),
            __aligned_free);
        this->_ndata=size;
      }
      unsigned int size128() const { return _n128; }

      void refer(const Type& AC) {
        ParentType::_refer_align16(AC);
        _n128=AC.size128();
      }
      void refer(const Type&,size_type,size_type) = delete;
      void _refer(const Type& AC,size_type bg,size_type num) {
        ParentType::_refer_align16(AC,bg,num);
        size_type nbyte=num*sizeof(monomer_type);
        _n128=(nbyte>>4)+((nbyte&0xFU)==0?0:1); // be careful the side effect
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

