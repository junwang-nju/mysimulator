
#ifndef _Random_Base_Interface_H_
#define _Random_Base_Interface_H_

#include <ctime>

namespace mysimulator {

  struct RandomBase {

    virtual void init(const unsigned int)=0;
    virtual const double randomDouble()=0;
    virtual const unsigned int randomUnsignedInt()=0;

    void initWithTime() { init(static_cast<unsigned int>(time(0))); }
    void fill(double* v,const unsigned int sz,
              const unsigned int off=uZero,const unsigned int step=uOne) {
      for(unsigned int i=0,k=off;i<sz;++i,k+=step) v[k]=randomDouble();
    }
    void fill(unsigned int* v,const unsigned int sz,
              const unsigned int off=uZero,const unsigned int step=uOne) {
      for(unsigned int i=0,k=off;i<sz;++i,k+=step) v[k]=randomUnsignedInt();
    }

  };

}

#endif

