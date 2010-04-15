
#ifndef _Interaction_Dihedral_Periodic_H_
#define _Interaction_Dihedral_Periodic_H_

#include "interaction-dihedral-base.h"
#include "functional-dihedral-periodic.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void EFunc_Dihedral_Periodic(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      VectorBase<refVector<double> >& tmVec,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      double& Energy) {
    EFunc_Dihedral_Base(Coor,Idx,Param,tmVec,DEval,Geo,Energy,
                        FuncDihedralPeriodic);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void GFunc_Dihedral_Periodic(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      VectorBase<refVector<double> >& tmVec,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      VectorBase<refVector<double> >& Grad) {
    GFunc_Dihedral_Base(Coor,Idx,Param,tmVec,DEval,Geo,Grad,
                        DiffDihedralPeriodic);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void BFunc_Dihedral_Periodic(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      VectorBase<refVector<double> >& tmVec,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      double& Energy, VectorBase<refVector<double> >& Grad) {
    BFunc_Dihedral_Base(Coor,Idx,Param,tmVec,DEval,Geo,Energy,Grad,
                        BothDihedralPeriodic);
  }

}

#endif
