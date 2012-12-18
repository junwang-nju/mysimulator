
#ifndef _PDB_InputOutput_H_
#define _PDB_InputOutput_H_

#include "pdb/io/get-number.h"
#include "pdb/io/get-content.h"

namespace mysimulator {

  PDB& operator<<(PDB& F,const char *code) {
    F.reset();
    F.SetCode(code);
    const char *ROOT= code[4]==':'?code+5:"./" ;
    unsigned int n=strlen(ROOT);
    char* fname=new char[n+11],*content;
    strncpy(fname,ROOT,n);
    if(fname[n-1]!='/') fname[n++]='/';
    strncpy(fname+n,code,4);  n+=4;
    strncpy(fname+n,".pdb",4);  n+=4;
    fname[n]='\0';
    FILE *fi=nullptr;
    fi=fopen(fname,"rt");
    if(fi==nullptr) fprintf(stderr,"PDB file %s Not Found!\n",fname);
    else {
      n=0;
      while(fgetc(fi)!=EOF) ++n;
      fclose(fi);
      content=new char[n+1];
      fi=fopen(fname,"rt");
      n=0;
      while((content[n++]=fgetc(fi))!=EOF) {}
      content[n-1]='\0';
      fclose(fi);
      const unsigned int nmodel=_NumberModel(content);
      F.allocate(nmodel);
      const unsigned int nmol=_NumberMolecule(content);
      Array<UInt,ArrayKernelName::SSE> nres(nmol);
      _NumberResidue(content,nres);
      for(unsigned int i=0;i<nmodel;++i) {
        F[i].allocate(nmol);
        for(unsigned int j=0;j<nmol;++j)  F[i][j].allocate(nres[j]);
      }
      F.BuildSeqMap();
      nres.reset();
      _GetMoleculeTag(content,F);
      _GetAltAtomInf(content,F);
      _GetResidue(content,F);
      _GetAtom(content,F);
      delete[] content;
    }
    delete[] fname;
    return F;
  }

}

#include "geometry/contact/interface.h"
#include "geometry/contact/method/interface.h"
#include "geometry/distance/calc.h"
#include "basic/util/square.h"

namespace mysimulator {

  template <ContactMethodName CMN>
  Contact operator &(PDB const& F, ContactMethod<CMN> const& M) {
    Contact C;
    fprintf(stderr,"Unknown Method to evaluate Contact!\n");
    return C;
  }

  Contact operator&(PDB const& F,
                    ContactMethod<ContactMethodName::CAlphaDistance> const& M) {
    assert((bool)F);
    Contact C;
    Array2D<Double,ArrayKernelName::SSE> _X;
    Array<Double,ArrayKernelName::Direct3D> Dsp;
    FreeSpace<3> FS;
    const SystemKindName PT=SystemKindName::Particle;
    if(M.ModelMode()==ModelSelectorName::First) {
      unsigned int n=0;
      for(unsigned int i=0;i<F[0].size();++i) n+=F[0][0].size();
      _X.allocate(n,3);
      Dsp.allocate(3);
      for(unsigned int i=0,m=0;i<F[0].size();++i)
      for(unsigned int j=0;j<F[0][0].size();++j,++m) {
        if(M.AltMode()==AltSelectorName::Default) {
          _X[m][0]=F[0].Residue(i,j,' ').Atom(PDBAtomName::CA).X();
          _X[m][1]=F[0].Residue(i,j,' ').Atom(PDBAtomName::CA).Y();
          _X[m][2]=F[0].Residue(i,j,' ').Atom(PDBAtomName::CA).Z();
        } else
          fprintf(stderr,"Not Implemented!\n");
      }
      double TSQ=__square(M.Threshold());
      n=0;
      for(unsigned int i=0;i<_X.size();++i)
      for(unsigned int j=i+1;j<_X.size();++j)
        if(TSQ<DistanceSQ<PT,PT>(Dsp,_X[i],_X[j],FS))  ++n;
      C.allocate(n);
      double tmd;
      for(unsigned int i=0,m=0;i<_X.size();++i)
      for(unsigned int j=i+1;j<_X.size();++j) {
        tmd=DistanceSQ<PT,PT>(Dsp,_X[i],_X[j],FS);
        if(TSQ<tmd) {
          C[m].I=i;
          C[m].J=j;
          C[m].Distance=__square_root(tmd);
          C[m].Kind=0;
          C[m].Weight=0.;
          ++m;
        }
      }
    } else
      fprintf(stderr,"Not Implemented!\n");
    Dsp.reset();
    _X.reset();
    return C;
  }

}

#endif

