
#ifndef _Random_BoxMuller_IO_H_
#define _Random_BoxMuller_IO_H_

#include "random/box-muller/interface.h"

namespace {

  template <typename UR>
  void Write(const BoxMuller<UR>& R) {
    assert(R.IsValid());
    Write(R.urng,"\t");
    unsigned long long* p=
      reinterpret_cast<unsigned long long*>(const_cast<double*>(R.s._data));
    Write(p[0],"\t",p[1],"\t",p[3]);
    Write("\t",R.isSecond);
  }

}

#endif

