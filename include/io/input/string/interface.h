
#ifndef _InputOutput_Input_String_Interface_H_
#define _InputOutput_Input_String_Interface_H_

#include "io/input/interface.h"
#include "vector/allocate.h"
#include "io/input/string/property-name.h"

namespace mysimulator {

  struct StringInput : public InputBase {

    typedef StringInput   Type;
    typedef InputBase     ParentType;

    Vector<char> buffer;
    Vector<unsigned int> property;

    StringInput() : ParentType(), buffer(), property() {}
    StringInput(const Type&) { Error("Copier of StringInput Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for StringInput Disabled!");
      return *this;
    }
    StringInput(const unsigned int n) : InputBase(), buffer(n), property() {
      _init();
    }
    ~StringInput() { clearData(); }

    void clearData() {
      release(buffer);
      release(property);
      release(static_cast<InputBase&>(*this));
    }
    void _init() {
      buffer[buffer.size-1]='\0';
      allocate(I.property,StringInputNumberProperty);
      property[StringLocation]=0;
      property[StringCapacity]=buffer.size-1;
    }
    template <typename T>
    void _read_part(char* inf, unsigned int len, const char* pat, T& value) {
      char nowc=inf[len];
      inf[len]='\0';
      sscanf(inf,pat,&value);
      inf[len]=nowc;
    }
    template <typename T>
    void _read(const char* pat, T& value) {
      assert(IsValid(buffer)&&IsValid(property));
      char* inf=buffer.data+property[StringLocation];
      unsigned int n=0;
      unsigned int sc=property[StringCapacity];
      while(isspace(inf[n])&&(n<=sc)) ++n;
      property[StringLocation]+=n;
      property[StringCapacity]-=n;
      inf=buffer.data+property[StringLocation];
      sc=property[StringCapacity];
      if(sc>0) {
        n=1;
        _read_part(inf,n,pat,value);
        ++n;
        while(n<=sc) {
          T tmvalue;
          _read_part(inf,n,pat,tmvalue);
          if(tmvalue==value)  break;
          value=tmvalue;
          ++n;
        }
        --n;
        property[StringLocation]+=n;
        property[StringCapacity]-=n;
      } else {
        Warn("Buffer Exhausted in StringInput!");
        SetState(FailBit);
      }
      return *this;
    }
    Type& read(char& c) { return _read("%c",c); }
    Type& read(unsigned char& uc) { return _read("%c",uc); }
    Type& read(bool& b) {
      char c;
      _read("%c",c);
      b=(c=='0'?false:true);
      return *this;
    }
    Type& read(short& s) { return _read("%hd",s); }

  };

  void release(StringInput& I) { I.clearData(); }

}

#endif

