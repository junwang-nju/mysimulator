
#ifndef _Basic_Memory_Access_Pointer_H_
#define _Basic_Memory_Access_Pointer_H_

#include "basic/memory/access-count.h"
#include "basic/memory/deleter.h"
#include <algorithm>

namespace mysimulator {

  enum class AccessContentName { Unassigned, GlobalUsed, PartUsed };

  template <typename T>
  class access_ptr {

    public:

      typedef access_ptr<T>   Type;
      typedef T* pointer;
      typedef const T* const_pointer;
      typedef T& reference;
      typedef T const& const_reference;
      typedef _memory_access_count* count_pointer;
      typedef const _memory_access_count* const_count_pointer;
      typedef void (*deleter)(void*);

    private:

      enum class AllocationName { NeedFree, NotNeedFree };

      pointer ptr;
      count_pointer count;
      AccessContentName part_flag;
      deleter del;

    public:

      access_ptr() : ptr(nullptr), count(nullptr),
                     part_flag(AccessContentName::Unassigned),
                     del(_delete_unit<T>) {}
      access_ptr(const Type& P) : access_ptr() { reset(P); }
      access_ptr(Type& P) : access_ptr() { swap(P); }
      ~access_ptr() { reset(); }

      Type& operator=(const Type& P)  { reset(P); return *this; }
      Type& operator=(const Type&& P) { swap(P); return *this; }

    private:

      void IncCount() {
        assert( part_flag != AccessContentName::Unassigned );
        if( part_flag == AccessContentName::GlobalUsed )    count->Inc();
        if( part_flag == AccessContentName::PartUsed )      count->IncPart();
      }

    public:

      operator bool() const {
        return ( ptr != nullptr ) && ( count != nullptr ) &&
               (bool)(*count) && part_flag != AccessContentName::Unassigned;
      }
      unsigned int GlobalUseCount() const {
        return count==nullptr ? 0 : count->GlobalUseCount();
      }
      unsigned int PartUseCount() const {
        return count==nullptr ? 0 : count->PartUseCount();
      }
      bool unique() const { 
        return count!=nullptr && count->IsOnly() && !count->IsPartUsed();
      }
      bool __aligned16() const {
        return (bool)(*this) && (((unsigned int)ptr)&0xFU)==0;
      }

      pointer get() const { return ptr; }
      reference operator*() { return *ptr; }
      pointer operator->() { return ptr; }
      reference operator[](int i) { return *(ptr+i); }
      const_reference operator[](int i) const { return *(ptr+i); }

      void reset() {
        if((bool)(*this)) {
          AllocationName allocflag = AllocationName::NotNeedFree;
          if( part_flag == AccessContentName::PartUsed )  count->DecPart();
          else if( count->IsOnly() ) {
            assert( !count->IsPartUsed() );
            delete count;
            allocflag = AllocationName::NeedFree;
          } else count->Dec();
          if( allocflag == AllocationName::NeedFree ) del(ptr);
          ptr = nullptr;
          count = nullptr;
          part_flag = AccessContentName::Unassigned;
        }
      }
      void reset( const_pointer PTR, const_count_pointer icount,
                  AccessContentName PF = AccessContentName::GlobalUsed,
                  deleter idel = _delete_unit ) {
        assert( PTR != nullptr );
        reset();
        ptr = const_cast<pointer>(PTR);
        count = const_cast<count_pointer>(icount);
        part_flag = PF;
        del = idel;
        IncCount();
      }
      void reset( const_pointer PTR, deleter idel = _delete_unit ) {
        reset( PTR, new _memory_access_count, AccessContentName::GlobalUsed,
               idel );
      }
      void reset( const Type& P, unsigned int BgIdx = 0 ) {
        assert((bool)P);
        reset( P.get() + BgIdx, P.count,
               ( P.part_flag == AccessContentName::GlobalUsed && BgIdx==0 ) ?
               AccessContentName::GlobalUsed : AccessContentName::PartUsed,
               P.del );
      }

      void swap(Type& P) {
        std::swap( ptr,       P.ptr );
        std::swap( count,     P.count );
        std::swap( part_flag, P.part_flag );
        std::swap( del,       P.del );
      }

  };

  template <typename T>
  bool operator==( const access_ptr<T>& l, const access_ptr<T>& r) {
    return l.get() == r.get();
  }

  template <typename T>
  bool operator!=( const access_ptr<T>& l, const access_ptr<T>& r ) {
    return l.get() != r.get();
  }

  template <typename T>
  bool operator<( const access_ptr<T>& l, const access_ptr<T>& r ) {
    return l.get() < r.get();
  }

  template <typename T>
  bool operator>( const access_ptr<T>& l, const access_ptr<T>& r ) {
    return l.get() > r.get();
  }

  template <typename T>
  bool operator<=( const access_ptr<T>& l, const access_ptr<T>& r ) {
    return !(l.get() > r.get());
  }

  template <typename T>
  bool operator>=( const access_ptr<T>& l, const access_ptr<T>& r ) {
    return !(l.get() < r.get());
  }

}

#include <cstddef>

namespace mysimulator {

  template <typename T>
  bool operator==( const access_ptr<T>& l, const std::nullptr_t r ) {
    return !l;
  }

  template <typename T>
  bool operator==( const std::nullptr_t l, const access_ptr<T>& r ) {
    return !r;
  }

  template <typename T>
  bool operator!=( const access_ptr<T>& l, const std::nullptr_t r ) {
    return (bool)l;
  }

  template <typename T>
  bool operator!=( const std::nullptr_t l, const access_ptr<T>& r ) {
    return (bool)r;
  }

  template <typename T>
  bool operator<( const access_ptr<T>& l, const std::nullptr_t r ) {
    return l.get() < nullptr;
  }

  template <typename T>
  bool operator<( const std::nullptr_t l, const access_ptr<T>& r ) {
    return nullptr < r.get();
  }

  template <typename T>
  bool operator>( const access_ptr<T>& l, const std::nullptr_t r ) {
    return nullptr < l;
  }

  template <typename T>
  bool operator>( const std::nullptr_t l, const access_ptr<T>& r ) {
    return r < nullptr;
  }

  template <typename T>
  bool operator<=( const access_ptr<T>& l, const std::nullptr_t r ) {
    return !(nullptr<l);
  }

  template <typename T>
  bool operator<=( const std::nullptr_t l, const access_ptr<T>& r ) {
    return !(r<nullptr);
  }

  template <typename T>
  bool operator>=( const access_ptr<T>& l, const std::nullptr_t r ) {
    return !(l<nullptr);
  }

  template <typename T>
  bool operator>=( const std::nullptr_t l, const access_ptr<T>& r ) {
    return !(nullptr<r);
  }

}

#include <ostream>

namespace std {

  template <typename T,typename U,typename V>
  basic_ostream<U,V>& operator<<( basic_ostream<U,V>& os,
                                  mysimulator::access_ptr<T> const& P ) {
    return os<<P.get();
  }

  template <typename T>
  void swap( mysimulator::access_ptr<T>& l, mysimulator::access_ptr<T>& r ) {
    l.swap(r);
  }

}

#endif

