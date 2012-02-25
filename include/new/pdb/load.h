
#ifndef _PDB_Load_H_
#define _PDB_Load_H_

#include "pdb/allocate.h"
#include "pdb/model/get-number.h"
#include "pdb/molecule/get-number.h"
#include "pdb/residue/get-number.h"
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

    n=strlen(ROOT);
    fname=new char[n+11];
    strncpy(fname,ROOT,n);
    strncpy(fname+n,code,4);
    strncpy(fname+n+4,".pdb",4);

    allocate(buffer,MaxBufferSize);

    FI.open(fname);
    n=0;
    fill(buffer,'\0');
    while(!IsFailed(FI))  FI>>buffer[n++];
    FI.close();

    strncpy(O.Code,code,4);
    n=NumberModels(buffer);
    allocate(O,n);
    n=NumberMolecules(buffer);
    for(unsigned int i=0;i<O.Model.size;++i)  allocate(O.Model[i],n);
    allocate(nRes,n);
    NumberResidues(nRes,buffer);
    for(unsigned int i=0;i<O.Model.size;++i)
    for(unsigned int j=0;j<O.Model[i].Molecule.size;++j)
      allocate(O.Model[i].Molecule[j],nRes[j]);

    release(buffer);
    delete_array(fname);
  }

}

#endif

