
#ifndef _Step_Propagator_H_
#define _Step_Propagator_H_

#include "array2d-numeric/interface.h"
#include "array2d/interface.h"
#include "unique/64bit/interface.h"
#include "step-propagator/name.h"

namespace mysimulator {

  template <typename T>
  class StepPropagator {

    public:

      typedef StepPropagator<T>   Type;
      template <typename T1> friend void Clear(StepPropagator<T1>&);

      StepPropagator() : _tag(UnassignedStepPropagator), _range(), _param(),
                         _X(), _G(), _V(), _E() {}
      ~StepPropagator() { Clear(*this); }

      bool IsValid() const {
        return (_tag!=UnassignedStepPropagator)&&_range.IsValid()&&
               _param.IsValid()&&_X.IsValid();
      }

      virtual void Allocate()=0;
      virtual void Init()=0;
      virtual void Clean()=0;
      virtual void Update1()=0;
      virtual void Update2()=0;
      virtual void Update3()=0;
      virtual void Update4()=0;
      virtual void Evolute1()=0;
      virtual void Evolute2()=0;
      virtual void Evolute3()=0;
      virtual void Evolute4()=0;

      void AllocateRange(unsigned int n) { _range.Allocate(n,2); }

      Array<unsigned int>& Range(unsigned int n) {
        assert(_range.IsValid());
        return _range[n];
      }
      const Array<unsigned int>& Range(unsigned int n) const {
        assert(_range.IsValid());
        return _range[n];
      }
      void IntroduceX(Array2DNumeric<T>& X) { _Introduce(_X,X); }
      void IntroduceG(Array2DNumeric<T>& G) { _Introduce(_G,G); }
      void IntroduceV(Array2DNumeric<T>& V) { _Introduce(_V,V); }
      void IntroduceV(ArrayNumeric<T>& V) { _Introduce(_V,V); }

    protected:

      StepPropagatorName        _tag;
      Array2D<unsigned int>     _range;
      Array<Unique64Bit>        _param;
      Array<Array2DNumeric<T> > _X;
      Array<Array2DNumeric<T> > _G;
      Array<Array2DNumeric<T> > _V;
      Array<ArrayNumeric<T> >   _E;

    private:

      template <template<typename> class AType>
      void _Introduce(Array<AType<T> >& A,AType<T>& IA) {
        assert(_range.IsValid());
        assert(IA.IsValid());
        Clear(A);
        A.Allocate(_range.Size());
        for(unsigned int i=0;i<_range.Size();++i)
          A[i].Refer(IA,_range[i][0],_range[i][1]);
      }

      StepPropagator(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagator<T>& P) {
    Clear(P._E);
    Clear(P._V);
    Clear(P._G);
    Clear(P._X);
    Clear(P._param);
    Clear(P._range);
    P._tag=UnassignedStepPropagator;
  }

}

#endif

