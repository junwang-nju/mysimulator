
#ifndef _PDB_Interface_H_
#define _PDB_Interface_H_

#include "array2d/interface.h"
#include "pdb-model/interface.h"
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

}

#endif

