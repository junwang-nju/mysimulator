
#ifndef _Basic_Expression_Base_H_
#define _Basic_Expression_Base_H_

#include "basic/expression/name.h"

namespace mysimulator {

  template <typename EA,typename EB, ExpressionOperationName EN>
  class _TwoMemberExpression {

    public:

      typedef _TwoMemberExpression<EA,EB,EN>  Type;

      static const ExpressionOperationName OpName;

    private:

      EA const& _A;
      EB const& _B;

    public:

      _TwoMemberExpression(EA const& A,EB const& B) : _A(A), _B(B) {}
      _TwoMemberExpression(const Type& E) : _A(E._A), _B(E._B) {}
      ~_TwoMemberExpression() {}

      Type& operator=(const Type&) = delete;

      operator bool() const { return (bool)_A && (bool)_B; }
      EA const& first() const { return _A; }
      EB const& second() const { return _B; }

  };

  template <typename EA,typename EB, ExpressionOperationName EN>
  const ExpressionOperationName _TwoMemberExpression<EA,EB,EN>::OpName = EN;

}

#endif

