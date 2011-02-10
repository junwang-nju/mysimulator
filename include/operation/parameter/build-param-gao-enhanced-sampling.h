
#ifndef _Build_Parameter_Gao_Enhanced_Sampling_H_
#define _Build_Parameter_Gao_Enhanced_Sampling_H_

#include "data/name/gao-enhanced-sampling.h"
#include "data/basic/unique-parameter.h"
#include <cmath>

namespace std {
  
  template <typename T>
  void BuildParameterGaoEnhancedSampling(UniqueParameter* prm) {
    Vector<T>& density=*reinterpret_cast<Vector<T>*>(prm[DensitySet].ptr);
    Vector<T>& temp=*reinterpret_cast<Vector<T>*>(prm[TemperatureSet].ptr);
    Vector<T>& lnden=*reinterpret_cast<Vector<T>*>(prm[LnDensitySet].ptr);
    Vector<T>& beta=*reinterpret_cast<Vector<T>*>(prm[BetaSet].ptr);
    Vector<T>& lnbd=*reinterpret_cast<Vector<T>*>(prm[LnBetaDensitySet].ptr);
    assert(density.size==temp.size); 
    assert(density.size==lnden.size); 
    assert(density.size==beta.size); 
    assert(density.size==lnbd.size);
    unsigned int n=density.size;
    for(unsigned int i=0;i<n;++i) {
      lnden[i]=log(density[i]);
      beta[i]=1./temp[i];
      lnbd[i]=log(beta[i]*density[i]);
    }
    copy(prm[RunBeta],1./prm[RunTemperature].value<T>());
  }

}

#include "data/basic/vector.h"

namespace std {
  
  template <typename T>
  void BuildParameterGaoEnhancedSampling(Vector<UniqueParameter>& prm) {
    assert(prm.size>=GaoEnhancedSamplingNumberParameter);
    BuildParameterGaoEnhancedSampling<T>(prm.data);
  }

}

#endif
