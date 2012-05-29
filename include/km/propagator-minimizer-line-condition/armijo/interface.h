
#ifndef _Propagator_Minimizer_Line_Condition_Armijo_Interface_H_
#define _Propagator_Minimizer_Line_Condition_Armijo_Interface_H_

#include "propagator-minimizer-line-condition/interface.h"

namespace mysimulator {

  template <typename T>
  class LineMinimizerConditionArmijo : public LineMinimizerCondition<T> {

    public:

      typedef LineMinimizerConditionArmijo<T>   Type;
      typedef LineMinimizerCondition<T>   ParentType;

      LineMinimizerConditionArmijo() : ParentType() {}
      ~LineMinimizerConditionArmijo() { Clear(*this); }

      virtual void Allocate() { this->_tag=Armijo; }
      virtual bool Check(T ry,T,T my,T dp,T,T step) { return ry<=my+step*dp; }

    private:

      LineMinimizerConditionArmijo(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(LineMinimizerConditionArmijo<T>& C) {
    typedef typename LineMinimizerConditionArmijo<T>::ParentType PType;
    Clear(static_cast<PType&>(C));
  }

}

#endif

