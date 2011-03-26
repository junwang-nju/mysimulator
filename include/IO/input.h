
#ifndef _InputOutput_Input_Base_H_
#define _InputOutput_Input_Base_H_

#include "IO/base.h"

namespace mysimulator {

  struct InputBase : public IOBase {

    typedef InputBase Type;
    typedef IOBase    ParentType;

    InputBase() : ParentType() {}
    InputBase(const Type&) {
      fprintf(stderr,"Copier of InputBase Disabled!\n");
    }
    Type& operator=(const Type&) {
      fprintf(stderr,"Operator= for InputBase Disabled!\n");
      return *this;
    }
    ~InputBase() { release(); }

    void release() { static_cast<ParentType&>(*this).release(); }

    virtual InputBase& read(bool&)=0;
    virtual InputBase& read(char&)=0;
    virtual InputBase& read(unsigned char&)=0;
    virtual InputBase& read(short&)=0;
    virtual InputBase& read(unsigned short&)=0;
    virtual InputBase& read(int&)=0;
    virtual InputBase& read(unsigned int&)=0;
    virtual InputBase& read(long&)=0;
    virtual InputBase& read(unsigned long&)=0;
    virtual InputBase& read(long long int&)=0;
    virtual InputBase& read(unsigned long long int&)=0;
    virtual InputBase& read(float&)=0;
    virtual InputBase& read(double&)=0;
    virtual InputBase& read(long double&)=0;
    virtual InputBase& read(void*&)=0;
    virtual InputBase& read(char*)=0;

    virtual InputBase& unget(const char&)=0;
    virtual InputBase& unget()=0;

  };

  bool IsValid(const InputBase&) { return true; }
  void copy(InputBase& B, const InputBase& cB) {
    copy(static_cast<IOBase&>(B),static_cast<const IOBase&>(cB));
  }

  InputBase& operator>>(InputBase& O, bool& b) { return O.read(b); }
  InputBase& operator>>(InputBase& O, char& c) { return O.read(c); }
  InputBase& operator>>(InputBase& O, unsigned char& uc) { return O.read(uc); }
  InputBase& operator>>(InputBase& O, short& s) { return O.read(s); }
  InputBase& operator>>(InputBase& O, unsigned short& us){ return O.read(us); }
  InputBase& operator>>(InputBase& O, int& i) { return O.read(i); }
  InputBase& operator>>(InputBase& O, unsigned int& u) { return O.read(u); }
  InputBase& operator>>(InputBase& O, long& l) { return O.read(l); }
  InputBase& operator>>(InputBase& O, unsigned long& ul) { return O.read(ul); }
  InputBase& operator>>(InputBase& O, long long int& ll) { return O.read(ll); }
  InputBase& operator>>(InputBase& O, unsigned long long int& ull) {
    return O.read(ull);
  }
  InputBase& operator>>(InputBase& O, float& f) { return O.read(f); }
  InputBase& operator>>(InputBase& O, double& d) { return O.read(d); }
  InputBase& operator>>(InputBase& O, long double& ld) { return O.read(ld); }
  InputBase& operator>>(InputBase& O, void*& ptr) { return O.read(ptr); }
  InputBase& operator>>(InputBase& O, char* s) { return O.read(s); }

  unsigned int getline(char* buff, const unsigned int nbuff, InputBase& I) {
    unsigned int n=0;
    for(unsigned int i=0;i<nbuff-1;++i) {
      I>>buff[i];
      if(buff[i]=='\n') {
        n=i+1;
        buff[n]='\0';
        break;
      }
    }
    return n;
  }

}

#endif

