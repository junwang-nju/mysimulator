
#ifndef _Array_Base_Interface_H_
#define _Array_Base_Interface_H_

#include "array/data/interface.h"
#include "status/part/interface.h"

namespace mysimulator {

  template <typename T> class ArrayBase;
  template <typename T> void Clear(ArrayBase<T>&);
  template <typename T> void _Swap(ArrayBase<T>&,ArrayBase<T>&);

  template <typename T>
  class ArrayBase : public ArrayData<T> {

    public:

      typedef ArrayBase<T>  Type;
      typedef ArrayData<T>  ParentType;
      friend void Clear<T>(Type&);
      friend void _Swap<T>(Type&,Type&);

      ArrayBase() : ParentType(), _status(NULL), _isPart(false) {}
      ~ArrayBase() { Clear(*this); }

      bool IsValid() const {
        return static_cast<const ParentType*>(this)->IsValid()&&(_status!=NULL);
      }
      void Allocate(unsigned int n) {
        Clear(*this);
        static_cast<ParentType*>(this)->Allocate(n);
        _status=new PartUsedStatus;
        _status->Init();
        _isPart=false;
      }
      void Refer(Type& A, unsigned int b, unsigned int n) {
        assert(A.IsValid());
        Clear(*this);
        static_cast<ParentType*>(this)->Refer(static_cast<ParentType&>(A),b,n);
        _status=A._status;
        _isPart=(A._isPart||(b>0)||(n<A.Size())?true:false);
        if(_isPart) _status->IncPart();
        else        _status->Inc();
      }
      void Refer(Type& A)  { Refer(A,0,A.Size()); }

    protected:

      PartUsedStatus  *_status;
      bool _isPart;

    private:

      ArrayBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(ArrayBase<T>& A) {
    if(A.IsValid()) {
      if(A._isPart) A._status->DecPart();
      else if(A._status->Only())  { delete A._status; A.SetAllocFlag(true); }
      else if(A._status->AllPartUse())
        throw "Need to Free Part Content First!";
      else { A._status->Dec(); A.SetAllocFlag(false); }
      Clear(static_cast<ArrayData<T>&>(A));
      A._status=NULL;
      A._isPart=false;
    }
  }

  template <typename T1, typename T2>
  void _Copy(ArrayBase<T1>& A1, const ArrayBase<T2>& A2) { A1.Copy(A2); }

  template <typename T1, typename T2>
  void _Fill(ArrayBase<T1>& A, const T2& fac) { A.Fill(fac); }

}

#endif

