
#ifndef _Utility_H_
#define _Utility_H_

namespace std {
  void Nullify(int& I);
  void Nullify(unsigned int& I);
  void Nullify(double& D);
  int compare(const int I, const int J);
  int compare(const double DI, const double DJ);
  void toupper(char* dest, const char* src, const unsigned int n);
  void tolower(char* dest, const char* src, const unsigned int n);
}

#endif

