
#ifndef _Random_Base_Interface_H_
#define _Random_Base_Interface_H_

#include <ctime>
#include "array/1d/content/interface.h"
#include "intrinsic-type/constant.h"

namespace mysimulator {

  struct RandomBase {

    virtual void init(const unsigned int&)=0;
    virtual const double randomDouble()=0;
    virtual const unsigned int randomUInt()=0;

    void initWithTime() { init(static_cast<unsigned int>(time(0))); }

    void fill(double* const& v, const unsigned int& sz,
              const unsigned int& off=uZero, const unsigned int& step=uOne) {
      for(unsigned int i=0,k=off;i<sz;++i,k+=step)  v[k]=randomDouble();
    }

    void fill(unsigned int* const& v, const unsigned int& sz,
              const unsigned int& off=uZero, const unsigned int& step=uOne) {
      for(unsigned int i=0,k=off;i<sz;++i,k+=step)  v[k]=randomUInt();
    }

    template <typename T>
    void fill(Array1DContent<T>& v) { fill(v.start,v.size); }

  };

}

#endif

