
#ifndef _Random_Base_Interface_H_
#define _Random_Base_Interface_H_

#include <ctime>

namespace mysimulator {

  struct RandomBase {

    public:

      typedef RandomBase    Type;

      RandomBase() {}

      virtual void Init(unsigned int) = 0;
      virtual const double Double() = 0;
      virtual const unsigned int UInt() = 0;

      void InitWithTime() { Init(static_cast<unsigned int>(time(0))); }

    private:

      RandomBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

