
#ifndef _Hash_H_
#define _Hash_H_

#include "data/basic/vector.h"

namespace std {

  struct Hash : public Vector<unsigned int> {

    typedef Vector<unsigned int> ParentType;

    Hash() : ParentType() {}
    Hash(const Hash&) { Error("Cannot create Hash"); }
    Hash& operator=(const Hash&) {
      Error("Cannot copy Hash");
      return *this;
    }
    ~Hash() { release(*this); }

  };

  bool IsAvailable(const Hash& h) {
    return IsAvailable(static_cast<const Vector<unsigned int>&>(h));
  }

  void release(Hash& h) { release(static_cast<Vector<unsigned int>&>(h)); }

  void copy(Hash& h, const Hash& ch) {
    copy(static_cast<Vector<unsigned int>&>(h),
         static_cast<const Vector<unsigned int>&>(ch));
  }

  void refer(Hash& h, const Hash& rh) {
    refer(static_cast<Vector<unsigned int>&>(h),
          static_cast<const Vector<unsigned int>&>(rh));
  }

  void allocate(Hash& h) {
    allocate(static_cast<Vector<unsigned int>&>(h),3);
    copy(static_cast<Vector<unsigned int>&>(h),0);
  }

  bool compare(const Hash& hA, const Hash& hB) {
    assert(hA.size==3);
    assert(hB.size==3);
    for(unsigned int i=0;i<3;++i) if(hA[i]!=hB[i])  return (hA[i]>hB[i]?1:-1);
    return 0;
  }

}

#endif

