
#ifndef _Interaction_Gao_Enhanced_Sampling_H_
#define _Interaction_Gao_Enhanced_Sampling_H_

namespace std {
  
  template <typename T,template<typename> class DBuff, typename GeomType,
            template <typename,template<typename>class,typename> class IType,
            typename PType>
  void EFuncGaoES(
      const Vector<T>* X, IType<T,DBuff,GeomType>& I, PType& P, 
      const UniqueParameter* MP, T& Energy, Vector<T>* tmvec=NULL) {
    T U=0.;
    CalcInteraction(I,X,P,U);
    Vector<T>& lnd=*reinterpret_cast<Vector<T>*>(MP[LnDensitySet].ptr);
    Vector<T>& b=*reinterpret_cast<Vector<T>*>(MP[BetaSet].ptr);
    T Up=0.;
  }

}

#endif
