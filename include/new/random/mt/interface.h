
#ifndef _Random_MT_Interface_H_
#define _Random_MT_Interface_H_

#include "random/mt/name.h"

namespace mysimulator {

  template <MTMethodName MM>
  struct MersenneTwister {
    public:
      typedef MersenneTwister<MM>   Type;
      MersenneTwister() {}
      ~MersenneTwister() { clearData(); }

      void clearData() {}
      bool isvalid() const { return false; }

    private:
      MersenneTwister(const Type&) {}
      Type& operator=(const Type&) { return *this; }
  };

  template <MTMethodName MM>
  void release(MersenneTwister<MM>& R) { R.clearData(); }

  template <MTMethodName MM>
  bool IsValid(const MersenneTwister<MM>& R) { return R.isvalid(); }

}

#endif

