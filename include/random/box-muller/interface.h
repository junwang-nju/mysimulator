
#ifndef _Random_Box_Muller_Interface_H_
#define _Random_Box_Muller_Interface_H_

#include "random/base/interface.h"

namespace mysimulator {

  template <typename UniformRNG>
  struct BoxMuller : public RandomBase {

    typedef BoxMuller<UniformRNG>   Type;
    typedef RandomBase    ParentType;

    UniformRNG urng;
    bool isSecond;

    BoxMuller() : urng(), isSecond(true) {}
    BoxMuller(const Type&) { Error("Copier of BoxMuller Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for BoxMuller Disabled!");
      return *this;
    }
    ~BoxMuller() { clearData(); }

    void clearData() { urng.clearData(); isSecond=true; }

  };

  template <typename UniformRNG>
  bool IsValid(const BoxMuller<UniformRNG>& G) { return IsValid(G.urng); }

  template <typename UniformRNG>
  void release(BoxMuller<UniformRNG>& G) { G.clearData(); }

}

#endif

