
#ifndef _Random_Interface_H_
#define _Random_Interface_H_

#include "array/data/interface.h"
#include <ctime>

namespace mysimulator {

  class Random;
  void Clear(Random&);

  class Random {

    public:

      typedef Random    Type;

      Random() {}
      virtual ~Random() { Clear(*this); }

      virtual bool IsValid() const = 0;
      virtual void Allocate() = 0;
      virtual void Init(unsigned int) = 0;
      virtual void Init(const ArrayData<unsigned int>&) = 0;
      virtual double Double() = 0;
      virtual unsigned int UInt() = 0;

      void InitWithTime() { Init(static_cast<unsigned int>(time(0))); }
      void Produce(ArrayData<double>& A) {
        assert(A.IsValid());
        const unsigned int n=A.Size();
        for(unsigned int i=0;i<n;++i) A[i]=Double();
      }
      void Produce(ArrayData<unsigned int>& A) {
        assert(A.IsValid());
        const unsigned int n=A.Size();
        for(unsigned int i=0;i<n;++i) A[i]=UInt();
      }
      template <typename T>
      void Produce(ArrayData<T>& A) {
        assert(A.IsValid());
        const unsigned int n=A.Size();
        for(unsigned int i=0;i<n;++i) Produce(A[i]);
      }

    private:

      Random(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void Clear(Random& R) {}

}

#endif

