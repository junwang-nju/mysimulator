
#ifndef _PDB_Contact_Analyze_H_
#define _PDB_Contact_Analyze_H_

#include "pdb/interface.h"
#include "pdb/contact/mode.h"
#include "pdb/atom/position/distance.h"

namespace mysimulator {

  template <PDBContactAnalyseModeName AM, PDBContactStructureModeName SM,
            typename AType>
  struct _ContactFunctor {

    public:
      static unsigned int Analyse(const PDBObject&, AType&, const double&) {
        Error("Not Implemented");
        return 0;
      }
      static unsigned int Analyse(const PDBObject& PO, AType& id) {
        return Analyse(PO,id,0.);
      }

  };

  template <typename AType>
  struct _ContactFunctor<CAlpha,FirstModel,AType> {
    public:
      static unsigned int Analyse(
          const PDBObject& PO, AType& id, const double& th) {
        assert(IsValid(PO));
        PDBMolecule* Mol=PO.Model[0].Molecule.start;
        unsigned int MolSize=PO.Model[0].Molecule.size;
        unsigned int w;
        const double thsq=th*th;
        w=0;
        for(unsigned int i=0;i<MolSize;++i)
        for(unsigned int k=0;k<Mol[i].Residue.size;++k) {
          for(unsigned int j=i;j<MolSize;++j)
          for(unsigned int l=0;l<Mol[j].Residue.size;++l) {
            if((k>=l)&&(i==j))  continue;
            if(DistanceSQ(Mol[i].Residue[k].Atom[AtomCA]->Loc,
                          Mol[j].Residue[l].Atom[AtomCA]->Loc)<thsq) {
              id[w][0]=i; id[w][1]=k; id[w][2]=j; id[w][3]=l;
              ++w;
              if(w>id.NumLines()) Error("Storage for ID Used Up!");
            }
          }
        }
        return w;
      }
      static unsigned int Analyse(const PDBObject& PO, AType& id) {
        return Analyse(PO,id,7.5);
      }
  };

  template <typename AType>
  struct _ContactFunctor<HeavyAtoms,FirstModel,AType> {
    public:
      static unsigned int Analyse(
          const PDBObject& PO, AType& id, const double& th) {
        assert(IsValid(PO));
        PDBMolecule* Mol=PO.Model[0].Molecule.start;
        unsigned int MolSize=PO.Model[0].Molecule.size;
        PDBAtomName AN1,AN2;
        unsigned int w;
        bool fbreak;
        const double thsq=th*th;
        w=0;
        for(unsigned int i=0;i<MolSize;++i)
        for(unsigned int k=0;k<Mol[i].Residue.size;++k) {
          for(unsigned int j=0;j<MolSize;++j)
          for(unsigned int l=0;l<Mol[j].Residue.size;++l) {
            if((k>=l)&&(i==j))  continue;
            if(i>j) continue;
            fbreak=false;
            for(unsigned int m=0;m<Mol[i].Residue[k].AtomName.size;++m) {
              if(fbreak)  break;
              AN1=Mol[i].Residue[k].AtomName[m];
              if(!IsHeavyAtom(AN1)) continue;
              for(unsigned int n=0;n<Mol[j].Residue[l].AtomName.size;++n) {
                if(fbreak)  break;
                AN2=Mol[j].Residue[l].AtomName[n];
                if(!IsHeavyAtom(AN2)) continue;
                if(DistanceSQ(Mol[i].Residue[k].Atom[AN1]->Loc,
                              Mol[j].Residue[l].Atom[AN2]->Loc)<thsq) {
                  id[w][0]=i; id[w][1]=k; id[w][2]=j; id[w][3]=l;
                  ++w;
                  if(w>id.NumLines()) Error("Storage for ID Used Up!");
                  fbreak=true;
                }
              }
            }
          }
        }
        return w;
      }

      static unsigned int Analyse(const PDBObject& PO, AType& id) {
        return Analyse(PO,id,5.0);
      }

  };

}

#include "array/2d/interface.h"

namespace mysimulator {

  template <PDBContactAnalyseModeName AM, PDBContactStructureModeName SM>
  unsigned int PDB2Contact(
      const PDBObject& PO, Array2DContent<unsigned int>& id, const double& th){
    return
    _ContactFunctor<AM,SM,Array2DContent<unsigned int> >::Analyse(PO,id,th);
  }

  template <PDBContactAnalyseModeName AM, PDBContactStructureModeName SM>
  unsigned int PDB2Contact(
      const PDBObject& PO, Array2DContent<unsigned int>& id){
    return _ContactFunctor<AM,SM,Array2DContent<unsigned int> >::Analyse(PO,id);
  }

  template <PDBContactAnalyseModeName AM, PDBContactStructureModeName SM>
  unsigned int PDB2Contact(const PDBObject& PO, Array2DContent<int>& id,
                           const double& th){
    return _ContactFunctor<AM,SM,Array2DContent<int> >::Analyse(PO,id,th);
  }

  template <PDBContactAnalyseModeName AM, PDBContactStructureModeName SM>
  unsigned int PDB2Contact(const PDBObject& PO, Array2DContent<int>& id) {
    return _ContactFunctor<AM,SM,Array2DContent<int> >::Analyse(PO,id);
  }

}

#endif

