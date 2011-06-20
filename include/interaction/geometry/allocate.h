
#ifndef _Interaction_Geometry_Allocate_H_
#define _Interaction_Geometry_Allocate_H_

#include "interaction/geometry/interface.h"

namespace mysimulator {

  template <template<typename>class DBuffer,typename GeomType,typename T>
  void allocate(InteractionGeometry<DBuffer,GeomType,T>& G,
                const unsigned int nunit, const unsigned int dim) {
    release(G);
    allocate(G.DB,dim,nunit);
    allocate(G.Geo,dim);
  }

  template <template<typename>class DBuffer,typename GeomType,typename T>
  void imprint(InteractionGeometry<DBuffer,GeomType,T>& G,
               const InteractionGeometry<DBuffer,GeomType,T>& cG) {
    allocate(G,cG.NumUnit(),G.Dimension());
  }

}

#endif

