
#ifndef _Array_2D_Expression_H_
#define _Array_2D_Expression_H_

namespace mysimulator {

  template <typename E,typename ET>
  class Array2DExpression {

    public:

      typedef unsigned int size_type;

      operator bool() const { return (bool)((E const&)(*this)); }
      size_type size() const { return ((E const&)(*this)).size(); }
      ET operator()(size_type i,size_type j) const {
        return ((E const&)(*this))[i][j];
      }
      operator E&() const { return (E&)(*this); }
      operator E const&() const { return (E const&)(*this); }

  };

}

#endif

