
#ifndef _Propagator_Minimizer_Line_Interface_H_
#define _Propagator_Minimizer_Line_Interface_H_

#include "propagator/minimizer/base/interface.h"
#include "propagator/minimizer/line/parameter-name.h"
#include "propagator-minimizer-line-condition/interface.h"

namespace mysimulator {

  template <typename T, typename GT>
  class PropagatorLineMinimizer : public PropagatorBaseMinimizer<T,GT> {

    public:

      typedef PropagatorLineMinimizer<T,GT>     Type;
      typedef PropagatorBaseMinimizer<T,GT>   ParentType;
      template <typename T1,typename GT1>
      friend void Clear(PropagatorLineMinimizer<T1,GT1>&);

      PropagatorLineMinimizer() : ParentType(), _backupX(), _Condition(NULL) {}
      virtual ~PropagatorLineMinimizer() { Clear(*this); }

      virtual bool IsValid() const { 
        return ParentType::IsValid()&&_backupX.IsValid();
      }

      virtual void IntroduceSystem(System<T,GT>& S) {
        ParentType::IntroduceSystem(S);
        _backupX.Imprint(S.Location());
      }
      virtual void DetachSystem() {
        ParentType::DetachSystem();
        Release(_backupX);
      }

    protected:

      Array2DNumeric<T> _backupX;
      LineMinimizerCondition<T>* _Condition;

      void _SetCondition(const LineMinimizerConditionName CN) {
        assert(this->_param.IsValid());
        Introduce(_Condition,CN);
        this->_param[LineMin_ConditionTag]=CN;
      }

    private:

      PropagatorLineMinimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T, typename GT>
  void Clear(PropagatorLineMinimizer<T,GT>& P) {
    if(P._Condition!=NULL) { delete P._Condition; P._Condition=NULL; }
    Clear(P._backupX);
    typedef typename PropagatorLineMinimizer<T,GT>::ParentType  PType;
    Clear(static_cast<PType&>(P));
  }

}

#endif

