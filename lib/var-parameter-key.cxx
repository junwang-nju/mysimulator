
#include "var-parameter-key.h"

namespace std {

  void varParameterKey::SetIndexSize(const unsigned int NI) {
    index().allocate(NI);
  }

}

