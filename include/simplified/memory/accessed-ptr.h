
#ifndef _Memory_Accessed_Pointer_H_
#define _Memory_Accessed_Pointer_H_

#include "memory/access-count.h"
#include <algorithm>

namespace mysimulator {

  enum class AccessContentName { Unassigned, GlobalUsed, PartUsed };

  template <typename T>
  class accessed_ptr {

    public:

      typedef accessed_ptr<T>   Type;
      typedef T* pointer;
      typedef const T* const_pointer;
      typedef T& reference;
      typedef const T& const_reference;
      typedef memory_access_count*  count_pointer;
      typedef void (*deleter)(void*);
      typedef const count_pointer const_count_pointer;

    private:

      enum class AllocationName { NeedFree, NeedNotFree };

      pointer           ptr;
      count_pointer     count;
      AccessContentName part_flag;
      deleter           del;

    public:

      accessed_ptr() : ptr(nullptr), count(nullptr),
                       part_flag(AccessContentName::Unassigned),
                       del(operator delete) {}
      accessed_ptr(const Type& APTR) : accessed_ptr() { reset(APTR); }
      accessed_ptr(Type&& APTR) : accessed_ptr() { swap(APTR); }
      ~accessed_ptr() { reset(); }

      Type& operator=(const Type& APTR) { reset(APTR); return *this; }
      Type& operator=(const Type&& APTR) { swap(APTR); return *this; }

      void reset() {
        if((bool)(*this)) {
          AllocationName alloc_flag=AllocationName::NeedNotFree;
          if(part_flag==AccessContentName::PartUsed)   count->DecPart();
          else if(count->IsOnly()) {
            if(count->IsPartUsed()) throw "Need to Free Part Content First!";
            else {
              delete count;
              alloc_flag=AllocationName::NeedFree;
            }
          } else count->Dec();
          if(alloc_flag==AllocationName::NeedFree)  del(ptr);
          ptr=nullptr;
          count=nullptr;
          part_flag=AccessContentName::Unassigned;
        }
      }
      void reset(const_pointer PTR,const_count_pointer icount,
                 AccessContentName PF=AccessContentName::GlobalUsed,
                 deleter idel=operator delete) {
        assert(PTR!=nullptr);
        reset();
        ptr=const_cast<pointer>(PTR);
        count=const_cast<count_pointer>(icount);
        part_flag=PF;
        del=idel;
        IncCount();
      }
      void reset(const_pointer PTR,deleter idel=operator delete) {
        reset(PTR,new memory_access_count,AccessContentName::GlobalUsed,idel);
      }
      void reset(const Type& APTR, unsigned int BgIdx=0) {
        assert((bool)APTR);
        reset(
            APTR.get()+BgIdx,APTR.count,
            (APTR.part_flag==AccessContentName::GlobalUsed&&BgIdx==0)?
              AccessContentName::GlobalUsed:AccessContentName::PartUsed,
            APTR.del);
      }
      void set_deleter(deleter idel) { del=idel; }

      void swap(Type& APTR) {
        std::swap(ptr,APTR.ptr);
        std::swap(count,APTR.count);
        std::swap(part_flag,APTR.part_flag);
        std::swap(del,APTR.del);
      }

      pointer get() const { return ptr; }
      reference operator*() { return *ptr; }
      pointer operator->() { return ptr; }
      reference operator[](int i) { return *(ptr+i); }
      const_reference operator[](int i) const { return *(ptr+i); }

      operator bool() const {
        return (ptr!=nullptr)&&(count!=nullptr)&&(bool)(*count)&&
               (part_flag!=AccessContentName::Unassigned);
      }
      unsigned int GlobalUseCount() const {
        return count==nullptr?0:count->GlobalUseCount();
      }
      unsigned int PartUsedCount() const {
        return count==nullptr?0:count->PartUsedCount();
      }
      bool unique() const {
        return (count!=nullptr)&&count->IsOnly()&&(!count->IsPartUsed());
      }

    private:

      void IncCount() {
        assert(part_flag!=AccessContentName::Unassigned);
        if(part_flag==AccessContentName::GlobalUsed)    count->Inc();
        else if(part_flag==AccessContentName::PartUsed) count->IncPart();
      }

  };

  template <typename T>
  bool operator==(const accessed_ptr<T>& lhs,const accessed_ptr<T>& rhs) {
    return lhs.get()==rhs.get();
  }
  template <typename T>
  bool operator!=(const accessed_ptr<T>& lhs,const accessed_ptr<T>& rhs) {
    return lhs.get()!=rhs.get();
  }
  template <typename T>
  bool operator<(const accessed_ptr<T>& lhs,const accessed_ptr<T>& rhs) {
    return lhs.get()<rhs.get();
  }
  template <typename T>
  bool operator>(const accessed_ptr<T>& lhs,const accessed_ptr<T>& rhs) {
    return lhs.get()>rhs.get();
  }
  template <typename T>
  bool operator<=(const accessed_ptr<T>& lhs,const accessed_ptr<T>& rhs) {
    return !(lhs.get()>rhs.get());
  }
  template <typename T>
  bool operator>=(const accessed_ptr<T>& lhs,const accessed_ptr<T>& rhs) {
    return !(lhs.get()<rhs.get());
  }

}

#include <cstddef>

namespace mysimulator {

  template <typename T>
  bool operator==(const accessed_ptr<T>& lhs,const std::nullptr_t rhs) {
    return !lhs;
  }
  template <typename T>
  bool operator==(const std::nullptr_t lhs,const accessed_ptr<T>& rhs) {
    return !rhs;
  }
  template <typename T>
  bool operator!=(const accessed_ptr<T>& lhs,const std::nullptr_t rhs) {
    return (bool)lhs;
  }
  template <typename T>
  bool operator!=(const std::nullptr_t lhs,const accessed_ptr<T>& rhs) {
    return (bool)rhs;
  }
  template <typename T>
  bool operator<(const accessed_ptr<T>& lhs,const std::nullptr_t rhs) {
    return lhs.get()<nullptr;
  }
  template <typename T>
  bool operator<(const std::nullptr_t lhs,const accessed_ptr<T>& rhs) {
    return nullptr<rhs.get();
  }
  template <typename T>
  bool operator>(const accessed_ptr<T>& lhs,const std::nullptr_t rhs) {
    return nullptr<lhs;
  }
  template <typename T>
  bool operator>(const std::nullptr_t lhs,const accessed_ptr<T>& rhs) {
    return rhs<nullptr;
  }
  template <typename T>
  bool operator<=(const accessed_ptr<T>& lhs,const std::nullptr_t rhs) {
    return !(nullptr<lhs);
  }
  template <typename T>
  bool operator<=(const std::nullptr_t lhs,const accessed_ptr<T>& rhs) {
    return !(rhs<nullptr);
  }
  template <typename T>
  bool operator>=(const accessed_ptr<T>& lhs,const std::nullptr_t rhs) {
    return !(lhs<nullptr);
  }
  template <typename T>
  bool operator>=(const std::nullptr_t lhs,const accessed_ptr<T>& rhs) {
    return !(nullptr<rhs);
  }

}

#include <ostream>

namespace std {

  template <typename T,typename U,typename V>
  basic_ostream<U,V>& operator<<(basic_ostream<U,V>& os,
                                 const mysimulator::accessed_ptr<T>& APTR) {
    return os<<APTR.get();
  }

}

#include <algorithm>

namespace std {

  template <typename T>
  void swap(mysimulator::accessed_ptr<T>& l, mysimulator::accessed_ptr<T>& r) {
    l.swap(r);
  }

}

#endif

