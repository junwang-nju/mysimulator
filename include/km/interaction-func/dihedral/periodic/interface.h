
#ifndef _Interaction_Func_Dihedral_Periodic_Interface_H_
#define _Interaction_Func_Dihedral_Periodic_Interface_H_

#include "interaction-func/dihedral/interface.h"
#include "interaction-func/dihedral/periodic/pre-name.h"
#include "interaction-func/dihedral/periodic/post-name.h"
#include "interaction-func/dihedral/periodic/vec-name.h"
#include "interaction-func/dihedral/periodic/neighbor-name.h"
#include "basic/cos.h"
#include "basic/sin.h"

namespace mysimulator {

  template <typename T,typename GT>
  class InteractionFuncDihedralPeriodic : public InteractionFuncDihedral<T,GT> {

    public:

      typedef InteractionFuncDihedralPeriodic<T,GT>   Type;
      typedef InteractionFuncDihedral<T,GT>   ParentType;

      InteractionFuncDihedralPeriodic() : ParentType() {}
      ~InteractionFuncDihedralPeriodic() { Clear(*this); }

      virtual void Allocate(unsigned int dim) {
        Clear(*this);
        this->_tag=DihedralPeriodic;
        this->_pre.Allocate(DihedralPeriodicNumberPre);
        this->_post.Allocate(DihedralPeriodicNumberPost);
        this->_tmvec.Allocate(DihedralPeriodicNumberVec,dim);
        this->_neighbor.Allocate(DihedralPeriodicNumberNeighbor);
      }

    protected:

      virtual void EFunc(const InteractionParameter<T>* P, T* Func) {
        Unique64Bit *Q=const_cast<Unique64Bit*>(&((*P)[DihedralPeriodicShift]));
        T dih=this->_post[DihedralValue];
        T theta;
        const unsigned int n=
          Value<unsigned int>((*P)[DihedralPeriodicNumberUnit]);
        for(unsigned int i=0;i<n;++i) {
          theta=dih+Value<T>(Q[DihedralPeriodicPhase]);
          theta*=Value<unsigned int>(Q[DihedralPeriodicFrequency]);
          (*Func)+=Value<T>(Q[DihedralPeriodicStrength])*(_Cos(theta)+1.);
          Q+=DihedralPeriodicUnitNumberParameter;
        }
      }
      virtual void GFunc(const InteractionParameter<T>* P, T* Diff) {
        Unique64Bit *Q=const_cast<Unique64Bit*>(&((*P)[DihedralPeriodicShift]));
        T dih=this->_post[DihedralValue];
        T theta;
        const unsigned int n=
          Value<unsigned int>((*P)[DihedralPeriodicNumberUnit]);
        for(unsigned int i=0;i<n;++i) {
          theta=dih+Value<T>(Q[DihedralPeriodicPhase]);
          theta*=Value<unsigned int>(Q[DihedralPeriodicFrequency]);
          (*Diff)-=Value<T>(Q[DihedralPeriodicStrFreq])*_Sin(theta);
          Q+=DihedralPeriodicUnitNumberParameter;
        }
      }
      virtual void BFunc(const InteractionParameter<T>* P, T* Func, T* Diff) {
        Unique64Bit *Q=const_cast<Unique64Bit*>(&((*P)[DihedralPeriodicShift]));
        T dih=this->_post[DihedralValue];
        T theta;
        const unsigned int n=
          Value<unsigned int>((*P)[DihedralPeriodicNumberUnit]);
        for(unsigned int i=0;i<n;++i) {
          theta=dih+Value<T>(Q[DihedralPeriodicPhase]);
          theta*=Value<unsigned int>(Q[DihedralPeriodicFrequency]);
          (*Func)+=Value<T>(Q[DihedralPeriodicStrength])*(_Cos(theta)+1.);
          (*Diff)-=Value<T>(Q[DihedralPeriodicStrFreq])*_Sin(theta);
          Q+=DihedralPeriodicUnitNumberParameter;
        }
      }

    private:

      InteractionFuncDihedralPeriodic(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(InteractionFuncDihedralPeriodic<T,GT>& F) {
    typedef typename InteractionFuncDihedralPeriodic<T,GT>::ParentType PType;
    Clear(static_cast<PType&>(F));
  }

  template <typename T1,typename GT1,typename T2,typename GT2>
  void _Copy(InteractionFuncDihedralPeriodic<T1,GT1>& F,
             const InteractionFuncDihedralPeriodic<T2,GT2>& BF) {
    typedef typename InteractionFuncDihedralPeriodic<T1,GT1>::ParentType PType1;
    typedef typename InteractionFuncDihedralPeriodic<T2,GT2>::ParentType PType2;
    _Copy(static_cast<PType1&>(F),static_cast<const PType2&>(BF));
  }

}

#endif

