
#ifndef _Intrinsic_Type_Shift_H_
#define _Intrinsic_Type_Shift_H_

namespace mysimulator {

  void shift(long double& a,
             const long double& b,
             const long double& c) { a+=b*c; }
  void shift(long double& a,
             const long double& b,
             const double& c) { a+=b*c; }
  void shift(long double& a,
             const long double& b,
             const float& c) { a+=b*c; }
  void shift(long double& a,
             const long double& b,
             const long long& c) { a+=b*c; }
  void shift(long double& a,
             const long double& b,
             const unsigned long long& c) { a+=b*c; }
  void shift(long double& a,
             const long double& b,
             const int& c) { a+=b*c; }
  void shift(long double& a,
             const long double& b,
             const unsigned int& c) { a+=b*c; }
  void shift(long double& a,
             const long double& b,
             const long& c) { a+=b*c; }
  void shift(long double& a,
             const long double& b,
             const unsigned long& c) { a+=b*c; }
  void shift(long double& a,
             const long double& b,
             const short& c) { a+=b*c; }
  void shift(long double& a,
             const long double& b,
             const unsigned short& c) { a+=b*c; }
  void shift(long double& a,
             const long double& b,
             const char& c) { a+=b*c; }
  void shift(long double& a,
             const long double& b,
             const unsigned char& c) { a+=b*c; }

  void shift(long double& a,
             const double& b,
             const long double& c) { a+=b*c; }
  void shift(long double& a,
             const double& b,
             const double& c) { a+=b*c; }
  void shift(long double& a,
             const double& b,
             const float& c) { a+=b*c; }
  void shift(long double& a,
             const double& b,
             const long long& c) { a+=b*c; }
  void shift(long double& a,
             const double& b,
             const unsigned long long& c) { a+=b*c; }
  void shift(long double& a,
             const double& b,
             const int& c) { a+=b*c; }
  void shift(long double& a,
             const double& b,
             const unsigned int& c) { a+=b*c; }
  void shift(long double& a,
             const double& b,
             const long& c) { a+=b*c; }
  void shift(long double& a,
             const double& b,
             const unsigned long& c) { a+=b*c; }
  void shift(long double& a,
             const double& b,
             const short& c) { a+=b*c; }
  void shift(long double& a,
             const double& b,
             const unsigned short& c) { a+=b*c; }
  void shift(long double& a,
             const double& b,
             const char& c) { a+=b*c; }
  void shift(long double& a,
             const double& b,
             const unsigned char& c) { a+=b*c; }

  void shift(long double& a,
             const float& b,
             const long double& c) { a+=b*c; }
  void shift(long double& a,
             const float& b,
             const double& c) { a+=b*c; }
  void shift(long double& a,
             const float& b,
             const float& c) { a+=b*c; }
  void shift(long double& a,
             const float& b,
             const long long& c) { a+=b*c; }
  void shift(long double& a,
             const float& b,
             const unsigned long long& c) { a+=b*c; }
  void shift(long double& a,
             const float& b,
             const int& c) { a+=b*c; }
  void shift(long double& a,
             const float& b,
             const unsigned int& c) { a+=b*c; }
  void shift(long double& a,
             const float& b,
             const long& c) { a+=b*c; }
  void shift(long double& a,
             const float& b,
             const unsigned long& c) { a+=b*c; }
  void shift(long double& a,
             const float& b,
             const short& c) { a+=b*c; }
  void shift(long double& a,
             const float& b,
             const unsigned short& c) { a+=b*c; }
  void shift(long double& a,
             const float& b,
             const char& c) { a+=b*c; }
  void shift(long double& a,
             const float& b,
             const unsigned char& c) { a+=b*c; }

