
#ifndef _Basic_Expression_Base_H_
#define _Basic_Expression_Base_H_

namespace mysimulator {

  template <typename EA,typename EB>
  class _TwoMemberExpression {

    public:

      typedef _TwoMemberExpression<EA,EB> Type;

    private:

      EA const& _A;
      EB const& _B;

    public:

      _TwoMemberExpression(EA const& A,EB const& B) : _A(A),_B(B) {}
      _TwoMemberExpression(const Type& E) : _A(E._A),_B(E._B) {}
      ~_TwoMemberExpression() {}
      Type& operator=(Type const&) = delete;

      operator bool() const { return ((bool)_A) && ((bool)_B); }
      EA const& first()   const { return _A; }
      EB const& second()  const { return _B; }

  };

}

#endif

