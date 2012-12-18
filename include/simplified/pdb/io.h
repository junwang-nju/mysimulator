
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

#endif

