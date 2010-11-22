
#ifndef _Minimal_Step_H_
#define _Minimal_Step_H_

namespace std {

  template <typename IType,typename SpType,typename IdType,typename T>
  double MinimalStep(const LineMinimizerBufferBase<IType,SpType,IdType,T>& B,
                     const SpType& Origin, const SpType& Dirc) {
    assert(IsAvailable(B));
    assert(IsAvailable(Origin));
    assert(IsAvailable(Dirc));
    xxxx
  }

}

#endif
