
#ifndef _Intrinsic_Type_Utility_Copy_H_
#define _Intrinsic_Type_Utility_Copy_H_

namespace mysimulator {

  void copy(long double& d, const long double& rd) { d=rd; }
  void copy(long double& d, const double& rd) { d=rd; }
  void copy(long double& d, const float& rd) { d=rd; }
  void copy(long double& d, const long long int& i) { d=i; }
  void copy(long double& d, const unsigned long long int& i) { d=i; }
  void copy(long double& d, const int& i) { d=i; }
  void copy(long double& d, const unsigned int& i) { d=i; }
  void copy(long double& d, const long& i) { d=i; }
  void copy(long double& d, const unsigned long& i) { d=i; }
  void copy(long double& d, const short& s) { d=s; }
  void copy(long double& d, const unsigned short& s) { d=s; }
  void copy(long double& d, const char& c) { d=c; }
  void copy(long double& d, const unsigned char& c) { d=c; }

  void copy(double& d, const double& rd) { d=rd; }
  void copy(double& d, const float& rd) { d=rd; }
  void copy(double& d, const long long int& i) { d=i; }
  void copy(double& d, const unsigned long long int& i) { d=i; }
  void copy(double& d, const int& i) { d=i; }
  void copy(double& d, const unsigned int& i) { d=i; }
  void copy(double& d, const long& i) { d=i; }
  void copy(double& d, const unsigned long& i) { d=i; }
  void copy(double& d, const short& s) { d=s; }
  void copy(double& d, const unsigned short& s) { d=s; }
  void copy(double& d, const char& c) { d=c; }
  void copy(double& d, const unsigned char& c) { d=c; }

  void copy(float& d, const float& rd) { d=rd; }
  void copy(float& d, const long long int& i) { d=i; }
  void copy(float& d, const unsigned long long int& i) { d=i; }
  void copy(float& d, const int& i) { d=i; }
  void copy(float& d, const unsigned int& i) { d=i; }
  void copy(float& d, const long& i) { d=i; }
  void copy(float& d, const unsigned long& i) { d=i; }
  void copy(float& d, const short& s) { d=s; }
  void copy(float& d, const unsigned short& s) { d=s; }
  void copy(float& d, const char& c) { d=c; }
  void copy(float& d, const unsigned char& c) { d=c; }

  void copy(long long int& i, const long long int& l) { i=l; }
  void copy(long long int& i, const int& ri) { i=ri; }
  void copy(long long int& i, const unsigned int& ri) { i=ri; }
  void copy(long long int& i, const long& l) { i=l; }
  void copy(long long int& i, const unsigned long& l) { i=l; }
  void copy(long long int& i, const short& s) { i=s; }
  void copy(long long int& i, const unsigned short& s) { i=s; }
  void copy(long long int& i, const char& c) { i=c; }
  void copy(long long int& i, const unsigned char& c) { i=c; }

  void copy(unsigned long long int& i, const unsigned long long int& l){ i=l; }
  void copy(unsigned long long int& i, const unsigned int& ri) { i=ri; }
  void copy(unsigned long long int& i, const unsigned long& l) { i=l; }
  void copy(unsigned long long int& i, const unsigned short& s) { i=s; }
  void copy(unsigned long long int& i, const char& c) { i=c; }
  void copy(unsigned long long int& i, const unsigned char& c) { i=c; }

  void copy(int& i, const int& ri) { i=ri; }
  void copy(int& i, const long& l) { i=l; }
  void copy(int& i, const short& s) { i=s; }
  void copy(int& i, const unsigned short& s) { i=s; }
  void copy(int& i, const char& c) { i=c; }
  void copy(int& i, const unsigned char& c) { i=c; }

  void copy(unsigned int& i, const unsigned int& ri) { i=ri; }
  void copy(unsigned int& i, const unsigned long& l) { i=l; }
  void copy(unsigned int& i, const unsigned short& s) { i=s; }
  void copy(unsigned int& i, const char& c) { i=c; }
  void copy(unsigned int& i, const unsigned char& c) { i=c; }

  void copy(long& i, const int& ri) { i=ri; }
  void copy(long& i, const long& l) { i=l; }
  void copy(long& i, const short& s) { i=s; }
  void copy(long& i, const unsigned short& s) { i=s; }
  void copy(long& i, const char& c) { i=c; }
  void copy(long& i, const unsigned char& c) { i=c; }

  void copy(unsigned long& i, const unsigned int& ri) { i=ri; }
  void copy(unsigned long& i, const unsigned long& l) { i=l; }
  void copy(unsigned long& i, const unsigned short& s) { i=s; }
  void copy(unsigned long& i, const char& c) { i=c; }
  void copy(unsigned long& i, const unsigned char& c) { i=c; }

  void copy(short& s, const short& rs) { s=rs; }
  void copy(short& s, const char& c) { s=c; }
  void copy(short& s, const unsigned char& c) { s=c; }

  void copy(unsigned short& s, const unsigned short& rs) { s=rs; }
  void copy(unsigned short& s, const char& c) { s=c; }
  void copy(unsigned short& s, const unsigned char& c) { s=c; }

  void copy(char& c, const char& rc) { c=rc; }
  void copy(char& c, const unsigned char& rc) { c=rc; }

  void copy(unsigned char& c, const char& rc) { c=rc; }
  void copy(unsigned char& c, const unsigned char& rc) { c=rc; }

  void copy(bool& b, const bool& rb) { b=rb; }
  void copy(bool& b, const long long int& i) { b=(i==0?false:true); }
  void copy(bool& b, const unsigned long long int& i) { b=(i==0?false:true); }
  void copy(bool& b, const int& i) { b=(i==0?false:true); }
  void copy(bool& b, const unsigned int& i) { b=(i==0?false:true); }
  void copy(bool& b, const long& i) { b=(i==0?false:true); }
  void copy(bool& b, const unsigned long& i) { b=(i==0?false:true); }
  void copy(bool& b, const short& i) { b=(i==0?false:true); }
  void copy(bool& b, const unsigned short& i) { b=(i==0?false:true); }
  void copy(bool& b, const char& i) { b=(i==0?false:true); }
  void copy(bool& b, const unsigned char& i) { b=(i==0?false:true); }

}

#endif

