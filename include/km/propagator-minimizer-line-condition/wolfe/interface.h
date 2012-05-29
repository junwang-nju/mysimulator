
#ifndef _Propagator_Minimizer_Line_Condition_Wolfe_Interface_H_
#define _Propagator_Minimizer_Line_Condition_Wolfe_Interface_H_

#include "propagator-minimizer-line-condition/armijo/interface.h"

namespace mysimulator {

  template <typename T>
  class LineMinimizerConditionWolfe : public LineMinimizerConditionArmijo<T> {

    public:

      typedef LineMinimizerConditionWolfe<T>    Type;
      typedef LineMinimizerConditionArmijo<T>   ParentType;

      LineMinimizerConditionWolfe() : ParentType() {}
      ~LineMinimizerConditionWolfe() { Clear(*this); }

      virtual void Allocate() { _tag=Wolfe; }
      virtual bool Check(T ry,T rp,T my,T dp,T cp,T step) {
        return ParentType::Check(ry,rp,my,dp,cp,step)&&(rp>=cp);
      }

    private:

      LineMinimizerConditionWolfe(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Allocate(LineMinimizerConditionWolfe<T>& C) {
    typedef typename LineMinimizerConditionWolfe<T>::ParentType   PType;
    Clear(static_cast<PType&>(C));
  }

}

#endif

