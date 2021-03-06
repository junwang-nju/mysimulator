
#ifndef _Array_Interface_H_
#define _Array_Interface_H_

#include "array/data/interface.h"
#include "status/part/interface.h"

namespace mysimulator {

  template <typename T> class Array;
  template <typename T> void Clear(Array<T>&);
  template <typename T> void _Swap(Array<T>&,Array<T>&);

  template <typename,template<typename> class> class Array2DBase;

  template <typename T>
  class Array: public ArrayData<T> {

    public:

      typedef Array<T>  Type;
      typedef ArrayData<T>  ParentType;
      friend void Clear<T>(Array<T>&);
      friend void _Swap<T>(Array<T>&,Array<T>&);
      template <typename T1, template <typename> class AF>
      friend class Array2DBase;

      Array() : ParentType(), _status(NULL), _isPart(false) {}
      virtual ~Array() { Clear(*this); }

      bool IsValid() const {
        return ParentType::IsValid()&&(_status!=NULL);
      }
      virtual void Allocate(unsigned int n) {
        Clear(*this);
        ParentType::Allocate(n);
        _status=new PartUsedStatus;
        _status->Init();
        _isPart=false;
      }
      void Refer(Type& A, unsigned int b, unsigned int n) {
        assert(A.IsValid());
        Clear(*this);
        ParentType::Refer(static_cast<ParentType&>(A),b,n);
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

      Array(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(Array<T>& A) {
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

  template <typename T>
  bool IsSame(const Array<T>& A, const Array<T>& B) {
    typedef typename Array<T>::ParentType PType;
    return IsSame(static_cast<const PType&>(A),static_cast<const PType&>(B));
  }

  template <typename T1, typename T2>
  void _Copy(Array<T1>& A1, const Array<T2>& A2) { A1.Copy(A2); }

  template <typename T1, typename T2>
  void _Fill(Array<T1>& A, const T2& fac) { A.Fill(fac); }

  template <typename T>
  void _Imprint(Array<T>& A, const Array<T>& B) { A.Imprint(B); }

  template <typename T>
  void _Swap(Array<T>& A, Array<T>& B) {
    typedef ArrayData<T>  DType;
    _Swap(static_cast<DType&>(A),static_cast<DType&>(B));
    _SwapContent(A._status,B._status);
    _SwapContent(A._isPart,B._isPart);
  }

  template <typename T>
  void _SwapContent(Array<T>& A, Array<T>& B) {
    _SwapContent(static_cast<ArrayData<T>&>(A),static_cast<ArrayData<T>&>(B));
  }

}

#endif

