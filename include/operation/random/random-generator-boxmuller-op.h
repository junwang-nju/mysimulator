
#ifndef _Random_Generator_BoxMuller_Operation_H_
#define _Random_Generator_BoxMuller_Operation_H_

#include "data/random/random-generator-boxmuller.h"
#include "operation/random/random-generator-mt-standard-op.h"
#include "operation/random/random-generator-mt-sfmt-op.h"
#include "operation/random/random-generator-mt-dsfmt-op.h"

namespace std {

  template <typename UniformRNG>
  void init(BoxMuller<UniformRNG>& G, const unsigned int seed) {
    assert(IsAvailable(G));
    init(*(G.urng),seed);
    *(G.isSecond)=false;
  }

  template <typename T>
  const T& rand(BoxMuller<MT_Standard>& G) {
    Error("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(BoxMuller<SFMT<607> >& G) {
    Error("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(BoxMuller<SFMT<1279> >& G) {
    Error("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(BoxMuller<SFMT<11213> >& G) {
    Error("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(BoxMuller<SFMT<19937> >& G) {
    Error("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(BoxMuller<SFMT<132049> >& G) {
    Error("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(BoxMuller<SFMT<216091> >& G) {
    Error("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(BoxMuller<SFMT<2281> >& G) {
    Error("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(BoxMuller<SFMT<4253> >& G) {
    Error("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(BoxMuller<SFMT<44497> >& G) {
    Error("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(BoxMuller<SFMT<86243> >& G) {
    Error("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(BoxMuller<dSFMT<521> >& G) {
    Error("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(BoxMuller<dSFMT<1279> >& G) {
    Error("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(BoxMuller<dSFMT<2203> >& G) {
    Error("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(BoxMuller<dSFMT<4253> >& G) {
    Error("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(BoxMuller<dSFMT<11213> >& G) {
    Error("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(BoxMuller<dSFMT<19937> >& G) {
    Error("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(BoxMuller<dSFMT<44497> >& G) {
    Error("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(BoxMuller<dSFMT<86243> >& G) {
    Error("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(BoxMuller<dSFMT<132049> >& G) {
    Error("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(BoxMuller<dSFMT<216091> >& G) {
    Error("Prohibit unknown type");
    return static_cast<T>(0);
  }

  template <typename UniformRNG>
  const double& drand(BoxMuller<UniformRNG>& G) {
    if(*(G.isSecond)) G.output=G[1]*G[2];
    else {
      do {
        G[0]=rand<double>(*(G.urng)); G[0]+=G[0]; G[0]-=1.;
        G[1]=rand<double>(*(G.urng)); G[1]+=G[1]; G[1]-=1.;
        G[2]=G[0]*G[0]+G[1]*G[1];
      } while((G[2]>1.)||(G[2]==0.));
      G[2]=sqroot(-2.0*log(G[2])/G[2]);
      G.output=G[0]*G[2];
    }
    *(G.isSecond)=!(*(G.isSecond));
    return G.output;
  }

  template <>
  const double& rand<double>(BoxMuller<MT_Standard>& G) { return drand(G); }
  template <>
  const double& rand<double>(BoxMuller<SFMT<607> >& G) { return drand(G); }
  template <>
  const double& rand<double>(BoxMuller<SFMT<1279> >& G) { return drand(G); }
  template <>
  const double& rand<double>(BoxMuller<SFMT<11213> >& G) { return drand(G); }
  template <>
  const double& rand<double>(BoxMuller<SFMT<19937> >& G) { return drand(G); }
  template <>
  const double& rand<double>(BoxMuller<SFMT<132049> >& G) { return drand(G); }
  template <>
  const double& rand<double>(BoxMuller<SFMT<216091> >& G) { return drand(G); }
  template <>
  const double& rand<double>(BoxMuller<SFMT<2281> >& G) { return drand(G); }
  template <>
  const double& rand<double>(BoxMuller<SFMT<4253> >& G) { return drand(G); }
  template <>
  const double& rand<double>(BoxMuller<SFMT<44497> >& G) { return drand(G); }
  template <>
  const double& rand<double>(BoxMuller<SFMT<86243> >& G) { return drand(G); }
  template <>
  const double& rand<double>(BoxMuller<dSFMT<521> >& G) { return drand(G); }
  template <>
  const double& rand<double>(BoxMuller<dSFMT<1279> >& G) { return drand(G); }
  template <>
  const double& rand<double>(BoxMuller<dSFMT<2203> >& G) { return drand(G); }
  template <>
  const double& rand<double>(BoxMuller<dSFMT<4253> >& G) { return drand(G); }
  template <>
  const double& rand<double>(BoxMuller<dSFMT<11213> >& G) { return drand(G); }
  template <>
  const double& rand<double>(BoxMuller<dSFMT<19937> >& G) { return drand(G); }
  template <>
  const double& rand<double>(BoxMuller<dSFMT<44497> >& G) { return drand(G); }
  template <>
  const double& rand<double>(BoxMuller<dSFMT<86243> >& G) { return drand(G); }
  template <>
  const double& rand<double>(BoxMuller<dSFMT<132049> >& G) { return drand(G); }
  template <>
  const double& rand<double>(BoxMuller<dSFMT<216091> >& G) { return drand(G); }

}

#endif

