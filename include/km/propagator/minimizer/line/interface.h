
#ifndef _Propagator_Minimizer_Line_Interface_H_
#define _Propagator_Minimizer_Line_Interface_H_

#include "propagator/minimizer/interface.h"

namespace mysimulator {

  template <typename T, typename GT>
  class PropagatorLineMinimizer : public PropagatorMinimizer<T,GT> {

    public:

      typedef PropagatorLineMinimizer<T,GT>     Type;
      typedef PropagatorMinimizer<T,GT>   ParentType;
      template <typename T1,typename GT1>
      friend void Clear(PropagatorLineMinimizer<T1,GT1>&);

      PropagatorLineMinimizer() : ParentType(), _backupX() {}
      virtual ~PropagatorLineMinimizer() { Clear(*this); }

      virtual bool IsValid() const { 
        return ParentType::IsValid()&&_backupX.IsValid();
      }

      virtual void IntroduceSystem(System<T,GT>& S) {
        ParentType::IntroduceSystem(S);
        _backupX.Imprint(S.Location());
      }

    protected:

      Array2DNumeric<T> _backupX;

    private:

      PropagatorLineMinimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, typename GT>
  void Clear(PropagatorLineMinimizer<T,GT>& P) {
    Clear(P._backupX);
    typedef typename PropagatorLineMinimizer<T,GT>::ParentType  PType;
    Clear(static_cast<PType&>(P));
  }

}

#endif

