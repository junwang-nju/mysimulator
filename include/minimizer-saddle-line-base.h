
#ifndef _Minimizer_Saddle_Line_Base_H_
#define _Minimizer_Saddle_Line_Base_H_

namespace std {

  template <typename SpaceDataType, typename ParameterType>
  struct SaddleLineMinimizerBase
    : public MinimizerBase<SpaceDataType,ParameterType> {

    typedef SaddleLineMinimizerBase<SpaceDataType,ParameterType>  Type;
    typedef MinimizerBase<SpaceDataType,ParameterType>  ParentType;

    SaddleLineMinimizerBase() : ParentType() {}

  };

}

#endif

