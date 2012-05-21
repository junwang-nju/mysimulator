
#ifndef _Status_Used_Interface_H_
#define _Status_Used_Interface_H_

namespace mysimulator {

  class UsedStatus {

    public:

      typedef UsedStatus  Type;
      friend void Clear(Type&);

      UsedStatus() : _count(0) {}
      ~UsedStatus() { Clear(*this); }

      bool IsValid() const { return _count>0; }
      bool Only() const { return _count==1; }
      void Init() { _count=1; }
      void Inc() { ++_count; }
      void Dec() { --_count; }

    protected:

      unsigned int _count;

    private:

      UsedStatus(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void Clear(UsedStatus& S) { S._count=0; }

}

#endif

