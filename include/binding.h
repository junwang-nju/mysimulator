
#ifndef _Binding_H_
#define _Binding_H_

#include "interaction-method.h"
#include "property-list.h"
#include "parameter-list.h"

namespace std {

  enum BindingCase {
    NoneBinding=0,
    CoordinateBinding,
    ParameterBinding,
    BothBinding
  };

  template <unsigned int BindingMode>
  class Binding {
    public:
      Binding() { myError("Unknown Binding Mode"); }
  };

  template <>
  class Binding<NoneBinding> {
    public:
      typedef Binding<NoneBinding>    Type;
      Binding() {}
      Binding(const Type& Binding) { myError("Cannot create from Binding"); }
      Type& operator=(const Type& B) {
        myError("Binding cannot be copied");
        return *this;
      }
  };

  template <>
  class Binding<CoordinateBinding> {
    public:
      typedef Binding<CoordinateBinding>  Type;
    protected:
      PropertyList<refVector<double>,varVector>  CoorLst;
      PropertyList<refVector<double>,varVector>  GradLst;
    public:
      Binding() : CoorLst(), GradLst() {}
      Binding(const Type& Binding) { myError("Cannot create from Binding"); }
      Type& operator=(const Type& B) {
        myError("Binding cannot be copied");
        return *this;
      }
      void With(const VectorBase<refVector<unsigned int> >& IdxLst,
                const VectorBase<refVector<double> >& CoorSeq,
                const VectorBase<refVector<double> >& GradSeq) {
        assert(IdxLst.size()>0);
        varVector<unsigned int> Sz(IdxLst.size());
        for(unsigned int i=0;i<IdxLst.size();++i) Sz[i]=IdxLst[i].size();
        CoorLst.allocate(Sz);
        GradLst.allocate(Sz);
        for(unsigned int i=0;i<IdxLst.size();++i)
        for(unsigned int j=0;j<IdxLst[i].size();++j) {
          CoorLst[i][j].refer(CoorSeq[IdxLst[i][j]]);
          GradLst[i][j].refer(GradSeq[IdxLst[i][j]]);
        }
      }

      typedef varVector<refVector<refVector<double> > > VecListType;

      VecListType& RunCoordinateList() { return CoorLst.Structure(); }
      
      const VecListType& RunCoordinateList() const {
        return CoorLst.Structure();
      }

      VecListType& RunGradientList() { return GradLst.Structure(); }
      
      const VecListType& RunGradientList() const{ return GradLst.Structure(); }

  };

  template <>
  class Binding<ParameterBinding> {
    public:
      typedef Binding<ParameterBinding>    Type;
    protected:
      varVector<refVector<double> > PrmLst;
    public:
      Binding() : PrmLst() {}
      Binding(const Type& Binding) { myError("Cannot create from Binding"); }
      Type& operator=(const Type& B) {
        myError("Binding cannot be copied");
        return *this;
      }
      template <template <template <typename> class> class DistEvalMethod,
                template <template <typename> class> class GeomType,
                template <typename> class VecTypeP>
      void With(const InteractionMethod<DistEvalMethod,GeomType>& IM,
                const VectorBase<refVector<unsigned int> >& IdxLst,
                const VectorBase<unsigned int>& KindSeq,
                const ParameterList<VecTypeP>& ParamCollection) {
        assert(IdxLst.size()>0);
        PrmLst.allocate(IdxLst.size());
        varVector<unsigned int> prmKey(IdxLst[0].size()+1);
        prmKey[0]=IM.InteractionTag();
        for(unsigned int i=0;i<IdxLst.size();++i) {
          for(unsigned int j=0;j<IdxLst[i].size();++j)
            prmKey[j+1]=KindSeq[IdxLst[i][j]];
          PrmLst[i].refer(*ParamCollection.get(prmKey));
        }
      }
      typedef varVector<refVector<double> > PrmListType;
      PrmListType& RunParameterList() { return PrmLst; }
      const PrmListType& RunParameterList() const { return PrmLst; }
  };

  template <>
  class Binding<BothBinding> {
    public:
      typedef Binding<BothBinding>    Type;
    protected:
      PropertyList<refVector<double>,varVector>  CoorLst;
      PropertyList<refVector<double>,varVector>  GradLst;
      varVector<refVector<double> > PrmLst;
    public:
      Binding() : CoorLst(), GradLst(), PrmLst() {}
      Binding(const Type& Binding) { myError("Cannot create from Binding"); }
      Type& operator=(const Type& B) {
        myError("Binding cannot be copied");
        return *this;
      }
      template <template <template <typename> class> class DistEvalMethod,
                template <template <typename> class> class GeomType,
                template <typename> class VecTypeP>
      void With(const InteractionMethod<DistEvalMethod,GeomType>& IM,
                const VectorBase<refVector<unsigned int> >& IdxLst,
                const VectorBase<unsigned int>& KindSeq,
                const VectorBase<refVector<double> >& CoorSeq,
                const VectorBase<refVector<double> >& GradSeq,
                const ParameterList<VecTypeP>& ParamCollection) {
        assert(IdxLst.size()>0);
        varVector<unsigned int> Sz(IdxLst.size());
        for(unsigned int i=0;i<IdxLst.size();++i) Sz[i]=IdxLst[i].size();
        CoorLst.allocate(Sz);
        GradLst.allocate(Sz);
        PrmLst.allocate(IdxLst.size());
        varVector<unsigned int> prmKey(IdxLst[0].size()+1);
        prmKey[0]=IM.InteractionTag();
        for(unsigned int i=0;i<IdxLst.size();++i) {
          for(unsigned int j=0;j<IdxLst[i].size();++j) {
            CoorLst[i][j].refer(CoorSeq[IdxLst[i][j]]);
            GradLst[i][j].refer(GradSeq[IdxLst[i][j]]);
            prmKey[j+1]=KindSeq[IdxLst[i][j]];
          }
          PrmLst[i].refer(*ParamCollection.get(prmKey));
        }
      }
      typedef varVector<refVector<double> > PrmListType;
      PrmListType& RunParameterList() { return PrmLst; }
      const PrmListType& RunParameterList() const { return PrmLst; }

      typedef varVector<refVector<refVector<double> > > VecListType;

      VecListType& RunCoordinateList() { return CoorLst.Structure(); }
      
      const VecListType& RunCoordinateList() const {
        return CoorLst.Structure();
      }

      VecListType& RunGradientList() { return GradLst.Structure(); }
      
      const VecListType& RunGradientList() const{ return GradLst.Structure(); }

  };

}

#endif

