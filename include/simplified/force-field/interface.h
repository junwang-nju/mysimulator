
#ifndef _Force_Field_Interface_H_
#define _Force_Field_Interface_H_

#include "force-field/name.h"
#include "force-field/item.h"
#include "array/interface.h"

namespace mysimulator {

  class ForceField;
  ForceField& operator<<(ForceField&,const char*);

  class ForceField {

    public:

      typedef ForceField    Type;

    private:

      ForceFieldName  _tag;
      Array<_ForceFieldItem> _item;
      _ForceFieldItem _blank;

    public:

      ForceField() : _tag(ForceFieldName::Unknown), _item(), _blank() {}
      ForceField(const Type& FF) : ForceField() { imprint(FF); operator=(FF); }
      ForceField(Type&& FF) : ForceField() { swap(FF); }
      ~ForceField() { reset(); }

      operator bool() const { return _tag!=ForceFieldName::Unknown && (bool)_item; }
      ForceFieldName Name() const { return _tag; }
      const _ForceFieldItem operator[](const char* key) const {
        assert((bool)(*this));
        for(unsigned int i=0;i<_item.size();++i)
          if(strcmp(key,_item[i].Key())==0)  return _item[i];
        fprintf(stderr,"No expected iterms are found in force field!\n");
        return _blank;
      }
      bool IsForceFieldCompatible(ForceFieldName rName) {
        if(rName==_tag) return true;
        return false;
      }
      void reset() {
        _tag=ForceFieldName::Unknown;
        _item.reset();
      }

      Type& operator=(const Type& FF) {
        assert((bool)(*this));
        assert((bool)FF);
        assert(Name()==FF.Name());
        _item=FF._item;
        return *this;
      }
      Type& operator=(const char* content) {
        assert((bool)(*this));
        assert(IsForceFieldCompatible(__parse_name_for_forcefield(content)));
        unsigned int n=0, bg=0, ed=0, m=0;;
        char c,*field=nullptr,*rkey=nullptr,*rtype=nullptr,*rval=nullptr;
        while((c=content[++n])!='\0') {
          if(c=='[') {
            assert(m<_item.size());
            bg=n+1;
          } else if(c==']') {
            ed=n-1;
            field=new char[ed-bg+2];
            SubString(field,content,bg,ed);
            __parse_key_for_forcefield_record(rkey,field);
            if(strcmp(rkey,"Include")==0) {
              __parse_type_for_forcefield_record(rtype,field);
              assert(strcmp(rtype,"FILE")==0);
              __delete_array<char>(rtype);  rtype=nullptr;
              __parse_value_for_forcefield_record(rval,field);
              (*this)<<rval;
              __delete_array<char>(rval); rval=nullptr;
            } else _item[m]=field;
            __delete_array<char>(rkey); rkey=nullptr;
            __delete_array<char>(field);  field=nullptr;
            bg=0;
            ed=0;
            ++m;
          }
        }
        return *this;
      }

      void allocate(ForceFieldName FFN) {
        reset();
        _tag=FFN;
        switch(FFN) {
          case ForceFieldName::ResidueGo:
            _item.allocate(6);
            break;
          default:
            fprintf(stderr,"Unknown Type of Force Field!\n");
        }
      }
      void imprint(const Type& FF) {
        assert((bool)FF);
        reset();
        allocate(FF.Name());
      }

      void swap(Type& FF) {
        std::swap(_tag,FF._tag);
        std::swap(_item,FF._item);
      }

  };

}

namespace std {

  void swap(mysimulator::ForceField& A, mysimulator::ForceField& B) { A.swap(B); }

}

#include "force-field/io.h"

#endif