  void shift(long double& a,
             const long long& b,
             const long double& c) { a+=b*c; }
  void shift(long double& a,
             const long long& b,
             const double& c) { a+=b*c; }
  void shift(long double& a,
             const long long& b,
             const float& c) { a+=b*c; }
  void shift(long double& a,
             const long long& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const long long& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const long long& b,
             const int& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const long long& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const long long& b,
             const long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const long long& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const long long& b,
             const short& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const long long& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const long long& b,
             const char& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const long long& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(long double& a,
             const unsigned long long& b,
             const long double& c) { a+=b*c; }
  void shift(long double& a,
             const unsigned long long& b,
             const double& c) { a+=b*c; }
  void shift(long double& a,
             const unsigned long long& b,
             const float& c) { a+=b*c; }
  void shift(long double& a,
             const unsigned long long& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned long long& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned long long& b,
             const int& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned long long& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned long long& b,
             const long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned long long& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned long long& b,
             const short& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned long long& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned long long& b,
             const char& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned long long& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(long double& a,
             const int& b,
             const long double& c) { a+=b*c; }
  void shift(long double& a,
             const int& b,
             const double& c) { a+=b*c; }
  void shift(long double& a,
             const int& b,
             const float& c) { a+=b*c; }
  void shift(long double& a,
             const int& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const int& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const int& b,
             const int& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const int& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const int& b,
             const long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const int& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const int& b,
             const short& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const int& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const int& b,
             const char& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const int& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(long double& a,
             const unsigned int& b,
             const long double& c) { a+=b*c; }
  void shift(long double& a,
             const unsigned int& b,
             const double& c) { a+=b*c; }
  void shift(long double& a,
             const unsigned int& b,
             const float& c) { a+=b*c; }
  void shift(long double& a,
             const unsigned int& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned int& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned int& b,
             const int& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned int& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned int& b,
             const long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned int& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned int& b,
             const short& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned int& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned int& b,
             const char& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned int& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(long double& a,
             const long& b,
             const long double& c) { a+=b*c; }
  void shift(long double& a,
             const long& b,
             const double& c) { a+=b*c; }
  void shift(long double& a,
             const long& b,
             const float& c) { a+=b*c; }
  void shift(long double& a,
             const long& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const long& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const long& b,
             const int& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const long& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const long& b,
             const long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const long& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const long& b,
             const short& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const long& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const long& b,
             const char& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const long& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(long double& a,
             const unsigned long& b,
             const long double& c) { a+=b*c; }
  void shift(long double& a,
             const unsigned long& b,
             const double& c) { a+=b*c; }
  void shift(long double& a,
             const unsigned long& b,
             const float& c) { a+=b*c; }
  void shift(long double& a,
             const unsigned long& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned long& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned long& b,
             const int& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned long& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned long& b,
             const long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned long& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned long& b,
             const short& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned long& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned long& b,
             const char& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned long& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(long double& a,
             const short& b,
             const long double& c) { a+=b*c; }
  void shift(long double& a,
             const short& b,
             const double& c) { a+=b*c; }
  void shift(long double& a,
             const short& b,
             const float& c) { a+=b*c; }
  void shift(long double& a,
             const short& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const short& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const short& b,
             const int& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const short& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const short& b,
             const long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const short& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const short& b,
             const short& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const short& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const short& b,
             const char& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const short& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(long double& a,
             const unsigned short& b,
             const long double& c) { a+=b*c; }
  void shift(long double& a,
             const unsigned short& b,
             const double& c) { a+=b*c; }
  void shift(long double& a,
             const unsigned short& b,
             const float& c) { a+=b*c; }
  void shift(long double& a,
             const unsigned short& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned short& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned short& b,
             const int& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned short& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned short& b,
             const long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned short& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned short& b,
             const short& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned short& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned short& b,
             const char& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned short& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(long double& a,
             const char& b,
             const long double& c) { a+=b*c; }
  void shift(long double& a,
             const char& b,
             const double& c) { a+=b*c; }
  void shift(long double& a,
             const char& b,
             const float& c) { a+=b*c; }
  void shift(long double& a,
             const char& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const char& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const char& b,
             const int& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const char& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const char& b,
             const long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const char& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const char& b,
             const short& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const char& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const char& b,
             const char& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const char& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(long double& a,
             const unsigned char& b,
             const long double& c) { a+=b*c; }
  void shift(long double& a,
             const unsigned char& b,
             const double& c) { a+=b*c; }
  void shift(long double& a,
             const unsigned char& b,
             const float& c) { a+=b*c; }
  void shift(long double& a,
             const unsigned char& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned char& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned char& b,
             const int& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned char& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned char& b,
             const long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned char& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned char& b,
             const short& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned char& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned char& b,
             const char& c) { a+=b*(c+0.); }
  void shift(long double& a,
             const unsigned char& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(double& a,
             const double& b,
             const double& c) { a+=b*c; }
  void shift(double& a,
             const double& b,
             const float& c) { a+=b*c; }
  void shift(double& a,
             const double& b,
             const long long& c) { a+=b*c; }
  void shift(double& a,
             const double& b,
             const unsigned long long& c) { a+=b*c; }
  void shift(double& a,
             const double& b,
             const int& c) { a+=b*c; }
  void shift(double& a,
             const double& b,
             const unsigned int& c) { a+=b*c; }
  void shift(double& a,
             const double& b,
             const long& c) { a+=b*c; }
  void shift(double& a,
             const double& b,
             const unsigned long& c) { a+=b*c; }
  void shift(double& a,
             const double& b,
             const short& c) { a+=b*c; }
  void shift(double& a,
             const double& b,
             const unsigned short& c) { a+=b*c; }
  void shift(double& a,
             const double& b,
             const char& c) { a+=b*c; }
  void shift(double& a,
             const double& b,
             const unsigned char& c) { a+=b*c; }

  void shift(double& a,
             const float& b,
             const double& c) { a+=b*c; }
  void shift(double& a,
             const float& b,
             const float& c) { a+=b*c; }
  void shift(double& a,
             const float& b,
             const long long& c) { a+=b*c; }
  void shift(double& a,
             const float& b,
             const unsigned long long& c) { a+=b*c; }
  void shift(double& a,
             const float& b,
             const int& c) { a+=b*c; }
  void shift(double& a,
             const float& b,
             const unsigned int& c) { a+=b*c; }
  void shift(double& a,
             const float& b,
             const long& c) { a+=b*c; }
  void shift(double& a,
             const float& b,
             const unsigned long& c) { a+=b*c; }
  void shift(double& a,
             const float& b,
             const short& c) { a+=b*c; }
  void shift(double& a,
             const float& b,
             const unsigned short& c) { a+=b*c; }
  void shift(double& a,
             const float& b,
             const char& c) { a+=b*c; }
  void shift(double& a,
             const float& b,
             const unsigned char& c) { a+=b*c; }

  void shift(double& a,
             const long long& b,
             const double& c) { a+=b*c; }
  void shift(double& a,
             const long long& b,
             const float& c) { a+=b*c; }
  void shift(double& a,
             const long long& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const long long& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const long long& b,
             const int& c) { a+=b*(c+0.); }
  void shift(double& a,
             const long long& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(double& a,
             const long long& b,
             const long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const long long& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const long long& b,
             const short& c) { a+=b*(c+0.); }
  void shift(double& a,
             const long long& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(double& a,
             const long long& b,
             const char& c) { a+=b*(c+0.); }
  void shift(double& a,
             const long long& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(double& a,
             const unsigned long long& b,
             const double& c) { a+=b*c; }
  void shift(double& a,
             const unsigned long long& b,
             const float& c) { a+=b*c; }
  void shift(double& a,
             const unsigned long long& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned long long& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned long long& b,
             const int& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned long long& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned long long& b,
             const long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned long long& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned long long& b,
             const short& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned long long& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned long long& b,
             const char& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned long long& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(double& a,
             const int& b,
             const double& c) { a+=b*c; }
  void shift(double& a,
             const int& b,
             const float& c) { a+=b*c; }
  void shift(double& a,
             const int& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const int& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const int& b,
             const int& c) { a+=b*(c+0.); }
  void shift(double& a,
             const int& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(double& a,
             const int& b,
             const long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const int& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const int& b,
             const short& c) { a+=b*(c+0.); }
  void shift(double& a,
             const int& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(double& a,
             const int& b,
             const char& c) { a+=b*(c+0.); }
  void shift(double& a,
             const int& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(double& a,
             const unsigned int& b,
             const double& c) { a+=b*c; }
  void shift(double& a,
             const unsigned int& b,
             const float& c) { a+=b*c; }
  void shift(double& a,
             const unsigned int& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned int& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned int& b,
             const int& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned int& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned int& b,
             const long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned int& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned int& b,
             const short& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned int& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned int& b,
             const char& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned int& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(double& a,
             const long& b,
             const double& c) { a+=b*c; }
  void shift(double& a,
             const long& b,
             const float& c) { a+=b*c; }
  void shift(double& a,
             const long& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const long& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const long& b,
             const int& c) { a+=b*(c+0.); }
  void shift(double& a,
             const long& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(double& a,
             const long& b,
             const long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const long& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const long& b,
             const short& c) { a+=b*(c+0.); }
  void shift(double& a,
             const long& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(double& a,
             const long& b,
             const char& c) { a+=b*(c+0.); }
  void shift(double& a,
             const long& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(double& a,
             const unsigned long& b,
             const double& c) { a+=b*c; }
  void shift(double& a,
             const unsigned long& b,
             const float& c) { a+=b*c; }
  void shift(double& a,
             const unsigned long& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned long& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned long& b,
             const int& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned long& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned long& b,
             const long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned long& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned long& b,
             const short& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned long& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned long& b,
             const char& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned long& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(double& a,
             const short& b,
             const double& c) { a+=b*c; }
  void shift(double& a,
             const short& b,
             const float& c) { a+=b*c; }
  void shift(double& a,
             const short& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const short& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const short& b,
             const int& c) { a+=b*(c+0.); }
  void shift(double& a,
             const short& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(double& a,
             const short& b,
             const long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const short& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const short& b,
             const short& c) { a+=b*(c+0.); }
  void shift(double& a,
             const short& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(double& a,
             const short& b,
             const char& c) { a+=b*(c+0.); }
  void shift(double& a,
             const short& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(double& a,
             const unsigned short& b,
             const double& c) { a+=b*c; }
  void shift(double& a,
             const unsigned short& b,
             const float& c) { a+=b*c; }
  void shift(double& a,
             const unsigned short& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned short& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned short& b,
             const int& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned short& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned short& b,
             const long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned short& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned short& b,
             const short& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned short& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned short& b,
             const char& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned short& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(double& a,
             const char& b,
             const double& c) { a+=b*c; }
  void shift(double& a,
             const char& b,
             const float& c) { a+=b*c; }
  void shift(double& a,
             const char& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const char& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const char& b,
             const int& c) { a+=b*(c+0.); }
  void shift(double& a,
             const char& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(double& a,
             const char& b,
             const long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const char& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const char& b,
             const short& c) { a+=b*(c+0.); }
  void shift(double& a,
             const char& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(double& a,
             const char& b,
             const char& c) { a+=b*(c+0.); }
  void shift(double& a,
             const char& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(double& a,
             const unsigned char& b,
             const double& c) { a+=b*c; }
  void shift(double& a,
             const unsigned char& b,
             const float& c) { a+=b*c; }
  void shift(double& a,
             const unsigned char& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned char& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned char& b,
             const int& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned char& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned char& b,
             const long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned char& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned char& b,
             const short& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned char& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned char& b,
             const char& c) { a+=b*(c+0.); }
  void shift(double& a,
             const unsigned char& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(float& a,
             const float& b,
             const float& c) { a+=b*c; }
  void shift(float& a,
             const float& b,
             const long long& c) { a+=b*c; }
  void shift(float& a,
             const float& b,
             const unsigned long long& c) { a+=b*c; }
  void shift(float& a,
             const float& b,
             const int& c) { a+=b*c; }
  void shift(float& a,
             const float& b,
             const unsigned int& c) { a+=b*c; }
  void shift(float& a,
             const float& b,
             const long& c) { a+=b*c; }
  void shift(float& a,
             const float& b,
             const unsigned long& c) { a+=b*c; }
  void shift(float& a,
             const float& b,
             const short& c) { a+=b*c; }
  void shift(float& a,
             const float& b,
             const unsigned short& c) { a+=b*c; }
  void shift(float& a,
             const float& b,
             const char& c) { a+=b*c; }
  void shift(float& a,
             const float& b,
             const unsigned char& c) { a+=b*c; }

  void shift(float& a,
             const long long& b,
             const float& c) { a+=b*c; }
  void shift(float& a,
             const long long& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const long long& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const long long& b,
             const int& c) { a+=b*(c+0.); }
  void shift(float& a,
             const long long& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(float& a,
             const long long& b,
             const long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const long long& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const long long& b,
             const short& c) { a+=b*(c+0.); }
  void shift(float& a,
             const long long& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(float& a,
             const long long& b,
             const char& c) { a+=b*(c+0.); }
  void shift(float& a,
             const long long& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(float& a,
             const unsigned long long& b,
             const float& c) { a+=b*c; }
  void shift(float& a,
             const unsigned long long& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned long long& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned long long& b,
             const int& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned long long& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned long long& b,
             const long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned long long& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned long long& b,
             const short& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned long long& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned long long& b,
             const char& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned long long& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(float& a,
             const int& b,
             const float& c) { a+=b*c; }
  void shift(float& a,
             const int& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const int& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const int& b,
             const int& c) { a+=b*(c+0.); }
  void shift(float& a,
             const int& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(float& a,
             const int& b,
             const long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const int& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const int& b,
             const short& c) { a+=b*(c+0.); }
  void shift(float& a,
             const int& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(float& a,
             const int& b,
             const char& c) { a+=b*(c+0.); }
  void shift(float& a,
             const int& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(float& a,
             const unsigned int& b,
             const float& c) { a+=b*c; }
  void shift(float& a,
             const unsigned int& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned int& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned int& b,
             const int& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned int& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned int& b,
             const long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned int& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned int& b,
             const short& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned int& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned int& b,
             const char& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned int& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(float& a,
             const long& b,
             const float& c) { a+=b*c; }
  void shift(float& a,
             const long& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const long& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const long& b,
             const int& c) { a+=b*(c+0.); }
  void shift(float& a,
             const long& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(float& a,
             const long& b,
             const long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const long& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const long& b,
             const short& c) { a+=b*(c+0.); }
  void shift(float& a,
             const long& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(float& a,
             const long& b,
             const char& c) { a+=b*(c+0.); }
  void shift(float& a,
             const long& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(float& a,
             const unsigned long& b,
             const float& c) { a+=b*c; }
  void shift(float& a,
             const unsigned long& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned long& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned long& b,
             const int& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned long& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned long& b,
             const long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned long& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned long& b,
             const short& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned long& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned long& b,
             const char& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned long& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(float& a,
             const short& b,
             const float& c) { a+=b*c; }
  void shift(float& a,
             const short& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const short& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const short& b,
             const int& c) { a+=b*(c+0.); }
  void shift(float& a,
             const short& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(float& a,
             const short& b,
             const long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const short& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const short& b,
             const short& c) { a+=b*(c+0.); }
  void shift(float& a,
             const short& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(float& a,
             const short& b,
             const char& c) { a+=b*(c+0.); }
  void shift(float& a,
             const short& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(float& a,
             const unsigned short& b,
             const float& c) { a+=b*c; }
  void shift(float& a,
             const unsigned short& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned short& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned short& b,
             const int& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned short& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned short& b,
             const long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned short& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned short& b,
             const short& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned short& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned short& b,
             const char& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned short& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(float& a,
             const char& b,
             const float& c) { a+=b*c; }
  void shift(float& a,
             const char& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const char& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const char& b,
             const int& c) { a+=b*(c+0.); }
  void shift(float& a,
             const char& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(float& a,
             const char& b,
             const long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const char& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const char& b,
             const short& c) { a+=b*(c+0.); }
  void shift(float& a,
             const char& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(float& a,
             const char& b,
             const char& c) { a+=b*(c+0.); }
  void shift(float& a,
             const char& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(float& a,
             const unsigned char& b,
             const float& c) { a+=b*c; }
  void shift(float& a,
             const unsigned char& b,
             const long long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned char& b,
             const unsigned long long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned char& b,
             const int& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned char& b,
             const unsigned int& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned char& b,
             const long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned char& b,
             const unsigned long& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned char& b,
             const short& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned char& b,
             const unsigned short& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned char& b,
             const char& c) { a+=b*(c+0.); }
  void shift(float& a,
             const unsigned char& b,
             const unsigned char& c) { a+=b*(c+0.); }

  void shift(long long& a,
             const long long& b,
             const long long& c) { a+=b*c; }
  void shift(long long& a,
             const long long& b,
             const int& c) { a+=b*c; }
  void shift(long long& a,
             const long long& b,
             const unsigned int& c) { a+=b*c; }
  void shift(long long& a,
             const long long& b,
             const long& c) { a+=b*c; }
  void shift(long long& a,
             const long long& b,
             const unsigned long& c) { a+=b*c; }
  void shift(long long& a,
             const long long& b,
             const short& c) { a+=b*c; }
  void shift(long long& a,
             const long long& b,
             const unsigned short& c) { a+=b*c; }
  void shift(long long& a,
             const long long& b,
             const char& c) { a+=b*c; }
  void shift(long long& a,
             const long long& b,
             const unsigned char& c) { a+=b*c; }

  void shift(long long& a,
             const int& b,
             const long long& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const int& b,
             const int& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const int& b,
             const unsigned int& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const int& b,
             const long& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const int& b,
             const unsigned long& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const int& b,
             const short& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const int& b,
             const unsigned short& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const int& b,
             const char& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const int& b,
             const unsigned char& c) { a+=static_cast<long long>(b)*c; }

  void shift(long long& a,
             const unsigned int& b,
             const long long& c) { a+=b*c; }
  void shift(long long& a,
             const unsigned int& b,
             const int& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned int& b,
             const unsigned int& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned int& b,
             const long& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned int& b,
             const unsigned long& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned int& b,
             const short& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned int& b,
             const unsigned short& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned int& b,
             const char& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned int& b,
             const unsigned char& c) { a+=static_cast<long long>(b)*c; }

  void shift(long long& a,
             const long& b,
             const long long& c) { a+=b*c; }
  void shift(long long& a,
             const long& b,
             const int& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const long& b,
             const unsigned int& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const long& b,
             const long& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const long& b,
             const unsigned long& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const long& b,
             const short& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const long& b,
             const unsigned short& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const long& b,
             const char& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const long& b,
             const unsigned char& c) { a+=static_cast<long long>(b)*c; }

  void shift(long long& a,
             const unsigned long& b,
             const long long& c) { a+=b*c; }
  void shift(long long& a,
             const unsigned long& b,
             const int& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned long& b,
             const unsigned int& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned long& b,
             const long& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned long& b,
             const unsigned long& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned long& b,
             const short& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned long& b,
             const unsigned short& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned long& b,
             const char& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned long& b,
             const unsigned char& c) { a+=static_cast<long long>(b)*c; }

  void shift(long long& a,
             const short& b,
             const long long& c) { a+=b*c; }
  void shift(long long& a,
             const short& b,
             const int& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const short& b,
             const unsigned int& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const short& b,
             const long& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const short& b,
             const unsigned long& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const short& b,
             const short& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const short& b,
             const unsigned short& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const short& b,
             const char& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const short& b,
             const unsigned char& c) { a+=static_cast<long long>(b)*c; }

  void shift(long long& a,
             const unsigned short& b,
             const long long& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned short& b,
             const int& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned short& b,
             const unsigned int& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned short& b,
             const long& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned short& b,
             const unsigned long& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned short& b,
             const short& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned short& b,
             const unsigned short& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned short& b,
             const char& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned short& b,
             const unsigned char& c) { a+=static_cast<long long>(b)*c; }

  void shift(long long& a,
             const char& b,
             const long long& c) { a+=b*c; }
  void shift(long long& a,
             const char& b,
             const int& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const char& b,
             const unsigned int& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const char& b,
             const long& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const char& b,
             const unsigned long& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const char& b,
             const short& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const char& b,
             const unsigned short& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const char& b,
             const char& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const char& b,
             const unsigned char& c) { a+=static_cast<long long>(b)*c; }

  void shift(long long& a,
             const unsigned char& b,
             const long long& c) { a+=b*c; }
  void shift(long long& a,
             const unsigned char& b,
             const int& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned char& b,
             const unsigned int& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned char& b,
             const long& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned char& b,
             const unsigned long& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned char& b,
             const short& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned char& b,
             const unsigned short& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned char& b,
             const char& c) { a+=static_cast<long long>(b)*c; }
  void shift(long long& a,
             const unsigned char& b,
             const unsigned char& c) { a+=static_cast<long long>(b)*c; }

  void shift(unsigned long long& a,
             const unsigned long long& b,
             const unsigned long long& c) { a+=b*c; }
  void shift(unsigned long long& a,
             const unsigned long long& b,
             const unsigned int& c) { a+=b*c; }
  void shift(unsigned long long& a,
             const unsigned long long& b,
             const unsigned long& c) { a+=b*c; }
  void shift(unsigned long long& a,
             const unsigned long long& b,
             const unsigned short& c) { a+=b*c; }
  void shift(unsigned long long& a,
             const unsigned long long& b,
             const unsigned char& c) { a+=b*c; }

  void shift(unsigned long long& a,
             const unsigned int& b,
             const unsigned long long& c) { a+=b*c; }
  void shift(unsigned long long& a,
             const unsigned int& b,
             const unsigned int& c) { a+=static_cast<unsigned long long>(b)*c; }
  void shift(unsigned long long& a,
             const unsigned int& b,
             const unsigned long& c){ a+=static_cast<unsigned long long>(b)*c; }
  void shift(unsigned long long& a,
             const unsigned int& b,
             const unsigned short& c){a+=static_cast<unsigned long long>(b)*c;}
  void shift(unsigned long long& a,
             const unsigned int& b,
             const unsigned char& c){ a+=static_cast<unsigned long long>(b)*c; }

  void shift(unsigned long long& a,
             const unsigned long& b,
             const unsigned long long& c) { a+=b*c; }
  void shift(unsigned long long& a,
             const unsigned long& b,
             const unsigned int& c) { a+=static_cast<unsigned long long>(b)*c; }
  void shift(unsigned long long& a,
             const unsigned long& b,
             const unsigned long& c){ a+=static_cast<unsigned long long>(b)*c; }
  void shift(unsigned long long& a,
             const unsigned long& b,
             const unsigned short& c){a+=static_cast<unsigned long long>(b)*c;}
  void shift(unsigned long long& a,
             const unsigned long& b,
             const unsigned char& c){ a+=static_cast<unsigned long long>(b)*c; }

  void shift(unsigned long long& a,
             const unsigned short& b,
             const unsigned long long& c) { a+=b*c; }
  void shift(unsigned long long& a,
             const unsigned short& b,
             const unsigned int& c) { a+=static_cast<unsigned long long>(b)*c; }
  void shift(unsigned long long& a,
             const unsigned short& b,
             const unsigned long& c){ a+=static_cast<unsigned long long>(b)*c; }
  void shift(unsigned long long& a,
             const unsigned short& b,
             const unsigned short& c){a+=static_cast<unsigned long long>(b)*c;}
  void shift(unsigned long long& a,
             const unsigned short& b,
             const unsigned char& c){ a+=static_cast<unsigned long long>(b)*c; }

  void shift(unsigned long long& a,
             const unsigned char& b,
             const unsigned long long& c) { a+=b*c; }
  void shift(unsigned long long& a,
             const unsigned char& b,
             const unsigned int& c) { a+=static_cast<unsigned long long>(b)*c; }
  void shift(unsigned long long& a,
             const unsigned char& b,
             const unsigned long& c){ a+=static_cast<unsigned long long>(b)*c; }
  void shift(unsigned long long& a,
             const unsigned char& b,
             const unsigned short& c){a+=static_cast<unsigned long long>(b)*c;}
  void shift(unsigned long long& a,
             const unsigned char& b,
             const unsigned char& c){ a+=static_cast<unsigned long long>(b)*c; }

  void shift(int& a,
             const int& b,
             const int& c) { a+=b*c; }
  void shift(int& a,
             const int& b,
             const long& c) { a+=b*c; }
  void shift(int& a,
             const int& b,
             const short& c) { a+=b*c; }
  void shift(int& a,
             const int& b,
             const unsigned short& c) { a+=b*c; }
  void shift(int& a,
             const int& b,
             const char& c) { a+=b*c; }
  void shift(int& a,
             const int& b,
             const unsigned char& c) { a+=b*c; }

  void shift(int& a,
             const long& b,
             const int& c) { a+=b*c; }
  void shift(int& a,
             const long& b,
             const long& c) { a+=b*c; }
  void shift(int& a,
             const long& b,
             const short& c) { a+=b*c; }
  void shift(int& a,
             const long& b,
             const unsigned short& c) { a+=b*c; }
  void shift(int& a,
             const long& b,
             const char& c) { a+=b*c; }
  void shift(int& a,
             const long& b,
             const unsigned char& c) { a+=b*c; }

  void shift(int& a,
             const short& b,
             const int& c) { a+=b*c; }
  void shift(int& a,
             const short& b,
             const long& c) { a+=b*c; }
  void shift(int& a,
             const short& b,
             const short& c) { a+=static_cast<int>(b)*c; }
  void shift(int& a,
             const short& b,
             const unsigned short& c) { a+=static_cast<int>(b)*c; }
  void shift(int& a,
             const short& b,
             const char& c) { a+=static_cast<int>(b)*c; }
  void shift(int& a,
             const short& b,
             const unsigned char& c) { a+=static_cast<int>(b)*c; }

  void shift(int& a,
             const unsigned short& b,
             const int& c) { a+=b*c; }
  void shift(int& a,
             const unsigned short& b,
             const long& c) { a+=b*c; }
  void shift(int& a,
             const unsigned short& b,
             const short& c) { a+=static_cast<int>(b)*c; }
  void shift(int& a,
             const unsigned short& b,
             const unsigned short& c) { a+=static_cast<int>(b)*c; }
  void shift(int& a,
             const unsigned short& b,
             const char& c) { a+=static_cast<int>(b)*c; }
  void shift(int& a,
             const unsigned short& b,
             const unsigned char& c) { a+=static_cast<int>(b)*c; }

  void shift(int& a,
             const char& b,
             const int& c) { a+=b*c; }
  void shift(int& a,
             const char& b,
             const long& c) { a+=b*c; }
  void shift(int& a,
             const char& b,
             const short& c) { a+=static_cast<int>(b)*c; }
  void shift(int& a,
             const char& b,
             const unsigned short& c) { a+=static_cast<int>(b)*c; }
  void shift(int& a,
             const char& b,
             const char& c) { a+=static_cast<int>(b)*c; }
  void shift(int& a,
             const char& b,
             const unsigned char& c) { a+=static_cast<int>(b)*c; }

  void shift(int& a,
             const unsigned char& b,
             const int& c) { a+=b*c; }
  void shift(int& a,
             const unsigned char& b,
             const long& c) { a+=b*c; }
  void shift(int& a,
             const unsigned char& b,
             const short& c) { a+=static_cast<int>(b)*c; }
  void shift(int& a,
             const unsigned char& b,
             const unsigned short& c) { a+=static_cast<int>(b)*c; }
  void shift(int& a,
             const unsigned char& b,
             const char& c) { a+=static_cast<int>(b)*c; }
  void shift(int& a,
             const unsigned char& b,
             const unsigned char& c) { a+=static_cast<int>(b)*c; }

  void shift(unsigned int& a,
             const unsigned int& b,
             const unsigned int& c) { a+=b*c; }
  void shift(unsigned int& a,
             const unsigned int& b,
             const unsigned long& c) { a+=b*c; }
  void shift(unsigned int& a,
             const unsigned int& b,
             const unsigned short& c) { a+=b*c; }
  void shift(unsigned int& a,
             const unsigned int& b,
             const unsigned char& c) { a+=b*c; }

  void shift(unsigned int& a,
             const unsigned long& b,
             const unsigned int& c) { a+=b*c; }
  void shift(unsigned int& a,
             const unsigned long& b,
             const unsigned long& c) { a+=b*c; }
  void shift(unsigned int& a,
             const unsigned long& b,
             const unsigned short& c) { a+=b*c; }
  void shift(unsigned int& a,
             const unsigned long& b,
             const unsigned char& c) { a+=b*c; }

  void shift(unsigned int& a,
             const unsigned short& b,
             const unsigned int& c) { a+=b*c; }
  void shift(unsigned int& a,
             const unsigned short& b,
             const unsigned long& c) { a+=static_cast<unsigned int>(b)*c; }
  void shift(unsigned int& a,
             const unsigned short& b,
             const unsigned short& c) { a+=static_cast<unsigned int>(b)*c; }
  void shift(unsigned int& a,
             const unsigned short& b,
             const unsigned char& c) { a+=static_cast<unsigned int>(b)*c; }

  void shift(unsigned int& a,
             const unsigned char& b,
             const unsigned int& c) { a+=b*c; }
  void shift(unsigned int& a,
             const unsigned char& b,
             const unsigned long& c){ a+=b*c; }
  void shift(unsigned int& a,
             const unsigned char& b,
             const unsigned short& c) { a+=static_cast<unsigned int>(b)*c; }
  void shift(unsigned int& a,
             const unsigned char& b,
             const unsigned char& c) { a+=static_cast<unsigned int>(b)*c; }

  void shift(long& a,
             const int& b,
             const int& c) { a+=b*c; }
  void shift(long& a,
             const int& b,
             const long& c) { a+=b*c; }
  void shift(long& a,
             const int& b,
             const short& c) { a+=b*c; }
  void shift(long& a,
             const int& b,
             const unsigned short& c) { a+=b*c; }
  void shift(long& a,
             const int& b,
             const char& c) { a+=b*c; }
  void shift(long& a,
             const int& b,
             const unsigned char& c) { a+=b*c; }

  void shift(long& a,
             const long& b,
             const int& c) { a+=b*c; }
  void shift(long& a,
             const long& b,
             const long& c) { a+=b*c; }
  void shift(long& a,
             const long& b,
             const short& c) { a+=b*c; }
  void shift(long& a,
             const long& b,
             const unsigned short& c) { a+=b*c; }
  void shift(long& a,
             const long& b,
             const char& c) { a+=b*c; }
  void shift(long& a,
             const long& b,
             const unsigned char& c) { a+=b*c; }

  void shift(long& a,
             const short& b,
             const int& c) { a+=b*c; }
  void shift(long& a,
             const short& b,
             const long& c) { a+=b*c; }
  void shift(long& a,
             const short& b,
             const short& c) { a+=static_cast<long>(b)*c; }
  void shift(long& a,
             const short& b,
             const unsigned short& c) { a+=static_cast<long>(b)*c; }
  void shift(long& a,
             const short& b,
             const char& c) { a+=static_cast<long>(b)*c; }
  void shift(long& a,
             const short& b,
             const unsigned char& c) { a+=static_cast<long>(b)*c; }

  void shift(long& a,
             const unsigned short& b,
             const int& c) { a+=b*c; }
  void shift(long& a,
             const unsigned short& b,
             const long& c) { a+=b*c; }
  void shift(long& a,
             const unsigned short& b,
             const short& c) { a+=static_cast<long>(b)*c; }
  void shift(long& a,
             const unsigned short& b,
             const unsigned short& c) { a+=static_cast<long>(b)*c; }
  void shift(long& a,
             const unsigned short& b,
             const char& c) { a+=static_cast<long>(b)*c; }
  void shift(long& a,
             const unsigned short& b,
             const unsigned char& c) { a+=static_cast<long>(b)*c; }

  void shift(long& a,
             const char& b,
             const int& c) { a+=b*c; }
  void shift(long& a,
             const char& b,
             const long& c) { a+=b*c; }
  void shift(long& a,
             const char& b,
             const short& c) { a+=static_cast<long>(b)*c; }
  void shift(long& a,
             const char& b,
             const unsigned short& c) { a+=static_cast<long>(b)*c; }
  void shift(long& a,
             const char& b,
             const char& c) { a+=static_cast<long>(b)*c; }
  void shift(long& a,
             const char& b,
             const unsigned char& c) { a+=static_cast<long>(b)*c; }

  void shift(long& a,
             const unsigned char& b,
             const int& c) { a+=b*c; }
  void shift(long& a,
             const unsigned char& b,
             const long& c) { a+=b*c; }
  void shift(long& a,
             const unsigned char& b,
             const short& c) { a+=static_cast<long>(b)*c; }
  void shift(long& a,
             const unsigned char& b,
             const unsigned short& c) { a+=static_cast<long>(b)*c; }
  void shift(long& a,
             const unsigned char& b,
             const char& c) { a+=static_cast<long>(b)*c; }
  void shift(long& a,
             const unsigned char& b,
             const unsigned char& c) { a+=static_cast<long>(b)*c; }

  void shift(unsigned long& a,
             const unsigned int& b,
             const unsigned int& c) { a+=b*c; }
  void shift(unsigned long& a,
             const unsigned int& b,
             const unsigned long& c) { a+=b*c; }
  void shift(unsigned long& a,
             const unsigned int& b,
             const unsigned short& c) { a+=b*c; }
  void shift(unsigned long& a,
             const unsigned int& b,
             const unsigned char& c) { a+=b*c; }

  void shift(unsigned long& a,
             const unsigned long& b,
             const unsigned int& c) { a+=b*c; }
  void shift(unsigned long& a,
             const unsigned long& b,
             const unsigned long& c) { a+=b*c; }
  void shift(unsigned long& a,
             const unsigned long& b,
             const unsigned short& c) { a+=b*c; }
  void shift(unsigned long& a,
             const unsigned long& b,
             const unsigned char& c) { a+=b*c; }

  void shift(unsigned long& a,
             const unsigned short& b,
             const unsigned int& c) { a+=b*c; }
  void shift(unsigned long& a,
             const unsigned short& b,
             const unsigned long& c) { a+=static_cast<unsigned long>(b)*c; }
  void shift(unsigned long& a,
             const unsigned short& b,
             const unsigned short& c) { a+=static_cast<unsigned long>(b)*c; }
  void shift(unsigned long& a,
             const unsigned short& b,
             const unsigned char& c) { a+=static_cast<unsigned long>(b)*c; }

  void shift(unsigned long& a,
             const unsigned char& b,
             const unsigned int& c) { a+=b*c; }
  void shift(unsigned long& a,
             const unsigned char& b,
             const unsigned long& c){ a+=b*c; }
  void shift(unsigned long& a,
             const unsigned char& b,
             const unsigned short& c) { a+=static_cast<unsigned long>(b)*c; }
  void shift(unsigned long& a,
             const unsigned char& b,
             const unsigned char& c) { a+=static_cast<unsigned long>(b)*c; }

  void shift(short& a,
             const short& b,
             const short& c) { a+=b*c; }
  void shift(short& a,
             const short& b,
             const char& c) { a+=b*c; }
  void shift(short& a,
             const short& b,
             const unsigned char& c) { a+=b*c; }

  void shift(short& a,
             const char& b,
             const short& c) { a+=b*c; }
  void shift(short& a,
             const char& b,
             const char& c) { a+=static_cast<short>(b)*c; }
  void shift(short& a,
             const char& b,
             const unsigned char& c) { a+=static_cast<short>(b)*c; }

  void shift(short& a,
             const unsigned char& b,
             const short& c) { a+=b*c; }
  void shift(short& a,
             const unsigned char& b,
             const char& c) { a+=static_cast<short>(b)*c; }
  void shift(short& a,
             const unsigned char& b,
             const unsigned char& c) { a+=static_cast<short>(b)*c; }

  void shift(unsigned short& a,
             const unsigned short& b,
             const unsigned short& c) { a+=b*c; }
  void shift(unsigned short& a,
             const unsigned short& b,
             const unsigned char& c) { a+=b*c; }

  void shift(unsigned short& a,
             const unsigned char& b,
             const unsigned short& c) { a+=b*c; }
  void shift(unsigned short& a,
             const unsigned char& b,
             const unsigned char& c) { a+=static_cast<unsigned short>(b)*c; }

  void shift(char& a,
             const char& b,
             const char& c) { a+=static_cast<short>(b)*c; }

  void shift(unsigned char& a,
             const unsigned char& b,
             const unsigned char& c) { a+=b*c; }

}

#endif

