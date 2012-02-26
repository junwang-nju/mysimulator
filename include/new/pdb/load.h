
#ifndef _PDB_Load_H_
#define _PDB_Load_H_

#include "pdb/allocate.h"
#include "pdb/model/get-number.h"
#include "pdb/model/allocate.h"
#include "pdb/molecule/get-number.h"
#include "pdb/molecule/allocate.h"
#include "pdb/residue/get-number.h"
#include "pdb/residue/guess-name.h"
#include "pdb/residue/set.h"
#include "pdb/residue/allocate.h"
#include "pdb/parse/ATOM/atom-name.h"
#include "pdb/parse/ATOM/residue-id.h"
#include "pdb/parse/ATOM/chain-tag.h"
#include "pdb/parse/ATOM/b-factor.h"
#include "pdb/parse/ATOM/position.h"
#include "io/input/file/interface.h"
#include "array/1d/allocate.h"
#include "array/1d/fill.h"

namespace mysimulator {

  void load(PDBObject& O, const char* code, const char* ROOT="./") {
    static const unsigned int MaxBufferSize=80000000U;
    char *fname;
    Array1D<char> buffer;
    unsigned int n;
    FileInput FI;
    Array1D<unsigned int> nRes;
    bool rflag;
    char* run;
    PDBLineName PLN;
    PDBAtomName AMN;
    int ResID,pResID=-1;
    unsigned int MolTag,pMolTag;
    int nmd,nml,nres;

    n=strlen(ROOT);
    fname=new char[n+11];
    strncpy(fname,ROOT,n);
    strncpy(fname+n,code,4);
    strncpy(fname+n+4,".pdb",4);

    allocate(buffer,MaxBufferSize);

    FI.open(fname);
    if(IsFailed(FI))  Error("PDB File",fname,"Not Found!");
    n=0;
    fill(buffer,'\0');
    while(!IsFailed(FI))  FI>>buffer[n++];
    FI.close();

    n=NumberModels(buffer);
    allocate(O,n);
    strncpy(O.Code,code,4);
    n=NumberMolecules(buffer);
    for(unsigned int i=0;i<O.Model.size;++i)  allocate(O.Model[i],n);
    allocate(nRes,n);
    NumberResidues(nRes,buffer);
    for(unsigned int i=0;i<O.Model.size;++i)
    for(unsigned int j=0;j<O.Model[i].Molecule.size;++j) {
      allocate(O.Model[i].Molecule[j],nRes[j]);
      for(unsigned int k=0;k<O.Model[i].Molecule[j].Residue.size;++k)
        allocate(O.Model[i].Molecule[j].Residue[k]);
    }

    run=buffer.start;
    rflag=true;
    nmd=0;
    nml=-1;
    pMolTag=0xFFFFFFFF;
    while(rflag) {
      n=LineSize(run);
      rflag=(run[n]!='\0');
      PLN=LineName(run);
      if(PLN==PDBENDMDL) {
        nmd++;
        pMolTag=0xFFFFFFFF;
        nml=-1;
      } else if((PLN==PDBATOM)&&(!AltLocationFlag4ATOM(run))) {
        AMN=AtomName4ATOM(run);
        ResID=ResidueID4ATOM(run);
        MolTag=ChainTag4ATOM(run);
        if(AMN==UnknownAtom) {
          for(unsigned int i=0;i<n;++i)  CErr<<run[i];
          CErr<<Endl;
          Error("Unknown Atom Type!");
        }
        if(MolTag!=pMolTag) {
          ++nml;
          pMolTag=MolTag;
          O.Model[nmd].Molecule[nml].Tag=MolTag;
          pResID=-1;
          nres=-1;
        }
        if(ResID!=pResID) {
          ++nres;
          pResID=ResID;
          O.Model[nmd].Molecule[nml].Residue[nres].ID=ResID;
        }
        O.Model[nmd].Molecule[nml].Residue[nres].Atom[AMN]=new PDBAtom;
        O.Model[nmd].Molecule[nml].Residue[nres].Atom[AMN]->BFactor=
          BFactor(run);
        Position(O.Model[nmd].Molecule[nml].Residue[nres].Atom[AMN]->Loc,run);
      }
      run+=n+1;
    }
    for(unsigned int i=0;i<O.Model.size;++i)
    for(unsigned int j=0;j<O.Model[i].Molecule.size;++j)
    for(unsigned int k=0;k<O.Model[i].Molecule[j].Residue.size;++k)
      set(O.Model[i].Molecule[j].Residue[k],
          GuessName(O.Model[i].Molecule[j].Residue[k].Atom));

    release(buffer);
    delete_array(fname);
  }

}

#endif

