
#ifndef _Basic_Memory_Access_Count_H_
#define _Basic_Memory_Access_Count_H_

#include <cassert>

namespace mysimulator {

  class __memory_access_count {

    public:

      typedef __memory_access_count  Type;

    private:

      unsigned int count;
      unsigned int part_count;

    public:

      __memory_access_count() : count(0), part_count(0) {}
      __memory_access_count(const Type&) = delete;
      ~__memory_access_count() { reset(); }

      Type& operator=(const Type&) = delete;

      operator bool() const   { return count>0; }
      bool IsOnly() const     { return count==1; }
      bool IsPartUsed() const { return part_count>0; }

      unsigned int GlobalUseCount() const { return count; }
      unsigned int PartUseCount()   const { return part_count; }

      void Inc() { assert(count<0xFFFFFFFFU); ++count; }
      void Dec() { assert(count>0); --count; }
      void IncPart() {
        assert((bool)(*this));
        assert(part_count<0xFFFFFFFFU);
        ++part_count;
      }
      void DecPart() {
        assert((bool)(*this));
        assert(part_count>0);
        --part_count;
      }

      void reset() { part_count=0; count=0; }

  };

}

#endif

