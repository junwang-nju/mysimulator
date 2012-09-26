
#ifndef _Memory_Accessed_Pointer_H_
#define _Memory_Accessed_Pointer_H_

#include "memory/access-count.h"

namespace mysimulator {

  enum class AccessContentName { Unassigned, GlobalUsed, PartUsed };

  template <typename T>
  class accessed_ptr {

    public:

      typedef accessed_ptr<T>   Type;
      typedef T* pointer;
      typedef const T* const_pointer;
      typedef T& reference;
      typedef memory_access_count*  count_pointer;

    private:

      enum class AllocationName { NeedFree, NeedNotFree };

      pointer         ptr;
      count_pointer   count;
      AccessContentName part_flag;

    public:

      accessed_ptr() : ptr(nullptr), count(nullptr),
                       part_flag(AccessContentName::Unassigned) {}
      accessed_ptr(const_pointer PTR,
                   AccessContentName PF=AccessContentName::GlobalUsed)
        : ptr(const_cast<pointer>(PTR)), count(new memory_access_count),
          part_flag(PF) {
        assert(PTR!=nullptr);
        IncCount();
      }
      accessed_ptr(const Type& APTR,unsigned int BgIdx=0)
        : ptr(const_cast<pointer>(APTR.ptr)+BgIdx),
          count(const_cast<count_pointer>(APTR.count)),
          part_flag(BgIdx==0?AccessContentName::GlobalUsed:
                             AccessContentName::PartUsed) {
        assert((bool)APTR);
        IncCount();
      }
      ~accessed_ptr() {
        if((bool)(*this)) {
          AllocationName alloc_flag=AllocationName::NeedNotFree;
          if(part_flag==AccessContentName::PartUsed)   count->DecPart();
          else if(count->IsOnly()) {
            if(count->IsPartUsed()) throw "Need to Free Part Content First!";
            else {
              count->~memory_access_count();
              alloc_flag=AllocationName::NeedFree;
            }
          } else count->Dec();
          if(alloc_flag==AllocationName::NeedFree)  ptr->~T();
          ptr=nullptr;
          count=nullptr;
          part_flag=AccessContentName::Unassigned;
        }
      }

      Type& operator=(const Type& APTR) {
        assert((bool)APTR);
        this->~accessed_ptr();
        ptr=const_cast<pointer>(APTR.ptr);
        count=const_cast<count_pointer>(APTR.count);
        part_flag=APTR.part_flag;
        IncCount();
        return *this;
      }
      Type& operator=(Type&& APTR) {
        assert((bool)APTR);
        this->~accessed_ptr();
        ptr=APTR.ptr;
        count=APTR.count;
        part_flag=APTR.part_flag;
        IncCount();
        return *this;
      }

      void reset() {  this->~accessed_ptr();  }
      void reset(const pointer* PTR,
                 AccessContentName PF=AccessContentName::GlobalUsed) {
        assert(PTR!=nullptr);
        this->~accessed_ptr();
        ptr=const_cast<pointer>(PTR);
        count=new count_pointer;
        part_flag=PF;
        IncCount();
      }

      void swap(Type& APTR) {
        pointer P;
        P=ptr;  ptr=APTR.ptr; APTR.ptr=P;
        count_pointer PC;
        PC=count; count=APTR.count; APTR.count=PC;
        AccessContentName PP;
        PP=part_flag; part_flag=APTR.part_flag; APTR.part_flag=PP;
      }

      pointer get() const { return ptr; }
      reference operator*() { return *ptr; }
      pointer operator->() { return ptr; }

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

