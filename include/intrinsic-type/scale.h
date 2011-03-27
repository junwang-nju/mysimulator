
#ifndef _Intrinsic_Type_Scale_H_
#define _Intrinsic_Type_Scale_H_

namespace mysimulator {

  void scale(long double& ld, const long double& ld2) { ld*=ld2; }
  void scale(long double& ld, const double& d) { ld*=d; }
  void scale(long double& ld, const float& f) { ld*=f; }
  void scale(long double& ld, const long long& ll) { ld*=ll; }
  void scale(long double& ld, const unsigned long long& ull) { ld*=ull; }
  void scale(long double& ld, const int& i) { ld*=i; }
  void scale(long double& ld, const unsigned int& u) { ld*=u; }
  void scale(long double& ld, const long& l) { ld*=l; }
  void scale(long double& ld, const unsigned long& ul) { ld*=ul; }
  void scale(long double& ld, const short& s) { ld*=s; }
  void scale(long double& ld, const unsigned short& us) { ld*=us; }
  void scale(long double& ld, const char& c) { ld*=c; }
  void scale(long double& ld, const unsigned char& uc) { ld*=uc; }

  void scale(double& d, const double& d2) { d*=d2; }
  void scale(double& d, const float& f) { d*=f; }
  void scale(double& d, const long long& ll) { d*=ll; }
  void scale(double& d, const unsigned long long& ull) { d*=ull; }
  void scale(double& d, const int& i) { d*=i; }
  void scale(double& d, const unsigned int& u) { d*=u; }
  void scale(double& d, const long& l) { d*=l; }
  void scale(double& d, const unsigned long& ul) { d*=ul; }
  void scale(double& d, const short& s) { d*=s; }
  void scale(double& d, const unsigned short& us) { d*=us; }
  void scale(double& d, const char& c) { d*=c; }
  void scale(double& d, const unsigned char& uc) { d*=uc; }

  void scale(float& f, const float& f2) { f*=f2; }
  void scale(float& f, const long long& ll) { f*=ll; }
  void scale(float& f, const unsigned long long& ull) { f*=ull; }
  void scale(float& f, const int& i) { f*=i; }
  void scale(float& f, const unsigned int& u) { f*=u; }
  void scale(float& f, const long& l) { f*=l; }
  void scale(float& f, const unsigned long& ul) { f*=ul; }
  void scale(float& f, const short& s) { f*=s; }
  void scale(float& f, const unsigned short& us) { f*=us; }
  void scale(float& f, const char& c) { f*=c; }
  void scale(float& f, const unsigned char& uc) { f*=uc; }

  void scale(long long& ll, const long long& ll2) { ll*=ll2; }
  void scale(long long& ll, const int& i) { ll*=i; }
  void scale(long long& ll, const unsigned int& u) { ll*=u; }
  void scale(long long& ll, const long& l) { ll*=l; }
  void scale(long long& ll, const unsigned long& ul) { ll*=ul; }
  void scale(long long& ll, const short& s) { ll*=s; }
  void scale(long long& ll, const unsigned short& us) { ll*=us; }
  void scale(long long& ll, const char& c) { ll*=c; }
  void scale(long long& ll, const unsigned char& uc) { ll*=uc; }

  void scale(unsigned long long& ull, const unsigned long long& ull2) {
    ull*=ull2;
  }
  void scale(unsigned long long& ull, const unsigned int& u) { ull*=u; }
  void scale(unsigned long long& ull, const unsigned long& ul) { ull*=ul; }
  void scale(unsigned long long& ull, const unsigned short& us) { ull*=us; }
  void scale(unsigned long long& ull, const unsigned char& uc) { ull*=uc; }

  void scale(int& i, const int& i2) { i*=i2; }
  void scale(int& i, const long& l) { i*=l; }
  void scale(int& i, const short& s) { i*=s; }
  void scale(int& i, const unsigned short& us) { i*=us; }
  void scale(int& i, const char& c) { i*=c; }
  void scale(int& i, const unsigned char& uc) { i*=uc; }

  void scale(unsigned int& u, const unsigned int& u2) { u*=u2; }
  void scale(unsigned int& u, const unsigned long& ul) { u*=ul; }
  void scale(unsigned int& u, const unsigned short& us) { u*=us; }
  void scale(unsigned int& u, const unsigned char& uc) { u*=uc; }

  void scale(long& l, const int& i) { l*=i; }
  void scale(long& l, const long& l2) { l*=l2; }
  void scale(long& l, const short& s) { l*=s; }
  void scale(long& l, const unsigned short& us) { l*=us; }
  void scale(long& l, const char& c) { l*=c; }
  void scale(long& l, const unsigned char& uc) { l*=uc; }

  void scale(unsigned long& ul, const unsigned long& ul2) { ul*=ul2; }
  void scale(unsigned long& ul, const unsigned int& u) { ul*=u; }
  void scale(unsigned long& ul, const unsigned short& us) { ul*=us; }
  void scale(unsigned long& ul, const unsigned char& uc) { ul*=uc; }

  void scale(short& s, const short& s2) { s*=s2; }
  void scale(short& s, const char& c) { s*=c; }
  void scale(short& s, const unsigned char& uc) { s*=uc; }

  void scale(unsigned short& us, const unsigned short& us2) { us*=us2; }
  void scale(unsigned short& us, const unsigned char& uc) { us*=uc; }

  void scale(char& c, const char& c2) { c*=c2; }

  void scale(unsigned char& c, const unsigned char& uc) { c*=uc; }

}

#endif

