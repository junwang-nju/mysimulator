
#ifndef _Grouped_Interaction_Interface_H_
#define _Grouped_Interaction_Interface_H_

#include "system-interaction/interface.h"

namespace mysimulator {

  template <typename T,typename GT>
  class GroupedInteraction {

    public:

      typedef GroupedInteraction<T,GT>    Type;
      template <typename T1,typename GT1>
      friend void Clear(GroupedInteraction<T1,GT1>&);

      GroupedInteraction() : _ISet(), _id() {}
      ~GroupedInteraction() { Clear(*this); }

      bool IsValid() const { return _ISet.IsValid()&&_id.IsValid(); }

      void Allocate(unsigned int n) {
        assert(_ISet.IsValid());
        assert(n<=_ISet.Size());
        _id.Allocate(n);
      }
      void Introduce(Array<SystemInteraction<T,GT> >& AI) { _ISet.Refer(AI); }

      unsigned int& WorkID(unsigned int n) { return _id[n]; }
      const unsigned int& WorkID(unsigned int n) const { return _id[n]; }

      void Calc(const ArrayNumeric<ArrayNumeric<T> >& X, T& Energy) {
        assert(IsValid());
        assert(X.IsValid());
        for(unsigned int i=0;i<_id.Size();++i)  _ISet[_id[i]].CalcE(X);
        Energy=0;
        for(unsigned int i=0;i<_id.Size();++i)  Energy+=_ISet[_id[i]].Energy();
      }
      void Calc(const ArrayNumeric<ArrayNumeric<T> >& X,
                Array2DNumeric<T>& Gradient) {
        assert(IsValid());
        assert(X.IsValid());
        assert(Gradient.IsValid());
        for(unsigned int i=0;i<_id.Size();++i) _ISet[_id[i]].CalcG(X);
        Gradient.BlasFill(0);
        for(unsigned int i=0;i<_id.Size();++i)
          Gradient.BlasShift(_ISet[_id[i]].Gradient());
      }
      void Calc(const ArrayNumeric<ArrayNumeric<T> >& X, T& Energy,
                Array2DNumeric<T>& Gradient) {
        assert(IsValid());
        assert(X.IsValid());
        assert(Gradient.IsValid());
        for(unsigned int i=0;i<_id.Size();++i) _ISet[_id[i]].CalcB(X);
        Energy=0;
        Gradient.BlasFill(0);
        for(unsigned int i=0;i<_id.Size();++i) {
          Energy+=_ISet[_id[i]].Energy();
          Gradient.BlasShift(_ISet[_id[i]].Gradient());
        }
      }

      void ClearFlag() {
        for(unsigned int i=0;i<_ISet.Size();++i)  _ISet[i].ClearFlag();
      }

    protected:

      Array<SystemInteraction<T,GT> > _ISet;
      Array<unsigned int> _id;

    private:

      GroupedInteraction(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(GroupedInteraction<T,GT>& I) {
    Clear(I._id);
    Clear(I._ISet);
  }

}

#endif

