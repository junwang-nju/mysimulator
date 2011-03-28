
#ifndef _Intrinsic_Type_Exchange_H_
#define _Intrinsic_Type_Exchange_H_

namespace mysimulator {

  void exchange(long double& a, long double& b) {
    long double c;
    c=a; a=b;  b=c;
  }
  void exchange(double& a, double& b) { double c=a; a=b;  b=c; }
  void exchange(float& a, float& b) { float c=a; a=b;  b=c; }
  void exchange(long long& a, long long& b) { long long c=a; a=b;  b=c; }
  void exchange(unsigned long& a, unsigned long long& b) {
    unsigned long long c;
    c=a; a=b;  b=c;
  }
  void exchange(int& a, int& b) { int c=a; a=b;  b=c; }
  void exchange(unsigned int& a, unsigned int& b) {
    unsigned int c;
    c=a; a=b;  b=c;
  }
  void exchange(long& a, long& b) { long c=a; a=b;  b=c; }
  void exchange(unsigned long& a, unsigned long& b) {
    unsigned long c;
    c=a; a=b;  b=c;
  }
  void exchange(short& a, short& b) { short c=a; a=b;  b=c; }
  void exchange(unsigned short& a, unsigned short& b) {
    unsigned short c;
    c=a; a=b;  b=c;
  }
  void exchange(char& a, char& b) { char c=a; a=b;  b=c; }
  void exchange(unsigned char& a, unsigned char& b) {
    unsigned char c;
    c=a; a=b;  b=c;
  }
  void exchange(bool& a, bool& b) { bool c=a; a=b;  b=c; }
  void exchange(void*& a, void*& b) { void* c=a; a=b;  b=c; }

}

#endif

