
#include "util.h"

namespace std {

  void Nullify(int& I) { I=0; }

  void Nullify(unsigned int& I) { I=0U; }

  void Nullify(double& D) { D=0.; }

  int compare(const int I, const int J) { return (I<J?-1:(I>J?1:0)); }

  int compare(const double DI, const double DJ) {
    return (DI<DJ?-1:(DI>DJ?1:0));
  }

}

