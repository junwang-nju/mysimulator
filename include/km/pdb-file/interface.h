
#ifndef _PDB_File_Interface_H_
#define _PDB_File_Interface_H_

#include "array/interface.h"
#include "pdb-file/record-name.h"
#include <cstdio>
#include <cstring>

namespace mysimulator {

  class PDBFile {

    public:

      typedef PDBFile   Type;
      friend void Clear(PDBFile&);

      PDBFile() : _content(), _now(NULL) {}
      ~PDBFile() { Clear(*this); }

      bool IsValid() const { return _content.IsValid(); }
      void Load(const char* code, const char* ROOT="./") {
        Clear(*this);
        char* fname;
        unsigned int n;
        n=strlen(ROOT);
        fname=new char[n+11];
        strncpy(fname,ROOT,n);
        strncpy(fname+n,code,4);
        strncpy(fname+n+4,".pdb",4);
        fname[n+4+4]='\0';
        FILE *fi=NULL;
        fi=fopen(fname,"rt");
        if(fi==NULL)  fprintf(stderr,"PDB File %s Nor Found!\n",fname);
        else {
          n=0;
          while(fgetc(fi)!=EOF) n++;
          fclose(fi);
          _content.Allocate(n+1);
          fi=fopen(fname,"rt");
          char c;
          n=0;
          while((c=fgetc(fi))!=EOF) _content[n++]=c;
          _content[n]='\0';
          fclose(fi);
          _now=_content.Head();
        }
      }

    protected:

      Array<char> _content;
      char* _now;

    private:

      PDBFile(const Type&) {}
      Type& operator=(const Type&) { return *this; }

      PDBRecordName RecordName() {
        if(strncmp(_now,"ATOM  ",6)==0)       return PDB_ATOM;
        else if(strncmp(_now,"MODEL ",6)==0)  return PDB_MODEL;
        else if(strncmp(_now,"ENDMDL",6)==0)  return PDB_ENDMDL;
        else if(strncmp(_now,"TER   ",6)==0)  return PDB_TER;
        return PDB_NotIMPLEMENTED;
      }

  };

  void Clear(PDBFile& F) { Clear(F._content); F._now=NULL; }

}

#endif

