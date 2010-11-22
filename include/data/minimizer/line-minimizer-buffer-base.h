
#ifndef _Line_Minimizer_Buffer_Base_H_
#define _Line_Minimizer_Buffer_Base_H_

namespace std {

  template <typename InteractionType,typename SpaceType,typedef IdxType,
            typename T>
  struct LineMinimizerBufferBase
    : public MinimizerBufferBase<InteractionType,SpaceDataType,IdxType,T> {
    typedef LineMinimizerBufferBase<InteractionType,SpaceDataType,IdxType,T>
            Type;
    typedef MinimizerBufferBase<InteractionType,SpaceType,IdxType,T>
            ParentType;

    SpaceType RunX;
    SpaceType RunG;
  };

}

#endif
