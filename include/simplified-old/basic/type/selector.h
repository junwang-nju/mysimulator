
#ifndef _Basic_Type_Selector_H_
#define _Basic_Type_Selector_H_

namespace mysimulator {

  template <typename T,bool FG>
  class __selectorA {
    static_assert(FG==false,"Type T is not in the expected group!\n");
  };

  template <typename T> class __selectorA<T,true>  { public: typedef T Type; };

  template <typename T,template<typename> class _FG>
  class __mono_selector {
    public: typedef typename __selectorA<T,_FG<T>::FG>::Type   Type;
  };

  template <typename T1,typename T2,unsigned int FG>
  class __selectorB {
    static_assert(FG==0,"No operation permitted for Type T1 and T2!\n");
  };

  template <typename T1,typename T2>
  class __selectorB<T1,T2,1> { public: typedef T1 Type; };
  template <typename T1,typename T2>
  class __selectorB<T1,T2,2> { public: typedef T2 Type; };

  template <typename T1,typename T2,template<typename,typename> class _FG>
  class __dual_selector {
    public: typedef typename __selectorB<T1,T2,_FG<T1,T2>::FG>::Type  Type;
  };

}

#endif

