
/**
 * @file pdb-file/interface.h
 * @brief the object to operate PDB file
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _PDB_File_Interface_H_
#define _PDB_File_Interface_H_

#include "pdb-file/record-name.h"
#include "pdb-file/atom-name-map.h"
#include "pdb-file/residue-name-map.h"
#include "pdb/interface.h"
#include "array2d-numeric/interface.h"
#include "basic/string.h"
#include <cstdio>
#include <cstring>

namespace mysimulator {

  class PDBFile {

    public:

      typedef PDBFile   Type;
      friend void Clear(PDBFile&);

      PDBFile() : _code(), _content(), _now(NULL) { strncpy(_code,"    ",5); }
      ~PDBFile() { Clear(*this); }

      bool IsValid() const {
        return _content.IsValid()&&(strncmp(_code,"    ",4)!=0);
      }
      const char* Code() const { return _code; }

      void Load(const char* code, const char* ROOT="./") {
        Clear(*this);
        strncpy(_code,code,4);
        _code[4]='\0';
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

      void Produce(PDBObject& M) {
        assert(IsValid());
        Clear(M);
        strncpy(M._code,_code,5);
        const unsigned int nmodel=NumberModel();
        M.Allocate(nmodel);
        const unsigned int nmol=NumberMolecule();
        ArrayNumeric<unsigned int> nres;
        nres.Allocate(nmol);
        NumberResidue(nres);
        M._seqIdx.Allocate(nres);
        M.BuildIndex();
        for(unsigned int i=0;i<nmodel;++i) {
          M.Model(i).Allocate(nmol);
          for(unsigned int j=0;j<nmol;++j) {
            M.Model(i).Molecule(j).Allocate(nres[j]);
          }
        }
        LoadMoleculeTag(M);
        LoadAltInfo(M);
        LoadResidue(M);
        LoadAtom(M);
      }

    protected:

      char _code[5];
      Array<char> _content;
      char* _now;

    private:

      PDBFile(const Type&) {}
      Type& operator=(const Type&) { return *this; }

      PDBRecordName RecordName() const {
        if(strncmp(_now,"ATOM  ",6)==0)       return PDB_ATOM;
        else if(strncmp(_now,"MODEL ",6)==0)  return PDB_MODEL;
        else if(strncmp(_now,"ENDMDL",6)==0)  return PDB_ENDMDL;
        else if(strncmp(_now,"TER   ",6)==0)  return PDB_TER;
        return PDB_NotIMPLEMENTED;
      }
      PDBAtomName AtomName() const {
        assert(RecordName()==PDB_ATOM);
        char str[6];
        SubString(str,_now,12,15);
        for(unsigned int i=0;i<NumberAtomNames;++i)
          if(strncmp(str,AtomMapping[i].NameString(),4)==0)
            return AtomMapping[i].Name();
        return UnknownAtom;
      }
      PDBResidueName ResidueName() const {
        assert(RecordName()==PDB_ATOM);
        char str[4];
        SubString(str,_now,17,19);
        for(unsigned int i=0;i<PDBResidueMappingSize;++i)
          if(strncmp(str,ResidueMapping[i].NameString(),3)==0)
            return ResidueMapping[i].Name();
        return UnknownResidue;
      }
      double BFactor() const {
        assert(RecordName()==PDB_ATOM);
        char str[8];
        SubString(str,_now,60,65);
        return atof(str);
      }
      double PositionX() const {
        assert(RecordName()==PDB_ATOM);
        char str[8];
        SubString(str,_now,30,37);
        return atof(str);
      }
      double PositionY() const {
        assert(RecordName()==PDB_ATOM);
        char str[8];
        SubString(str,_now,38,45);
        return atof(str);
      }
      double PositionZ() const {
        assert(RecordName()==PDB_ATOM);
        char str[8];
        SubString(str,_now,46,53);
        return atof(str);
      }
      unsigned int ChainTag() const {
        assert(RecordName()==PDB_ATOM);
        return static_cast<unsigned int>(_now[21]);
      }
      int ResidueID() const {
        assert(RecordName()==PDB_ATOM);
        char str[6];
        SubString(str,_now,22,25);
        return atoi(str);
      }
      char AltLocationFlag() const {
        assert(RecordName()==PDB_ATOM);
        return _now[16];
      }
      unsigned int NumberModel() {
        char *run=_now;
        unsigned int nl,nmodel;
        nl=0;
        nmodel=0;
        while(1) {
          nl=LineSize(_now);
          if(RecordName()==PDB_MODEL)  ++nmodel;
          if(_now[nl]=='\0')   break;
          _now+=nl+1;
        }
        _now=run;
        return (nmodel==0?1:nmodel);
      }
      unsigned int NumberMolecule() {
        char *run=_now;
        unsigned int nl,nmol;
        nl=0;
        nmol=0;
        PDBRecordName PRN;
        while(1) {
          nl=LineSize(_now);
          PRN=RecordName();
          if(PRN==PDB_TER)  ++nmol;
          else if(PRN==PDB_ENDMDL)  break;
          if(_now[nl]=='\0')   break;
          _now+=nl+1;
        }
        _now=run;
        return nmol;
      }
      void LoadMoleculeTag(PDBObject& M) {
        unsigned int nl,nMol,nTag=0;
        PDBRecordName PRN;
        nl=0;
        nMol=0;
        _now=_content.Head();
        while(1) {
          nl=LineSize(_now);
          PRN=RecordName();
          if(PRN==PDB_ENDMDL) break;
          else if(PRN==PDB_TER) { M.Model(0).Molecule(nMol)._tag=nTag; ++nMol; }
          else if(PRN==PDB_ATOM) nTag=ChainTag();
          if(_now[nl]=='\0')   break;
          _now+=nl+1;
        }
        _now=_content.Head();
        for(unsigned int i=1;i<M._model.Size();++i)
        for(unsigned int j=0;j<M.Model(i)._Molecule.Size();++j)
          M.Model(i).Molecule(j)._tag=M.Model(0).Molecule(j).Tag();
      }
      void NumberResidue(ArrayData<unsigned int>& RSz) { // scan only 1st-model
        assert(RSz.Size()==NumberMolecule());
        char *run=_now;
        PDBRecordName PRN;
        unsigned int nl,nmol,nres,tres,rres;
        nl=0;
        nmol=0;
        nres=0;
        tres=rres=0;
        while(1) {
          nl=LineSize(_now);
          PRN=RecordName();
          if(PRN==PDB_ATOM){
            tres=ResidueID();
            if(tres!=rres)  { ++nres; rres=tres; }
          } else if(PRN==PDB_TER) { RSz[nmol]=nres; ++nmol; nres=0; }
          else if(PRN==PDB_ENDMDL)  break;
          if(_now[nl]=='\0')   break;
          _now+=nl+1;
        }
        _now=run;
      }
      void LoadAltInfo(PDBObject& M) {
        char ALFSet[256];
        unsigned int NSet;
        unsigned int nl,nowModel,nowSet;
        bool isHaveEndMDL;
        char ALF;
        PDBRecordName PRN;
        nowModel=0;
        NSet=0;
        _now=_content.Head();
        isHaveEndMDL=false;
        while(1) {
          nl=LineSize(_now);
          PRN=RecordName();
          if(PRN==PDB_ENDMDL) {
            isHaveEndMDL=true;
            Clear(M.Model(nowModel)._AFlag);
            if(NSet>0)  {
              M.Model(nowModel)._AFlag.Allocate(NSet);
              for(unsigned int i=0;i<NSet;++i)
                M.Model(nowModel)._AFlag[i]=ALFSet[i];
            }
            ++nowModel;
            NSet=0;
          } else if(PRN==PDB_ATOM) {
            ALF=AltLocationFlag();
            if(ALF!=' ') {
              nowSet=257;
              for(unsigned int i=0;i<NSet;++i)
                if(ALF==ALFSet[i])  { nowSet=i; break; }
              if(nowSet>256) { ALFSet[NSet]=ALF;  ++NSet; }
            }
          }
          if(_now[nl]=='\0')   break;
          _now+=nl+1;
        }
        if(!isHaveEndMDL) {
          Clear(M.Model(nowModel)._AFlag);
          if(NSet>0)  {
            M.Model(nowModel)._AFlag.Allocate(NSet);
            for(unsigned int i=0;i<NSet;++i)
              M.Model(nowModel)._AFlag[i]=ALFSet[i];
          }
        }
        bool isHaveAlt;
        unsigned int nowMol,nowRes,tRes,rRes,n;
        nowModel=0;
        nowMol=0;
        nowRes=0;
        rRes=0;
        isHaveAlt=false;
        _now=_content.Head();
        while(1) {
          nl=LineSize(_now);
          PRN=RecordName();
          if(PRN==PDB_ENDMDL) { ++nowModel; nowMol=0; nowRes=0; }
          else if(PRN==PDB_TER) {
            n=(isHaveAlt?M.Model(nowModel)._AFlag.Size():1);
            M.Model(nowModel).Molecule(nowMol).AltResidue(nowRes).Allocate(n);
            isHaveAlt=false;
            ++nowMol; nowRes=0; rRes=0;
          } else if(PRN==PDB_ATOM) {
            tRes=ResidueID();
            if(rRes==0) rRes=tRes;
            if(tRes!=rRes) {
              n=(isHaveAlt?M.Model(nowModel)._AFlag.Size():1);
              M.Model(nowModel).Molecule(nowMol).AltResidue(nowRes).Allocate(n);
              isHaveAlt=false;
              ++nowRes;
              rRes=tRes;
            }
            isHaveAlt=isHaveAlt||(AltLocationFlag()!=' ');
          }
          if(_now[nl]=='\0')   break;
          _now+=nl+1;
        }
        _now=_content.Head();
      }

      void LoadResidue(PDBObject& M) {
        Array2DNumeric<unsigned int> key;
        char ALF;
        unsigned int nl,nMod,nMol,nRes,tRes,rRes,n;
        PDBRecordName PRN;
        PDBAtomName PAN;
        Array<PDBResidueName> RN;
        nl=0;
        nMod=0;
        nMol=0;
        nRes=0;
        rRes=0;
        n=M.Model(nMod)._AFlag.Size();
        n=(n==0?1:n);
        key.Allocate(n,NumberResidueKey);
        key.BlasFill(0U);
        RN.Allocate(n);
        for(unsigned int i=0;i<n;i++) RN[i]=UnknownResidue;
        _now=_content.Head();
        while(1) {
          nl=LineSize(_now);
          PRN=RecordName();
          if(PRN==PDB_ENDMDL) { ++nMod; nMol=0; nRes=0; rRes=0; Clear(key); }
          else if(PRN==PDB_MODEL) {
            n=M.Model(nMod)._AFlag.Size();
            n=(n==0?1:n);
            key.Allocate(n,NumberResidueKey);
            key.BlasFill(0U);
            RN.Allocate(n);
            for(unsigned int i=0;i<n;i++) RN[i]=UnknownResidue;
          } else if(PRN==PDB_TER) {
            n=M.Model(nMod).Molecule(nMol).AltResidue(nRes)._AResidue.Size();
            for(unsigned int i=0;i<n;++i) {
              if(M.Model(nMod)._AFlag.IsValid()) ALF=M.Model(nMod)._AFlag[i];
              else ALF=' ';
              if(!IsMatchResidue(RN[i],key[i].Head()))
                RN[i]=static_cast<PDBResidueName>(RN[i]+20);
              M.Model(nMod).Residue(nMol,nRes,ALF).Allocate(RN[i],
                                                            key[i].Head());
              M.Model(nMod).Residue(nMol,nRes,ALF)._ID=rRes;
            }
            ++nMol; nRes=0; rRes=0; key.BlasFill(0U);
            for(unsigned int i=0;i<key.Size();i++) RN[i]=UnknownResidue;
          } else if(PRN==PDB_ATOM) {
            tRes=ResidueID();
            if(rRes==0)   rRes=tRes;
            if(tRes!=rRes) {
              n=M.Model(nMod).Molecule(nMol).AltResidue(nRes)._AResidue.Size();
              for(unsigned int i=0;i<n;++i) {
                if(M.Model(nMod)._AFlag.IsValid()) ALF=M.Model(nMod)._AFlag[i];
                else ALF=' ';
                if(nRes==0) {
                  if(!IsMatchResidue(RN[i],key[i].Head()))
                    RN[i]=static_cast<PDBResidueName>(RN[i]+40);
                }
                M.Model(nMod).Residue(nMol,nRes,ALF).Allocate(RN[i],
                                                              key[i].Head());
                M.Model(nMod).Residue(nMol,nRes,ALF)._ID=rRes;
              }
              ++nRes;
              rRes=tRes;
              key.BlasFill(0U);
              for(unsigned int i=0;i<key.Size();i++) RN[i]=UnknownResidue;
            }
            PAN=AtomName();
            if(PAN==UnknownAtom)  fprintf(stderr,"Unknown Atom Type!\n");
            else {
              ALF=AltLocationFlag();
              if(ALF==' ')
                for(unsigned int i=0;i<key.Size();++i) {
                  key[i][PAN/32]|=(1<<(PAN%32));
                  if(RN[i]==UnknownResidue) RN[i]=ResidueName();
                }
              else {
                n=M.Model(nMod)._Index(ALF);
                key[n][PAN/32]|=(1<<(PAN%32));
                RN[n]=ResidueName();
              }
            }
          }
          if(_now[nl]=='\0')   break;
          _now+=nl+1;
        }
        _now=_content.Head();
      }
      void LoadAtom(PDBObject& M) {
        char ALF;
        unsigned int nl,nMod,nMol,nRes,tRes,rRes,nAlt;
        PDBRecordName PRN;
        PDBAtomName PAN;
        nMod=0;
        nMol=0;
        nRes=0;
        rRes=0;
        nAlt=M.Model(nMod).Molecule(nMol).AltResidue(nRes)._AResidue.Size();
        _now=_content.Head();
        while(1) {
          nl=LineSize(_now);
          PRN=RecordName();
          if(PRN==PDB_ENDMDL) { ++nMod; nMol=0; nRes=0; rRes=0; }
          else if(PRN==PDB_TER) { ++nMol; nRes=0; rRes=0; }
          else if(PRN==PDB_ATOM) {
            tRes=ResidueID();
            if(rRes==0) {
              rRes=tRes;
              nAlt=
                M.Model(nMod).Molecule(nMol).AltResidue(nRes)._AResidue.Size();
            }
            if(rRes!=tRes) {
              ++nRes; rRes=tRes;
              nAlt=
                M.Model(nMod).Molecule(nMol).AltResidue(nRes)._AResidue.Size();
            }
            ALF=AltLocationFlag();
            PAN=AtomName();
            if(ALF==' ') {
              for(unsigned int i=0;i<nAlt;++i) {
                M.Model(nMod).Molecule(nMol).AltResidue(nRes).WorkResidue(i).
                  Atom(PAN).BFactor()=BFactor();
                M.Model(nMod).Molecule(nMol).AltResidue(nRes).WorkResidue(i).
                  Atom(PAN).Location().X()=PositionX();
                M.Model(nMod).Molecule(nMol).AltResidue(nRes).WorkResidue(i).
                  Atom(PAN).Location().Y()=PositionY();
                M.Model(nMod).Molecule(nMol).AltResidue(nRes).WorkResidue(i).
                  Atom(PAN).Location().Z()=PositionZ();
              }
            } else {
              M.Model(nMod).Residue(nMol,nRes,ALF).Atom(PAN).BFactor()=
                BFactor();
              M.Model(nMod).Residue(nMol,nRes,ALF).Atom(PAN).Location().X()=
                PositionX();
              M.Model(nMod).Residue(nMol,nRes,ALF).Atom(PAN).Location().Y()=
                PositionY();
              M.Model(nMod).Residue(nMol,nRes,ALF).Atom(PAN).Location().Z()=
                PositionZ();
            }
          }
          if(_now[nl]=='\0')   break;
          _now+=nl+1;
        }
        _now=_content.Head();
      }

  };

  void Clear(PDBFile& F) {
    Clear(F._content); F._now=NULL; strncpy(F._code,"    ",5); }

}

#endif

