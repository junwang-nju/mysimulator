
#ifndef _InputOutput_Input_Base_H_
#define _InputOutput_Input_Base_H_

#include "io/base/interface.h"
#include "io/special-char.h"

namespace mysimulator {

  struct InputBase : public IOBase {

    public:

      typedef InputBase       Type;
      typedef IOBase          ParentType;

      InputBase() : ParentType() {}
      ~InputBase() { clearData(); }

      void clearData() { static_cast<ParentType*>(this)->clearData(); }
      bool isvalid() const {
        return static_cast<const ParentType* const&>(this)->isvalid();
      }

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
      virtual InputBase& read(char* const&)=0;

      virtual InputBase& unget(const char&)=0;
      virtual InputBase& unget()=0;

      virtual InputBase& getline(char* buff) {
        int i=-1;
        while(1) {
          read(buff[++i]);
          if(buff[i]==CharLineEnd)  { buff[i]='\0'; break; }
          if(buff[i+1]==CharEOF)    { buff[i+1]='\0'; break; }
        }
        return *this;
      } // may overwrite CharEOF

    private:

      InputBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  bool IsValid(const InputBase& I) { return I.isvalid(); }
  void release(InputBase& I) { I.clearData(); }

}

#define _INPUT(type) \
  InputBase& operator>>(InputBase& I, type& val) { return I.read(val); }

namespace mysimulator {

  _INPUT(bool)
  _INPUT(char)
  _INPUT(unsigned char)
  _INPUT(short)
  _INPUT(unsigned short)
  _INPUT(long)
  _INPUT(unsigned long)
  _INPUT(int)
  _INPUT(unsigned int)
  _INPUT(long long)
  _INPUT(unsigned long long)
  _INPUT(float)
  _INPUT(double)
  _INPUT(long double)
  _INPUT(void*)
  _INPUT(char* const)

}

#undef _INPUT

#endif

