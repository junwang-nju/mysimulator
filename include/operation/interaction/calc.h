
#ifndef _Interaction_Calculate_H_
#define _Interaction_Calculate_H_

#include "data/interaction/simple.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      SimpleInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const unsigned int* idx, T& Energy){
    F.EFunc(X,idx,F.prm.data,F.B,F.Geo,Energy,
            F.tmvec.structure,F.NumMerUnit());
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      SimpleInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const unsigned int* idx, Vector<T>* Gradient) {
    F.GFunc(X,idx,F.prm.data,F.B,F.Geo,Gradient,
            F.tmvec.structure,F.NumMerUnit());
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      SimpleInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const unsigned int* idx,
      T& Energy, Vector<T>* Gradient){
    F.BFunc(X,idx,F.prm.data,F.B,F.Geo,Energy,Gradient,
            F.tmvec.structure,F.NumMerUnit());
  }

}

#include "data/interaction/simple-vector.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      SimpleVectorInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const Vector<unsigned int>* idx, T& Energy) {
    for(unsigned int i=0;i<F.size;++i)
      F[i].EFunc(X,idx[i].data,F[i].prm.data,F.B,F.Geo,Energy,
                 F[i].tmvec.structure,F.NumMerUnit());
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      SimpleVectorInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X,const Vector<unsigned int>* idx,Vector<T>* Gradient) {
    for(unsigned int i=0;i<F.size;++i)
      F[i].GFunc(X,idx[i].data,F[i].prm.data,F.B,F.Geo,Gradient,
                 F[i].tmvec.structure,F.NumMerUnit());
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      SimpleVectorInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X,const Vector<unsigned int>* idx,
      T& Energy, Vector<T>* Gradient) {
    for(unsigned int i=0;i<F.size;++i)
      F[i].BFunc(X,idx[i].data,F[i].prm.data,F.B,F.Geo,Energy,Gradient,
                 F[i].tmvec.structure,F.NumMerUnit());
  }

}

#include "data/interaction/list.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const Vector<unsigned int>* idx,T& Energy) {
    for(unsigned int i=0;i<F.prm.size;++i)
      F.EFunc(X,idx[i].data,F.prm[i].data,F.B,F.Geo,Energy,
              F.tmvec.structure,F.NumMerUnit());
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const Vector<unsigned int>* idx,Vector<T>* Gradient){
    for(unsigned int i=0;i<F.prm.size;++i) {
      F.GFunc(X,idx[i].data,F.prm[i].data,F.B,F.Geo,Gradient,
              F.tmvec.structure,F.NumMerUnit());
    }
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const Vector<unsigned int>* idx,
      T& Energy, Vector<T>* Gradient) {
    for(unsigned int i=0;i<F.prm.size;++i)
      F.BFunc(X,idx[i].data,F.prm[i].data,F.B,F.Geo,Energy,Gradient,
              F.tmvec.structure,F.NumMerUnit());
  }

}

#include "data/interaction/list-vector.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListVectorInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const PropertyList<unsigned int>* idx, T& Energy) {
    for(unsigned int i=0;i<F.size;++i)
    for(unsigned int k=0;k<F[i].prm.size;++k)
      F[i].EFunc(X,idx[i][k].data,F[i].prm[k].data,F.B,F.Geo,Energy,
                 F[i].tmvec.structure,F.NumMerUnit());
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListVectorInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const PropertyList<unsigned int>* idx,
      Vector<T>* Gradient) {
    for(unsigned int i=0;i<F.size;++i)
    for(unsigned int k=0;k<F[i].prm.size;++k)
      F[i].GFunc(X,idx[i][k].data,F[i].prm[k].data,F.B,F.Geo,Gradient,
                 F[i].tmvec.structure,F.NumMerUnit());
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListVectorInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const PropertyList<unsigned int>* idx,
      T& Energy, Vector<T>* Gradient) {
    for(unsigned int i=0;i<F.size;++i)
    for(unsigned int k=0;k<F[i].prm.size;++k)
      F[i].BFunc(X,idx[i][k].data,F[i].prm[k].data,F.B,F.Geo,Energy,Gradient,
                 F[i].tmvec.structure,F.NumMerUnit());
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListVectorInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const Vector<Vector<unsigned int> >* idx, T& Energy){
    for(unsigned int i=0;i<F.size;++i)
    for(unsigned int k=0;k<F[i].prm.size;++k)
      F.EFunc(X,idx[i][k].data,F[i].prm[k].data,F.B,F.Geo,Energy,
              F[i].tmvec.structure,F.NumMerUnit());
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListVectorInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const Vector<Vector<unsigned int> >* idx,
      Vector<T>* Gradient) {
    for(unsigned int i=0;i<F.size;++i)
    for(unsigned int k=0;k<F[i].prm.size;++k)
      F.GFunc(X,idx[i][k].data,F[i].prm[k].data,F.B,F.Geo,Gradient,
              F[i].tmvec.structure,F.NumMerUnit());
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void CalcInteraction(
      ListVectorInteraction<T,DistBuffer,GeomType>& F,
      const Vector<T>* X, const Vector<Vector<unsigned int> >* idx,
      T& Energy, Vector<T>* Gradient) {
    for(unsigned int i=0;i<F.size;++i)
    for(unsigned int k=0;k<F[i].prm.size;++k)
      F.BFunc(X,idx[i][k].data,F[i].prm[k].data,F.B,F.Geo,Energy,Gradient,
              F[i].tmvec.structure,F.NumMerUnit());
  }

}

#endif

