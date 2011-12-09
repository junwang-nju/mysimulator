
#ifndef _Random_MT_Interface_H_
#define _Random_MT_Interface_H_

#include "random/mt/name.h"

namespace mysimulator {

  template <MTMethodName MM, unsigned int Fac=0U>
  struct MersenneTwister {
    public:
      typedef MersenneTwister<MM,Fac>   Type;
      MersenneTwister() {}
      ~MersenneTwister() { clearData(); }

      void clearData() {}
      bool isvalid() const { return false; }

    private:
      MersenneTwister(const Type&) {}
      Type& operator=(const Type&) { return *this; }
  };

  template <MTMethodName MM, unsigned int Fac>
  void release(MersenneTwister<MM,Fac>& R) { R.clearData(); }

  template <MTMethodName MM, unsigned int Fac>
  bool IsValid(const MersenneTwister<MM,Fac>& R) { return R.isvalid(); }

}

#include "random/mt/standard/specification.h"
#include "random/mt/dsfmt/specification.h"

#endif

