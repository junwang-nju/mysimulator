
#include "util.h"
#include <cctype>

namespace std {

  void Nullify(int& I) { I=0; }

  void Nullify(unsigned int& I) { I=0U; }

  void Nullify(double& D) { D=0.; }

  int compare(const int I, const int J) { return (I<J?-1:(I>J?1:0)); }

  int compare(const double DI, const double DJ) {
    return (DI<DJ?-1:(DI>DJ?1:0));
  }

  void toupper(char* dest, const char* src, const unsigned int n) {
    for(unsigned int i=0;i<n;++i) dest[i]=toupper(src[i]);
  }

  void tolower(char* dest, const char* src, const unsigned int n) {
    for(unsigned int i=0;i<n;++i) dest[i]=tolower(src[i]);
  }

}

