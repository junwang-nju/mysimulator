
/**
 * @file pdb/interface.h
 * @brief dat structure storing whole information from PDB file
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _PDB_Interface_H_
#define _PDB_Interface_H_

#include "array2d/interface.h"
#include "pdb-model/interface.h"
#include "pdb/contact-mode.h"
#include "pdb/source-mode.h"
#include "distance/calc.h"
#include <cstring>

namespace mysimulator {

  class PDBObject {

    public:

      typedef PDBObject   Type;
      friend void Clear(PDBObject&);
      friend class PDBFile;

      PDBObject() : _code(), _nres(0), _model(), _seqIdx() {
        strncpy(_code,"    ",5);
      }
      ~PDBObject() { Clear(*this); }

      bool IsValid() const {
        return (strncmp(_code,"    ",4)!=0)&&(_nres>0)&&
               _model.IsValid()&&_seqIdx.IsValid();
      }
      void Allocate(unsigned int n) { _model.Allocate(n); }

      PDBModel& Model(unsigned int i) {
        assert(_model.IsValid()); return _model[i];
      }
      const char* Code() const { return _code; }
      const unsigned int NumberResidue() const { return _nres; }
      const PDBModel& Model(unsigned int i) const {
        assert(_model.IsValid()); return _model[i];
      }
      const unsigned int Index(unsigned int i,unsigned int j) const {
        assert(_seqIdx.IsValid());
        return _seqIdx[i][j];
      }
      void BuildIndex() {
        assert(_seqIdx.IsValid());
        const unsigned int n=_seqIdx.NumElements();
        _nres=n;
        for(unsigned int i=0;i<n;++i) _seqIdx._ldata[i]=i;
      }

      const unsigned int NumberModel() const { return _model.Size(); }

      template <PDBSourceMode SM,typename T>
      unsigned int ProduceCAlpha(Array2DNumeric<T>& X) {
        if(SM==UseFirstModel) return _ProduceCAlpha_FirstModel(X);
        else {
          fprintf(stderr,"Improper Source Mode!\n");
          return 0;
        }
      }

      template <typename T>
      unsigned int _ProduceCAlpha_FirstModel(Array2DNumeric<T>& X) {
        const unsigned int NMol=Model(0).NumberMolecule();
        if(X.Size()!=NumberResidue()) {
          Clear(X);
          X.Allocate(NumberResidue(),3);
        }
        for(unsigned int i=0,n=0;i<NMol;++i)
        for(unsigned int j=0;j<Model(0).Molecule(i).NumberResidue();++j,++n) {
          X[n][0]=Model(0).Residue(i,j).Atom(AtomCA).Location().X();
          X[n][1]=Model(0).Residue(i,j).Atom(AtomCA).Location().Y();
          X[n][2]=Model(0).Residue(i,j).Atom(AtomCA).Location().Z();
        }
        return NMol;
      }

      template <PDBContactAnalysisMode AM,PDBSourceMode SM>
      unsigned int ProduceContact(const double&,Array2D<unsigned int>&) {
        fprintf(stderr,"Not Available!\n");
        return 0;
      }

      template <PDBContactAnalysisMode AM,PDBSourceMode SM>
      unsigned int ProduceContact(Array2D<unsigned int>&) {
        fprintf(stderr,"Not Available!\n");
        return 0;
      }

    protected:

      char _code[5];
      unsigned int _nres;
      Array<PDBModel> _model;
      Array2D<unsigned int> _seqIdx;

    private:

      PDBObject(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void Clear(PDBObject& O) {
    strncpy(O._code,"    ",5);
    O._nres=0;
    Clear(O._model);
    Clear(O._seqIdx);
  }

  template <>
  unsigned int PDBObject::ProduceContact<BaseCAlpha,UseFirstModel>(
      const double& TH, Array2D<unsigned int>& CM) {
    const unsigned int NMol=Model(0).NumberMolecule();
    const double THSQ=TH*TH;
    unsigned int nc;
    nc=0;
    for(unsigned int i=0;i<NMol;++i)
    for(unsigned int k=0;k<Model(0).Molecule(i).NumberResidue();++k)
    for(unsigned int j=i;j<NMol;++j)
    for(unsigned int l=0;l<Model(0).Molecule(j).NumberResidue();++l) {
      if((i==j)&&(k>=l))  continue;
      if(DistanceSQ(Model(0).Residue(i,k).Atom(AtomCA).Location(),
                    Model(0).Residue(j,l).Atom(AtomCA).Location())<THSQ)
        ++nc;
    }
    if(CM.Size()!=nc) {
      Clear(CM);
      CM.Allocate(nc,4);
    }
    nc=0;
    for(unsigned int i=0;i<NMol;++i)
    for(unsigned int k=0;k<Model(0).Molecule(i).NumberResidue();++k)
    for(unsigned int j=i;j<NMol;++j)
    for(unsigned int l=0;l<Model(0).Molecule(j).NumberResidue();++l) {
      if((i==j)&&(k>=l))  continue;
      if(DistanceSQ(Model(0).Residue(i,k).Atom(AtomCA).Location(),
                    Model(0).Residue(j,l).Atom(AtomCA).Location())<THSQ) {
        CM[nc][0]=i;  CM[nc][1]=k;
        CM[nc][2]=j;  CM[nc][3]=l;
        ++nc;
      }
    }
    return nc;
  }

  template <>
  unsigned int PDBObject::ProduceContact<BaseHeavyAtoms,UseFirstModel>(
      const double& TH, Array2D<unsigned int>& CM) {
    const unsigned int NMol=Model(0).NumberMolecule();
    const double THSQ=TH*TH;
    PDBAtomName AN1,AN2;
    unsigned int nc=0;
    for(unsigned int i=0;i<NMol;++i)
    for(unsigned int k=0;k<Model(0).Molecule(i).NumberResidue();++k)
    for(unsigned int j=i;j<NMol;++j)
    for(unsigned int l=0;l<Model(0).Molecule(j).NumberResidue();++l) {
      if((i==j)&&(k>=l))  continue;
      for(unsigned int m=0;m<Model(0).Residue(i,k).NumberAtom();++m) {
        AN1=Model(0).Residue(i,k).AtomName(m);
        if(!IsHeavyAtom(AN1))  continue;
        for(unsigned int n=0;n<Model(0).Residue(j,l).NumberAtom();++n) {
          AN2=Model(0).Residue(j,l).AtomName(n);
          if(!IsHeavyAtom(AN2))  continue;
          if(DistanceSQ(Model(0).Residue(i,k).Atom(AN1).Location(),
                        Model(0).Residue(j,l).Atom(AN2).Location())<THSQ) {
            ++nc;
            m=Model(0).Residue(i,k).NumberAtom()+1;
            break;
          }
        }
      }
    }
    if(CM.Size()!=nc) {
      Clear(CM);
      CM.Allocate(nc,4);
    }
    nc=0;
    for(unsigned int i=0;i<NMol;++i)
    for(unsigned int k=0;k<Model(0).Molecule(i).NumberResidue();++k)
    for(unsigned int j=i;j<NMol;++j)
    for(unsigned int l=0;l<Model(0).Molecule(j).NumberResidue();++l) {
      if((i==j)&&(k>=l))  continue;
      for(unsigned int m=0;m<Model(0).Residue(i,k).NumberAtom();++m) {
        AN1=Model(0).Residue(i,k).AtomName(m);
        if(!IsHeavyAtom(AN1))  continue;
        for(unsigned int n=0;n<Model(0).Residue(j,l).NumberAtom();++n) {
          AN2=Model(0).Residue(j,l).AtomName(n);
          if(!IsHeavyAtom(AN2))  continue;
          if(DistanceSQ(Model(0).Residue(i,k).Atom(AN1).Location(),
                        Model(0).Residue(j,l).Atom(AN2).Location())<THSQ) {
            CM[nc][0]=i;  CM[nc][1]=k;
            CM[nc][2]=j;  CM[nc][3]=l;
            ++nc;
            m=Model(0).Residue(i,k).NumberAtom()+1;
            break;
          }
        }
      }
    }
    return nc;
  }

  template <>
  unsigned int PDBObject::ProduceContact<BaseCAlpha,UseFirstModel>(
      Array2D<unsigned int>& CM) {
    return ProduceContact<BaseCAlpha,UseFirstModel>(7.5,CM);
  }
  template <>
  unsigned int PDBObject::ProduceContact<BaseHeavyAtoms,UseFirstModel>(
      Array2D<unsigned int>& CM) {
    return ProduceContact<BaseHeavyAtoms,UseFirstModel>(4.5,CM);
  }
  template <>
  unsigned int PDBObject::ProduceContact<SheaDef,UseFirstModel>(
      Array2D<unsigned int>& CM) {
    const unsigned int NMol=Model(0).NumberMolecule();
    PDBAtomName AN1,AN2;
    unsigned int nc=0;
    for(unsigned int i=0;i<NMol;++i)
    for(unsigned int k=0;k<Model(0).Molecule(i).NumberResidue();++k)
    for(unsigned int j=i;j<NMol;++j)
    for(unsigned int l=0;l<Model(0).Molecule(j).NumberResidue();++l) {
      if((i==j)&&(k>=l))  continue;
      if(DistanceSQ(Model(0).Residue(i,k).Atom(AtomCA).Location(),
                    Model(0).Residue(j,l).Atom(AtomCA).Location())<64.0) {
        ++nc;
        continue;
      }
      for(unsigned int m=0;m<Model(0).Residue(i,k).NumberAtom();++m) {
        AN1=Model(0).Residue(i,k).AtomName(m);
        if(!IsHeavyAtom(AN1))   continue;
        if(IsMainChain(AN1))    continue;
        for(unsigned int n=0;n<Model(0).Residue(j,l).NumberAtom();++n) {
          AN2=Model(0).Residue(j,l).AtomName(n);
          if(!IsHeavyAtom(AN2))   continue;
          if(IsMainChain(AN2))    continue;
          if(DistanceSQ(Model(0).Residue(i,k).Atom(AN1).Location(),
                        Model(0).Residue(j,l).Atom(AN2).Location())<16.0) {
            ++nc;
            m=Model(0).Residue(i,k).NumberAtom()+1;
            break;
          }
        }
      }
    }
    if(CM.Size()!=nc) {
      Clear(CM);
      CM.Allocate(nc,4);
    }
    nc=0;
    for(unsigned int i=0;i<NMol;++i)
    for(unsigned int k=0;k<Model(0).Molecule(i).NumberResidue();++k)
    for(unsigned int j=i;j<NMol;++j)
    for(unsigned int l=0;l<Model(0).Molecule(j).NumberResidue();++l) {
      if((i==j)&&(k>=l))  continue;
      if(DistanceSQ(Model(0).Residue(i,k).Atom(AtomCA).Location(),
                    Model(0).Residue(j,l).Atom(AtomCA).Location())<64.0) {
        CM[nc][0]=i;  CM[nc][1]=k;
        CM[nc][2]=j;  CM[nc][3]=l;
        ++nc;
        continue;
      }
      for(unsigned int m=0;m<Model(0).Residue(i,k).NumberAtom();++m) {
        AN1=Model(0).Residue(i,k).AtomName(m);
        if(!IsHeavyAtom(AN1))   continue;
        if(IsMainChain(AN1))    continue;
        for(unsigned int n=0;n<Model(0).Residue(j,l).NumberAtom();++n) {
          AN2=Model(0).Residue(j,l).AtomName(n);
          if(!IsHeavyAtom(AN2))   continue;
          if(IsMainChain(AN2))    continue;
          if(DistanceSQ(Model(0).Residue(i,k).Atom(AN1).Location(),
                        Model(0).Residue(j,l).Atom(AN2).Location())<16.0) {
            CM[nc][0]=i;  CM[nc][1]=k;
            CM[nc][2]=j;  CM[nc][3]=l;
            ++nc;
            m=Model(0).Residue(i,k).NumberAtom()+1;
            break;
          }
        }
      }
    }
    return nc;
  }

}

#endif

