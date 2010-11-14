
#ifndef _Random_Generator_BoxMuller_Operation_H_
#define _Random_Generator_BoxMuller_Operation_H_

#include "data/random/random-generator-boxmuller.h"
#include <cmath>

namespace std {

  template <typename UniformRNG>
  void init(BoxMuller<UniformRNG>& G, const unsigned int seed) {
    assert(IsAvailable(G));
    init(*(G.urng),seed);
    *(G.isSecond)=false;
  }

  template <typename T, typename UniformRNG>
  const T& rand(BoxMuller<UniformRNG>& G) {
    myError("Prohibit unknown type");
    return static_cast<T>(0);
  }

}

#include "operation/random/random-generator-mt-standard-op.h"
#include "operation/random/random-generator-mt-sfmt-op.h"
#include "operation/random/random-generator-mt-dsfmt-op.h"

namespace std {

  template <typename UniformRNG>
  const double& drand(BoxMuller<UniformRNG>& G) {
    if(*(G.isSecond)) G.output=G[1]*G[2];
    else {
      do {
        G[0]=rand<double>(*(G.urng)); G[0]+=G[0]; G[0]-=1.;
        G[1]=rand<double>(*(G.urng)); G[1]+=G[1]; G[1]-=1.;
        G[2]=G[0]*G[0]+G[1]*G[1];
      } while((G[2]>1.)||(G[2]==0.));
      G[2]=sqrt(-2.0*log(G[2])/G[2]);
      G.output=G[0]*G[2];
    }
    *(G.isSecond)=!(*(G.isSecond));
    return G.output;
  }

  template <>
  const double& rand<double,MT_Standard>(BoxMuller<MT_Standard>& G) {
    return drand(G);
  }
  template <>
  const double& rand<double,SFMT<607> >(BoxMuller<SFMT<607> >& G) {
    return drand(G);
  }
  template <>
  const double& rand<double,SFMT<1279> >(BoxMuller<SFMT<1279> >& G) {
    return drand(G);
  }
  template <>
  const double& rand<double,SFMT<11213> >(BoxMuller<SFMT<11213> >& G) {
    return drand(G);
  }
  template <>
  const double& rand<double,SFMT<19937> >(BoxMuller<SFMT<19937> >& G) {
    return drand(G);
  }
  template <>
  const double& rand<double,SFMT<132049> >(BoxMuller<SFMT<132049> >& G) {
    return drand(G);
  }
  template <>
  const double& rand<double,SFMT<216091> >(BoxMuller<SFMT<216091> >& G) {
    return drand(G);
  }
  template <>
  const double& rand<double,SFMT<2281> >(BoxMuller<SFMT<2281> >& G) {
    return drand(G);
  }
  template <>
  const double& rand<double,SFMT<4253> >(BoxMuller<SFMT<4253> >& G) {
    return drand(G);
  }
  template <>
  const double& rand<double,SFMT<44497> >(BoxMuller<SFMT<44497> >& G) {
    return drand(G);
  }
  template <>
  const double& rand<double,SFMT<86243> >(BoxMuller<SFMT<86243> >& G) {
    return drand(G);
  }
  template <>
  const double& rand<double,dSFMT<521> >(BoxMuller<dSFMT<521> >& G) {
    return drand(G);
  }
  template <>
  const double& rand<double,dSFMT<1279> >(BoxMuller<dSFMT<1279> >& G) {
    return drand(G);
  }
  template <>
  const double& rand<double,dSFMT<2203> >(BoxMuller<dSFMT<2203> >& G) {
    return drand(G);
  }
  template <>
  const double& rand<double,dSFMT<4253> >(BoxMuller<dSFMT<4253> >& G) {
    return drand(G);
  }
  template <>
  const double& rand<double,dSFMT<11213> >(BoxMuller<dSFMT<11213> >& G) {
    return drand(G);
  }
  template <>
  const double& rand<double,dSFMT<19937> >(BoxMuller<dSFMT<19937> >& G) {
    return drand(G);
  }
  template <>
  const double& rand<double,dSFMT<44497> >(BoxMuller<dSFMT<44497> >& G) {
    return drand(G);
  }
  template <>
  const double& rand<double,dSFMT<86243> >(BoxMuller<dSFMT<86243> >& G) {
    return drand(G);
  }
  template <>
  const double& rand<double,dSFMT<132049> >(BoxMuller<dSFMT<132049> >& G) {
    return drand(G);
  }
  template <>
  const double& rand<double,dSFMT<216091> >(BoxMuller<dSFMT<216091> >& G) {
    return drand(G);
  }

}

#endif

